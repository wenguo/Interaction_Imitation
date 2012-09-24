#ifndef IMAGEBOX_HH
#define IMAGEBOX_HH
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <list>

#include "global.h"
#include "utils.hh"

using namespace std;

#define TX_BUFFER_SIZE CHANNEL_BUFFER_SIZE 
#define MAX_BUFF_SIZE 4096

class Canvas;

struct rgb{
    unsigned char red,green,blue;
};
struct color_info{
    rgb color;          // example color (such as used in test output)
    char *name;         // color's meaninful name (e.g. ball, goal)
    double merge;       // merge density threshold
    int expected_num;   // expected number of regions (used for merge)
    int min_area;
    int max_area;
    int y_low,y_high;   // Y,U,V component thresholds
    int u_low,u_high;
    int v_low,v_high;
};

class ImageBox
{
    public:
        ImageBox(Canvas*parent, int startx, int starty, int port, int width=320, int height=240);
        ~ImageBox();


        bool Connect();


        static void * Monitoring(void *ptr);
        void Snapshot(unsigned int ts);


        //    private:
        Canvas* canvas;
        int startx;
        int starty;

        pthread_t monitor_thread;
        pthread_mutex_t mutex;
        pthread_cond_t image_ready_cond;
        bool image_ready;

        list<blob_info_t*> blobs;
        blob_info_t blob_info[MAX_COLORS_TRACKED];

        static int index;
        int id;

        char name[64];

        int img_width;
        int img_height;
        double scale;
        unsigned char * img_yuv_buffer;
        RawImageFrame frame;
        unsigned char * img_rgb_buffer;

        unsigned int timestamp;
        bool userQuit;

        static bool flipped_image;
};


#endif
