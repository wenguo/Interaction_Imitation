#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 


#include "capture.h"
#include "cmvision.h"
#include "global.h"

const char *color_filename = "colors.txt";
const int input_idx = 1;
const int width  = 320;
const int height = 240;
const int num_frames = 10000;
int portno = 5000;

#ifdef LAPTOP
#define PIXEL_FORMAT V4L2_PIX_FMT_YUYV
const char *video_device = "/dev/video0";
#else
#define PIXEL_FORMAT V4L2_PIX_FMT_UYVY
const char *video_device = "/dev/video1";
#endif

#define RX_BUFFER_SIZE HEADER_SIZE + CHANNEL_INFO_SIZE + CRC_SIZE



unsigned char rx_buffer[RX_BUFFER_SIZE];
unsigned char tx_buffer[width*height*3];



void addBlob(int x1, int y1, int x2, int y2, unsigned char * img, int width, int height, rgb color);
void addBlobRGB(int x1, int y1, int x2, int y2, unsigned char * img, int width, int height, rgb c);

int main(int argc, char *argv[])
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;


 /*   system("modprobe -r poX030");
    system("modprobe -r atmel_isi");
    system("modprobe  poX030");
*/
    if(argc == 3)
    {
        portno = atoi(argv[2]);
        server = gethostbyname(argv[1]);
        if (server == NULL) 
        {
            printf("ERROR, no such host\n");
            exit(0);
        }
    }
    else if(argc ==1)
    {
        portno = 5000;
        //server = gethostbyname("192.168.0.59");
        server = gethostbyname("localhost");
    }
    else
    {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        printf("ERROR opening socket\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
        printf("ERROR connecting\n");
        exit(0);
    }


    Capture cap;
    CMVision vision;

    // initialize
    if(!cap.init(video_device,input_idx,width,height,PIXEL_FORMAT))
    {
        printf("Error initializing camera");
        return 0;
    }

    if(!vision.initialize(width, height))
    {
        printf("Error initializing vision");
        return 0;
    }
    if(!vision.loadOptions(color_filename))
    {
        printf("Error loading color file");
    }


    unsigned  char * dst = new unsigned char[width*height*3];
    RawImageFrame frame;
    frame.hdr.type = RawImageFrame::ImageTypeRawYUV;
    frame.hdr.width = width;
    frame.hdr.height = height;
    frame.data = new uint8_t[width*height*2];
    memset(dst, 0, width*height*3);
    memset(frame.data, 0, width*height*2);
    char ppmFilename1[64];
    char ppmFilename2[64];

    blob_info_t blob_info[MAX_COLORS_TRACKED];

    // main loop
    for(int i=0; i<num_frames; i++)
    {
        // capture and process a frame
        const Capture::Image *img = cap.captureFrame();


        if(img != NULL)
        {
            sprintf(ppmFilename1, "log_%da.ppm", i);
            sprintf(ppmFilename2, "log_%db.ppm", i);
            Capture::YUV422toRGB888(width, height, (unsigned char*) img->data, dst);
            frame.hdr.timestamp= img->timestamp;
            memcpy(frame.data, (unsigned char*)img->data, width*height*2);
            //Capture::YUYVtoUYVY(width, height, (unsigned char*) img->data, data_dst);


            //addBlob(391,199, 395,300, dst, width, height);
            vision.processFrame(reinterpret_cast<image_pixel*>(img->data));

            for(int ch=0; ch<CMV_MAX_COLORS; ch++)
            {
                rgb c = vision.getColorVisual(ch);
                CMVision::region* reg = vision.getRegions(ch);

                while(reg)
                {
                    //printf("%s %d %d (%.2f %.2f): %d %d %d %d\n",vision.getColorName(ch), reg->color, reg->area, reg->cen_x, reg->cen_y, reg->x1, reg->y1, reg->x2, reg->y2);
                    addBlob(reg->x1, reg->y1, reg->x2, reg->y2, frame.data, width, height, c);
                    addBlobRGB(reg->x1, reg->y1, reg->x2, reg->y2, dst, width, height, c);
                    reg = reg->next;
                }

            }

            memset(rx_buffer, 0, RX_BUFFER_SIZE);
            n = read(sockfd,rx_buffer,RX_BUFFER_SIZE);
            if (n < 0) 
                printf("ERROR writing to socket\n");
            else
            {
                printf("read %d bytes :\n", n);
                for(int i=0;i<n;i++)
                    printf("%#x\t", rx_buffer[i]);
                printf("\n");
            }


            switch (rx_buffer[0])
            {
                case REQ_IMAGE_FRAME:
                    {
#ifdef TRANSFER_RGB
                        n = write(sockfd, dst, width*height * 3);
#else
                        n = write(sockfd, &frame.hdr, sizeof(RawImageFrame::RawImageFileHdr));
                        n += write(sockfd, frame.data, width*height*2);
#endif
                        if (n < 0) 
                            printf("ERROR writing to socket\n");
                    }
                    break;
                case REQ_CHANNEL_INFO:
                    {
                        int ymin,ymax,umin,umax,vmin,vmax;
                        rgb color=vision.getColorVisual(rx_buffer[1]);
                        vision.getThreshold(rx_buffer[1], ymin,ymax,umin,umax,vmin,vmax);
                        tx_buffer[0] = rx_buffer[1];
                        tx_buffer[1] = color.red;
                        tx_buffer[2] = color.green;
                        tx_buffer[3] = color.blue;
                        tx_buffer[4] = ymin;
                        tx_buffer[5] = ymax;
                        tx_buffer[6] = umin;
                        tx_buffer[7] = umax;
                        tx_buffer[8] = vmin;
                        tx_buffer[9] = vmax;

                        printf("Send channel %d info  ... ", rx_buffer[1]);
                        n = write(sockfd, tx_buffer, RX_BUFFER_SIZE);
                        if (n < 0) 
                            printf("failed %d\n", n);
                        else
                            printf("Done %d!\n",n);

                    }
                    break;
                case SET_CHANNEL_INFO:
                    {
                        printf("Received request to set channel %d info\n", rx_buffer[1]);
                        CMVision::color_info *colorinfo = vision.getColorInfo(rx_buffer[1]);
                        colorinfo->color.red = rx_buffer[2];
                        colorinfo->color.green  = rx_buffer[3];
                        colorinfo->color.blue  = rx_buffer[4];

                        int ymin,ymax,umin,umax,vmin,vmax;
                        ymin = rx_buffer[5];
                        ymax = rx_buffer[6];
                        umin = rx_buffer[7];
                        umax = rx_buffer[8];
                        vmin = rx_buffer[9];
                        vmax = rx_buffer[10];

                        vision.setThreshold(rx_buffer[1], ymin,ymax,umin,umax, vmin,vmax);

                        printf("red: %d\ngreen: %d\nblue: %d\nymin: %d\nymax: %d\numin: %d\numax: %d\nvmin: %d\nvmax: %d\n", 
                                rx_buffer[2], rx_buffer[3], rx_buffer[4],
                                ymin,ymax,umin,umax,vmin,vmax);
                    }
                    break;
                case REQ_BLOB_INFO:
                    {
                        memset(blob_info, 0, MAX_COLORS_TRACKED*sizeof(blob_info_t));
                        for(int ch=0; ch<MAX_COLORS_TRACKED;ch++)
                        {
                            int num_blobs = 0;
                            rgb c = vision.getColorVisual(ch);
                            CMVision::region* reg = vision.getRegions(ch);
                            printf("request blob info, channel %d\n",ch);

                            blob_info[ch].channel = ch;

                            while(reg)
                            {
                                blob_info[ch].num_blobs=num_blobs + 1;
                                blob_info[ch].blobs[num_blobs].offset.x = width/2-(reg->x1+reg->x2)/2;
                                blob_info[ch].blobs[num_blobs].offset.y = height/2-(reg->y1+ reg->y2)/2;
                                blob_info[ch].blobs[num_blobs].size.x = reg->x2-reg->x1;
                                blob_info[ch].blobs[num_blobs].size.y = reg->y2 - reg->y1;
                                reg = reg->next;
                                if(num_blobs++ > MAX_BLOBS_PER_CHANNEL)
                                    break;
                            }
                        }
                        //TODO append crc to tx_buffer
                        memcpy(tx_buffer, blob_info, MAX_COLORS_TRACKED*sizeof(blob_info_t));
                        printf("Send blob info  ... %d ", MAX_COLORS_TRACKED*sizeof(blob_info_t));
                        n = write(sockfd, tx_buffer, MAX_COLORS_TRACKED*sizeof(blob_info_t));
                        if (n < 0) 
                            printf("failed %d\n", n);
                        else
                            printf("Done %d!\n",n);
                    }
                    break;
                case REQ_ID:
                    {
                        tx_buffer[0]='l';
                        tx_buffer[1]='a';
                        tx_buffer[2]='p';
                        tx_buffer[3]='t';
                        tx_buffer[4]='o';
                        tx_buffer[5]='p';
                        tx_buffer[6]='\0';
                        n = write(sockfd, tx_buffer, 7);
                        if (n < 0) 
                            printf("failed %d\n", n);
                        else
                            printf("Done %d!\n",n);
                    }
                    break;
                case UNKNOWN:
                default:
                    {
                        printf("Request type %d -- %d\n", rx_buffer[0], n);
                        for(int i=0;i<RX_BUFFER_SIZE;i++)
                            printf("%#x\t",rx_buffer[i]);
                        printf("\n");
                    }
                    break;
            }
            //cap.ppm16Write(ppmFilename1, dst, width, height);
            memset(dst, 0, width*height*3);
            memset(frame.data, 0, width*height*2);


            // do something with the data here
            printf("."); fflush(stdout);


            cap.releaseFrame(img);
        }
    }
    printf("\n");

    delete []dst;
    delete []frame.data;

    cap.close();

    return 1;

}


