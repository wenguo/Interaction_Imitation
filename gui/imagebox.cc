#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

#include "imagebox.hh"
#include "canvas.hh"


int ImageBox::index = 0;
int iDisplay::index = 0;
#ifndef LAPTOP
bool ImageBox::flipped_image = true;
#else
bool ImageBox::flipped_image = false;
#endif

ImageBox::ImageBox(int p, int width, int height, iDisplay* parent)
{
    id = ImageBox::index++;
    img_width = width;
    img_height = height;
    port = p;
    clientsockfd = -1;

    display = parent;

    //img_yuv_buffer = new unsigned char[img_width* img_height *2];
    frame.hdr.type = RawImageFrame::ImageTypeRawYUV;
    frame.hdr.width = img_width;
    frame.hdr.height =img_height;
    frame.data = new uint8_t[img_width*img_height*2];
    img_rgb_buffer = new uint8_t[img_width* img_height *3];

    userQuit = false;
    channel_index = 0;

    connected = false;
    capturing = false;
    image_ready = false;

    
    char str[64];
    sprintf(str, "robot%d.%d", id, port);
    memcpy(name, str, strlen(str));

    pthread_cond_init(&image_ready_cond,NULL);
    logfile=NULL;

    pthread_create(&monitor_thread, 0, Monitoring, this);
    pthread_create(&capture_thread, 0, Capturing, this);
}

ImageBox::~ImageBox()
{
    printf("Destroy imagebox %d\n", id);
    if(frame.data)
        delete []frame.data;
    if(img_rgb_buffer)
        delete []img_rgb_buffer;
}

