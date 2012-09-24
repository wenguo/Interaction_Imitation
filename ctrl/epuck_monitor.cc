#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "epuck.hh"
#include "lolmsg.h"
#include "global.h"

char * g_host("localhost");
//char * g_host("192.168.0.59");
extern int userQuit;

void Robot::Subscribe(const LolMessage*msg, void *ptr)
{
    if(!msg || !ptr)
        return;

    Robot *robot = (Robot*)ptr;
    int monitoring_port = 0;
    switch(msg->command)
    {
        case REQ_SUBSCRIPTION_ACK:
            {
                if(!robot->monitoringIPC)
                {
                    monitoring_port = msg->data[1];
                    monitoring_port = monitoring_port << 8 | msg->data[0];
                    robot->monitoringIPC = new IPC::IPC();
                    robot->monitoringIPC->SetCallback(Monitoring, (void*)robot);
                    robot->monitoringIPC->Start(g_host, monitoring_port, false);
                    char hostname[64];
                    gethostname(hostname,64);
                    robot->monitoringIPC->SendData(REQ_ID_ACK, (uint8_t*)hostname, strlen(hostname));
                }
            }     
        default:
            break;
    }
}


void Robot::Monitoring(const LolMessage*msg, void *ptr)
{
    if(!msg || !ptr)
        return;

    Robot *robot = (Robot*)ptr;

    if(!robot->monitoringIPC)
        return;

    int image_size = robot->img_width * robot->img_height * 2;
    int header_size =sizeof(RawImageFrame::RawImageFileHdr);
    unsigned char *tx_buffer=new unsigned char[image_size + header_size];

    switch(msg->command)
    {
        case REQ_IMAGE_FRAME:
            {
                printf("recieved request for new image\n");
                pthread_mutex_lock(&robot->vision_mutex);
                memcpy(tx_buffer, (unsigned char*)&robot->frame.hdr, header_size);
                memcpy(tx_buffer + header_size, (unsigned char*)robot->img->data, image_size);				
                pthread_mutex_unlock(&robot->vision_mutex);


                for(int ch=0; ch<MAX_COLORS_TRACKED; ch++)
                {
                    pthread_mutex_lock(&robot->vision_mutex);
                    rgb c = robot->vision.getColorVisual(ch);
                    CMVision::region* reg = robot->vision.getRegions(ch);
                    pthread_mutex_unlock(&robot->vision_mutex);

                    while(reg)
                    {
                        addBlob(reg->x1, reg->y1, reg->x2, reg->y2, tx_buffer + header_size, robot->img_width, robot->img_height, c);
                        reg = reg->next;
                    }

                }

                robot->monitoringIPC->SendData(REQ_IMAGE_FRAME_ACK, tx_buffer, image_size + header_size);
            }
            break;
        case REQ_CHANNEL_INFO:
            {
                printf("recieved request for channel_info\n");
                int ymin,ymax,umin,umax,vmin,vmax;
                rgb color=robot->vision.getColorVisual(msg->data[0]);
                robot->vision.getThreshold(msg->data[0], ymin,ymax,umin,umax,vmin,vmax);
                tx_buffer[0] = msg->data[0];
                tx_buffer[1] = color.red;
                tx_buffer[2] = color.green;
                tx_buffer[3] = color.blue;
                tx_buffer[4] = ymin;
                tx_buffer[5] = ymax;
                tx_buffer[6] = umin;
                tx_buffer[7] = umax;
                tx_buffer[8] = vmin;
                tx_buffer[9] = vmax;


                robot->monitoringIPC->SendData(REQ_CHANNEL_INFO_ACK, tx_buffer, 10);

            }
            break;

        case SET_CHANNEL_INFO:
            {
                printf("Received request to set channel %d info\n", msg->data[0]);
                CMVision::color_info *colorinfo = robot->vision.getColorInfo(msg->data[0]);
                colorinfo->color.red = msg->data[1];
                colorinfo->color.green  = msg->data[2];
                colorinfo->color.blue  = msg->data[3];

                int ymin,ymax,umin,umax,vmin,vmax;
                ymin = msg->data[4];
                ymax = msg->data[5];
                umin = msg->data[6];
                umax = msg->data[7];
                vmin = msg->data[8];
                vmax = msg->data[9];

                robot->vision.setThreshold(msg->data[0], ymin,ymax,umin,umax, vmin,vmax);

                tx_buffer[0] = 0xAA;
                robot->monitoringIPC->SendData(SET_CHANNEL_INFO_ACK, tx_buffer, 1);


                printf("red: %d\ngreen: %d\nblue: %d\nymin: %d\nymax: %d\numin: %d\numax: %d\nvmin: %d\nvmax: %d\n", 
                        msg->data[1], msg->data[2], msg->data[3],
                        ymin,ymax,umin,umax,vmin,vmax);
            }
            break;
        case REQ_BLOB_INFO:
            {
                printf("recieved request for blob_info\n");
                blob_info_t blob_info[MAX_COLORS_TRACKED];
                memset(&blob_info, 0, MAX_COLORS_TRACKED*sizeof(blob_info_t));

                std::list<Object*>::iterator it;
                if(robot->vm)
                {
                    std::list<Object*> objects = robot->vm->Objects();
                    int num_blobs[MAX_COLORS_TRACKED] = {0};
                    for(it = objects.begin();it!=objects.end();it++)
                    {
                        Object * obj = *it;
                        if(obj)
                        {
                            for(int ch=0;ch<MAX_COLORS_TRACKED;ch++)
                            {
                                Blob_info blob = obj->GetLatestAveragedBlobInfo(robot->timestamp, ch);
                                blob_info[ch].channel = ch;
                                if(blob.sys_timestamp!=-1)
                                {
                                    if(num_blobs[ch] >= MAX_BLOBS_PER_CHANNEL)
                                        break;
                                    blob_info[ch].blobs[num_blobs[ch]].offset.x = blob.offset.x;
                                    blob_info[ch].blobs[num_blobs[ch]].offset.y = blob.offset.y;
                                    blob_info[ch].blobs[num_blobs[ch]].size.x = blob.size.x;
                                    blob_info[ch].blobs[num_blobs[ch]].size.y = blob.size.y;
                                    blob_info[ch].blobs[num_blobs[ch]].id = obj->id;
                                    num_blobs[ch]++;
                                }
                            }
                        }
                    }
                    for(int ch=0;ch<MAX_COLORS_TRACKED;ch++)
                        blob_info[ch].num_blobs=num_blobs[ch];

                }
                //memcpy(tx_buffer, blob_info, MAX_COLORS_TRACKED * sizeof(blob_info_t));
                robot->monitoringIPC->SendData(REQ_BLOB_INFO_ACK, (uint8_t*)blob_info, MAX_COLORS_TRACKED * sizeof(blob_info_t));
            }
            break;
        case REQ_ID:
            {
                printf("received request for ID\n");
                char hostname[64];
                gethostname(hostname,64);
                int size=strlen(hostname);
                robot->monitoringIPC->SendData(REQ_ID_ACK, (uint8_t*)hostname, size);
            }
            break;
        case UNKNOWN:
        default:
            break;

    }


}