typedef struct
{
    unsigned char u;
    unsigned char y1;
    unsigned char v;
    unsigned char y2;
} uyvy_t;

void addBlob(int x1, int y1, int x2, int y2, unsigned char * img, int width, int height, rgb color)
{
    int y,u,v;
    if(x1<0)
        x1=0;
    if(x2<0)
        x2=0;
    if(y1<0)
        y1=0;
    if(y2<0)
        y2=0;
    if(x1>=width)
        x1=width-1;
    if(x2>=width)
        x2=width-1;
    if(y1>=height)
        y1=height-1;
    if(y2>=height)
        y2=height-1;

    RGB2YUV(color.red, color.green, color.blue, y,u,v);

    for (int i=x1; i<=x2;i++)
    {
        img[(y1*width  + i )*2] = u;
        img[(y1*width  + i)*2 + 1] = y;
        img[(y1*width  + i)*2 + 2] = v;
        img[(y1*width  + i)*2 + 3] = y;
    }
    for (int i=x1; i<=x2;i++)
    {
        img[(y2*width  + i )*2] = u;
        img[(y2*width  + i)*2 + 1] = y;
        img[(y2*width  + i)*2 + 2] = v;
        img[(y2*width  + i)*2 + 3] = y;
    }

    for (int i=y1; i<=y2;i++)
    {
        img[(i*width  + x1)*2] = u;
        img[(i*width  + x1)*2 + 1] = y;
        img[(i*width  + x1)*2 + 2] = v;
        img[(i*width  + x1)*2 + 3] = y;
    }
    for (int i=y1; i<=y2;i++)
    {
        img[(i*width  + x2)*2] = u;
        img[(i*width  + x2)*2 + 1] = y;
        img[(i*width  + x2)*2 + 2] = v;
        img[(i*width  + x2)*2 + 3] = y;
    }
}
void addBlobRGB(int x1, int y1, int x2, int y2, unsigned char * img, int width, int height, rgb c)
{
    if(x1<0)
        x1=0;
    if(x2<0)
        x2=0;
    if(y1<0)
        y1=0;
    if(y2<0)
        y2=0;
    if(x1>=width)
        x1=width-1;
    if(x2>=width)
        x2=width-1;
    if(y1>=height)
        y1=height-1;
    if(y2>=height)
        y2=height-1;


    for (int i=x1; i<=x2;i++)
    {
        img[(y1*width  + i )*3] = 255 - c.red;
        img[(y1*width  + i)*3 + 1] = 255 - c.green;
        img[(y1*width  + i)*3 + 2] = 255 - c.blue;
    }
    for (int i=x1; i<=x2;i++)
    {
        img[(y2*width  + i )*3] = 255 - c.red;
        img[(y2*width  + i)*3 + 1] = 255 - c.green;
        img[(y2*width  + i)*3 + 2] = 255 - c.blue;
    }

    for (int i=y1; i<=y2;i++)
    {
        img[(i*width  + x1)*3] = 255 - c.red;
        img[(i*width  + x1)*3 + 1] = 255 - c.green;
        img[(i*width  + x1)*3 + 2] = 255 - c.blue;
    }
    for (int i=y1; i<=y2;i++)
    {
        img[(i*width  + x2)*3] = 255 - c.red;
        img[(i*width  + x2)*3 + 1] = 255 - c.green;
        img[(i*width  + x2)*3 + 2] = 255 - c.blue;
    }
}
