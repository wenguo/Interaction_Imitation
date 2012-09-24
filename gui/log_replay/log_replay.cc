#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

#include <FL/Fl_Button.H>

#include "global.h"
#include "canvas.hh"
#include "imagebox.hh"

using namespace std;

const int width  = 320;
const int height = 240;

int channel_index = 0;
color_info channel_info;

void Start(Fl_Widget* o, void*);
void Stop(Fl_Widget* o, void*);
void Snapshot(Fl_Widget* o, void*);
void Capture(Fl_Widget* o, void*);
void Stream(Fl_Widget* o, void*);
void SetChannelInfo(Fl_Widget *, void *);
void GetChannelInfo(Fl_Widget *, void *);

const char *slider_names[9] = {"Red", "Green", "Blue", "Y_min", "U_min", "V_min", "Y_max", "U_max", "V_max"};
enum slider_index{RED=0, GREEN, BLUE, YMIN, UMIN, VMIN, YMAX, UMAX, VMAX};

Canvas * canvas;

UserInput* Input;

//--------------------------------------------
int main(int argc, char **argv) {
    
    Input = new UserInput;
    canvas =  new Canvas(663, 600, Input, "Log_Replay");

    Fl_Button but_start( 70, 520, 80, 40,"Start" );
    Fl_Button but_stop( 220, 520, 80, 40,"Stop" );
    Fl_Button but_snapshot( 370, 520, 80, 40,"Snapshot" );
    Fl_Button but_flip( 520, 520, 80, 40,"Capture" );
    Fl_Check_Button but_stream(700, 20, 200, 20, "Streaming Image");
    but_start.callback(Start);
    but_stop.callback(Stop);
    but_snapshot.callback(Snapshot);
    but_stream.callback(Stream);
    but_flip.callback(Capture);

    canvas->end();
    canvas->show();
    canvas->redraw_overlay();

    return Fl::run();
}

#define PIXEL_FORMAT V4L2_PIX_FMT_YUYV

void callback(void*input)
{
    Fl::repeat_timeout(0.1, callback);    
    Canvas::timestamp++;
    //canvas->redraw_overlay();
}

void Start(Fl_Widget* o, void* input)
{
    Fl::add_timeout(0.1, callback, input);
}

void Stop(Fl_Widget * o, void * input)
{
    Fl::remove_timeout(callback);
}

void Snapshot(Fl_Widget * o, void *input)
{   
    string time_string;
    ::time_t time_now = time(NULL);
    struct tm * timeinfo;
    timeinfo = localtime (&time_now);

    canvas->Snapshot(timeinfo);


}

void Stream(Fl_Widget * o, void * input)
{
    Fl_Check_Button * btn = (Fl_Check_Button*) o;
 
    printf("stream clicked %d\n", btn->value());
}

void Capture(Fl_Widget * o, void * input)
{
    string time_string;
    ::time_t time_now = time(NULL);
    struct tm * timeinfo;
    timeinfo = localtime (&time_now);
    canvas->Capture(timeinfo);
}


void SetChannelInfo(Fl_Widget * o, void *input)
{
}
void GetChannelInfo(Fl_Widget * o, void *input)
{
}