void *ImageBox::Monitoring(void *ptr)
{
    ImageBox* client = (ImageBox*) ptr;

    printf("Create imagebox %d\n", client->id);
    int sockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr;
 
    bool binded = false;
    //start server
    while(!binded)
    {
        sockfd = socket(AF_INET, SOCK_STREAM,0);
        if(sockfd <0)
        {
            binded =false;
            continue;
        }

        memset((char*) &serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(client->port);
        if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        {
            printf("ERROR on binding, try again in 1 second\n");
            binded = false;
            close(sockfd);
            usleep(1000000);
        }
        else
            binded  = true;

    }

    //listening for connection
    listen(sockfd,5);
    printf("listenging on port %d\n", client->port);

    struct sockaddr_in cli_addr;
    clilen = sizeof(cli_addr);
    client->clientsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    printf("accept\n");
    if (client->clientsockfd < 0) 
        printf("ERROR on accept\n");


    pthread_mutex_lock(&client->mutex);
    client->connected = true;
    pthread_mutex_unlock(&client->mutex);

    //main loop, keep reading
    unsigned char rx_buffer[SERVER_RX_BUFFER_SIZE];



    lolmsgParseInit(&client->parseContext, new uint8_t[SERVER_LOL_BUFFER_SIZE], SERVER_LOL_BUFFER_SIZE);

    while(!client->userQuit)
    {
        //reading
        memset(rx_buffer, 0, SERVER_RX_BUFFER_SIZE);
        int received = read(client->clientsockfd,rx_buffer, SERVER_RX_BUFFER_SIZE);
        if (received <= 0) 
        {
            printf("ERROR read to socket : %d -- it seems connection lost\n", received);
            client->connected = false;
            break;
        }
        else
        {
            int parsed = 0;
            while (parsed < received)
            {
                parsed += lolmsgParse(&client->parseContext, rx_buffer + parsed, received - parsed);
                LolMessage* msg = lolmsgParseDone(&client->parseContext);
                if(msg!=NULL)
                {
                    client->ProcessMessage(msg);
               //     client->RequestInfo(REQ_IMAGE_FRAME);
                }
            }
        }
        
    }
 
    printf("Imagebox %d exit monitoring thread\n", client->id);

    //disconnect with display
    client->display->imagebox = NULL;
    client->display = NULL;

    pthread_exit(NULL);
    return NULL;
}


void ImageBox::SetREQType(comm_status_t req_type)
{
    pthread_mutex_lock(&mutex);
    comm_tx_status = req_type;
    pthread_mutex_unlock(&mutex);
}

void ImageBox::Snapshot(unsigned int ts)
{
    if(connected)
    {
        char filename[128];
        sprintf(filename, "%s/%d.ppm", logfolder, ts);
        pthread_mutex_lock(&mutex);
        ppm16Write(filename,img_rgb_buffer, img_width, img_height);
        pthread_mutex_unlock(&mutex);
    }
}

void *ImageBox::Capturing(void *ptr)
{
    ImageBox* imagebox = (ImageBox*) ptr;
    while(1)
    {
        pthread_mutex_lock(&imagebox->mutex);
        while(!imagebox->image_ready)
        {
            pthread_cond_wait(&imagebox->image_ready_cond, &imagebox->mutex);
        }
        imagebox->image_ready = false;
        imagebox->WriteFrame(&imagebox->frame, imagebox->logfile);
        pthread_mutex_unlock(&imagebox->mutex);
        printf("write frame\n");
        //        imagebox->Snapshot(imagebox->canvas->timestamp);
    }

    return NULL;
}

bool ImageBox::WriteFrame(const RawImageFrame *frame, FILE *out_fd)
{
    if(!frame || out_fd<0) return(false);

    // write header and contents
    int hw = fwrite(&frame->hdr, 1, sizeof(frame->hdr), out_fd);
    int bw = fwrite(frame->data, 1, frame->hdr.width * frame->hdr.height, out_fd);

    bool ok = (hw==sizeof(frame->hdr) && bw==frame->hdr.width * frame->hdr.height);
    return(ok);
}

bool ImageBox::InitCapturing(const char *folder)
{
    if(!connected || !folder) return (false);

    capturing = true;

    char filename[256];
    sprintf(filename, "%s/%s.img", folder, name);

    logfile = fopen(filename, "w");

    if(!logfile)
        return false;
    else
        return true;

}


bool ImageBox::SendCommand(int sockfd, comm_status_t type, uint8_t *data, int32_t size)
{
    LolMessage msg;
    lolmsgInit(&msg, 0, type, data, size);
    int len = lolmsgSerializedSize(&msg);
    uint8_t buf[len];
    lolmsgSerialize(&msg, buf);
    int n = write(sockfd, buf, len);
    if(n<0)
        return false;
    else
        return true;
}

bool ImageBox::ProcessMessage(const LolMessage * msg)
{
    if(!msg || clientsockfd < 0)
        return false;
    //printLolMessage(msg);
    int image_size = img_width * img_height;
    int header_size = sizeof(RawImageFrame::RawImageFileHdr);

    switch (msg->command)
    {
        case REQ_IMAGE_FRAME_ACK:
            {
              //  printf("%d received new image\n", id);
                pthread_mutex_lock(&mutex);
                memcpy(&frame.hdr, msg->data, header_size );
                memcpy(frame.data, msg->data + header_size, image_size * 2);
                YUV422toRGB888(img_width, img_height, frame.data, img_rgb_buffer);

                if(flipped_image)
                {
                   flip(img_width, img_height, img_rgb_buffer); 
                }
                pthread_mutex_unlock(&mutex);

                if(capturing)
                {
                    pthread_mutex_lock(&mutex);
                    image_ready = true;
                    pthread_cond_signal(&image_ready_cond);
                    pthread_mutex_unlock(&mutex);
                }
                display->canvas->redraw_overlay();

                break;
            }
        case REQ_CHANNEL_INFO_ACK:
            {
                printf("%d received channel_info: ", id);
                for(int i=0;i<msg->length;i++)
                    printf("%d\t", msg->data[i]);
                printf("\n");
                pthread_mutex_lock(&mutex);
                display->canvas->user_input->sliders[RED]->value(msg->data[1]);
                display->canvas->user_input->sliders[GREEN]->value(msg->data[2]);
                display->canvas->user_input->sliders[BLUE]->value(msg->data[3]);
                display->canvas->user_input->sliders[YMIN]->value(msg->data[4]);
                display->canvas->user_input->sliders[YMAX]->value(msg->data[5]);
                display->canvas->user_input->sliders[UMIN]->value(msg->data[6]);
                display->canvas->user_input->sliders[UMAX]->value(msg->data[7]);
                display->canvas->user_input->sliders[VMIN]->value(msg->data[8]);
                display->canvas->user_input->sliders[VMAX]->value(msg->data[9]);
                pthread_mutex_unlock(&mutex);
                break;
            }
        case REQ_BLOB_INFO_ACK:
            {
                printf("%d received blobs info ", id);
                for(int i=0;i<msg->length;i++)
                    printf("%d\t", msg->data[i]);
                printf("\n");

                //blob_info_t *blob_info = new blob_info_t;
                memcpy(blob_info, msg->data, MAX_COLORS_TRACKED*sizeof(blob_info_t));

                display->canvas->redraw_overlay();

                break;
            }
        case REQ_ID_ACK:
            {
                printf("%d received client id: %s\n ", id, msg->data);

                memset(name, 0, 64);
                memcpy(name, msg->data, msg->length);

                time_t time_now = time(NULL);
                tm * timeinfo= localtime (&time_now);
                
                display->canvas->user_input->client_selection->add(name);
                display->canvas->user_input->client_selection->value(name);

                sprintf(logfolder, "./logs/%s-%02d%02d-%02d%02d%02d", name, timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

                mkdir(logfolder, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);


                break;
            }
        case UNKNOWN:
        default:
            break;
    }

 
    return true;
}

void ImageBox::Monitoring(LolMessage * msg, void *ptr)
{
    if(!msg || !ptr)
        return;

    ImageBox *imgbox = (ImageBox*)ptr;

    int image_size = imgbox->img_width * imgbox->img_height;
    int header_size = sizeof(RawImageFrame::RawImageFileHdr);

    switch (msg->command)
    {
        case REQ_IMAGE_FRAME_ACK:
            {
              //  printf("%d received new image\n", id);
                pthread_mutex_lock(&imgbox->mutex);
                memcpy(&imgbox->frame.hdr, msg->data, header_size );
                memcpy(imgbox->frame.data, msg->data + header_size, image_size * 2);
                YUV422toRGB888(imgbox->img_width, imgbox->img_height, imgbox->frame.data, imgbox->img_rgb_buffer);

                if(imgbox->flipped_image)
                {
                   flip(imgbox->img_width, imgbox->img_height, imgbox->img_rgb_buffer); 
                }
                pthread_mutex_unlock(&imgbox->mutex);

                if(imgbox->capturing)
                {
                    pthread_mutex_lock(&imgbox->mutex);
                    imgbox->image_ready = true;
                    pthread_cond_signal(&imgbox->image_ready_cond);
                    pthread_mutex_unlock(&imgbox->mutex);
                }
                imgbox->display->canvas->redraw_overlay();

                break;
            }
        case REQ_CHANNEL_INFO_ACK:
            {
                printf("%d received channel_info: ", imgbox->id);
                for(int i=0;i<msg->length;i++)
                    printf("%d\t", msg->data[i]);
                printf("\n");
                pthread_mutex_lock(&imgbox->mutex);
                imgbox->display->canvas->user_input->sliders[RED]->value(msg->data[1]);
                imgbox->display->canvas->user_input->sliders[GREEN]->value(msg->data[2]);
                imgbox->display->canvas->user_input->sliders[BLUE]->value(msg->data[3]);
                imgbox->display->canvas->user_input->sliders[YMIN]->value(msg->data[4]);
                imgbox->display->canvas->user_input->sliders[YMAX]->value(msg->data[5]);
                imgbox->display->canvas->user_input->sliders[UMIN]->value(msg->data[6]);
                imgbox->display->canvas->user_input->sliders[UMAX]->value(msg->data[7]);
                imgbox->display->canvas->user_input->sliders[VMIN]->value(msg->data[8]);
                imgbox->display->canvas->user_input->sliders[VMAX]->value(msg->data[9]);
                pthread_mutex_unlock(&imgbox->mutex);
                break;
            }
        case REQ_BLOB_INFO_ACK:
            {
                printf("%d received blobs info ", imgbox->id);
                for(int i=0;i<msg->length;i++)
                    printf("%d\t", msg->data[i]);
                printf("\n");

                //blob_info_t *blob_info = new blob_info_t;
                memcpy(imgbox->blob_info, msg->data, MAX_COLORS_TRACKED*sizeof(blob_info_t));

                imgbox->display->canvas->redraw_overlay();

                break;
            }
        case REQ_ID_ACK:
            {
                printf("%d received client id: %s\n ", imgbox->id, msg->data);

                memset(imgbox->name, 0, 64);
                memcpy(imgbox->name, msg->data, msg->length);

                time_t time_now = time(NULL);
                tm * timeinfo= localtime (&time_now);
                
                imgbox->display->canvas->user_input->client_selection->add(imgbox->name);
                imgbox->display->canvas->user_input->client_selection->value(imgbox->name);

                sprintf(imgbox->logfolder, "./logs/%s-%02d%02d-%02d%02d%02d", imgbox->name, timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

                mkdir(imgbox->logfolder, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH);


                break;
            }
        case UNKNOWN:
        default:
            break;
    }

 
    return;
}



bool ImageBox::SetChannelInfo(color_info ch_info, int index)
{
    printf("%d set channel  %d info\n", id, index);

    unsigned char tx_buffer[CLIENT_RX_BUFFER_SIZE];
    tx_buffer[0] = index;
    tx_buffer[1] = ch_info.color.red;
    tx_buffer[2] = ch_info.color.green;
    tx_buffer[3] = ch_info.color.blue;
    tx_buffer[4] = ch_info.y_low;
    tx_buffer[5] = ch_info.y_high;
    tx_buffer[6] = ch_info.u_low;
    tx_buffer[7] = ch_info.u_high;
    tx_buffer[8] = ch_info.v_low;
    tx_buffer[9] = ch_info.v_high;

    return SendCommand(clientsockfd, SET_CHANNEL_INFO, tx_buffer, 10);

}

bool ImageBox::RequestInfo(comm_status_t req_type)
{

    if(clientsockfd<0)
        return false;

    bool ret=false;
    unsigned char tx_buffer[CLIENT_RX_BUFFER_SIZE];

   //requesting
    memset(tx_buffer, 0, CLIENT_RX_BUFFER_SIZE);
    switch (req_type)
    {
        case REQ_CHANNEL_INFO:
            {
                printf("%d request channel %d info\n", id, channel_index);
            
                tx_buffer[0] = channel_index;

                ret = SendCommand(clientsockfd, REQ_CHANNEL_INFO, tx_buffer, 1);
                break;
            }
        case REQ_BLOB_INFO:
            {
                printf("%d request channel %d blob info, expected size %d\n", id, channel_index, MAX_COLORS_TRACKED*sizeof(blob_info_t));
                tx_buffer[0] = channel_index;
                ret = SendCommand(clientsockfd, REQ_BLOB_INFO, tx_buffer, 1);
                break;
            }
        case REQ_IMAGE_FRAME:
            {
                printf("%d request image frame\n", id);
                tx_buffer[0]=0xAA;
                ret = SendCommand(clientsockfd, REQ_IMAGE_FRAME, tx_buffer, 1);
                break;
            }
        case REQ_ID:
            {
                tx_buffer[0]=0xAA;
                ret = SendCommand(clientsockfd, REQ_ID, tx_buffer, 1);

                break;
            }
        case UNKNOWN:
        default:
            break;

    }

    return ret;

}

iDisplay::iDisplay(Canvas * parent, int x, int y, int w, int h)
{
    startx = x;
    starty = y;
    canvas = parent;

    width = w;
    height = h;

    region_x1 = 0;
    region_y1 = 0;
    region_x2 = 0;
    region_y2 = 0;
    clicked = 0;

    imagebox = NULL;

    scale = 1.0;
    id = iDisplay::index++;

}

bool iDisplay::SetImageBox(ImageBox *box) 
{
    imagebox = box;
    if(box)
    {
        imagebox->display = this;
        return true;
    }
    else
        return false;
}


bool iDisplay::InRegion(int x, int y)
{
    if ( x > startx && x <= startx + scale * width && y > starty && y<=starty + scale * height)
        return true;
    else
        return false;

}
