#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

#include "imagebox.hh"
#include "canvas.hh"


int ImageBox::index = 0;
#ifndef LAPTOP
bool ImageBox::flipped_image = true;
#else
bool ImageBox::flipped_image = false;
#endif

ImageBox::ImageBox(Canvas*parent, int sx, int sy, int p, int width, int height)
{
    id = ImageBox::index++;
    img_width = width;
    img_height = height;
    scale = 1.0;

    canvas = parent;
    startx = sx;
    starty = sy;

    //img_yuv_buffer = new unsigned char[img_width* img_height *2];
    frame.hdr.type = RawImageFrame::ImageTypeRawYUV;
    frame.hdr.width = img_width;
    frame.hdr.height =img_height;
    frame.data = new uint8_t[img_width*img_height*2];
    img_rgb_buffer = new unsigned char[img_width* img_height *3];

    userQuit = false;


    image_ready = false;

    pthread_create(&monitor_thread, 0, Monitoring, this);
}

ImageBox::~ImageBox()
{
    if(frame.data)
        delete []frame.data;
    if(img_rgb_buffer)
        delete []img_rgb_buffer;
}

void *ImageBox::Monitoring(void *ptr)
{
    ImageBox* client = (ImageBox*) ptr;


    while(!client->userQuit)
    {
    }
    printf("exit thread\n");

    pthread_exit(NULL);
    return NULL;
}

void ImageBox::Snapshot(unsigned int ts)
{
        char filename[128];
        sprintf(filename, "%s/%d.ppm", "./", ts);
        pthread_mutex_lock(&mutex);
        ppm16Write(filename,img_rgb_buffer, img_width, img_height);
        pthread_mutex_unlock(&mutex);
}
