#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>


#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Overlay_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Input_Choice.H>

#include <iostream>
#include <fstream>
#include "VisualMemory.hh"

using namespace std;

void Start(Fl_Widget* o, void*);
void Stop(Fl_Widget* o, void*);
void StepForward(Fl_Widget* o, void*);
void StepBackward(Fl_Widget* o, void*);
void SelectLog(Fl_Widget* o, void*);
const int width  = 320;
const int height = 240;
int timestamp=0;

VisualMemory vm(320, 240);

int GetLogsDir (vector<string> &files);


const Fl_Color colors[]={FL_RED, FL_GREEN};

class ImageBox : public Fl_Overlay_Window
{
    public:
        ImageBox(int w, int h): 
            Fl_Overlay_Window(w,h,"ImageBox"),
            region_x1(0),
            region_y1(0),
            region_x2(0),
            region_y2(0),
            clicked(false)
    {
        startx = (640-width)/2;
        starty = (480-height)/2;
    };
        void draw_overlay();
        int handle(int event);
        ~ImageBox(){};
        int region_x1; //selection region
        int region_y1;
        int region_x2;
        int region_y2;

        int startx;
        int starty;

        int clicked;
};

ImageBox * imgbox;

void ImageBox::draw_overlay()
{
    fl_color(FL_BLACK);
    fl_rect(10,10,640,480); //draw a frame box around image
    fl_rect(660,10,220,570); //draw a frame box around image
    fl_rect(10,500,640,80); //draw a frame box around image

    char str[64];
    sprintf(str, "%d", timestamp);
    fl_draw_box(FL_FLAT_BOX, startx, starty, width, height, FL_BLACK);
    fl_color(FL_RED);
    fl_draw(str,10, 25);

    int orig_x = startx+ width/2;
    int orig_y = starty + height/2;
    
    printf("------------------------------------\n");


    std::list<Object*>::iterator it;
    for(int i=0;i<2;i++)
    {
        std::list<Object*> objects = i==0 ? vm.OldObjects() : vm.Objects();
        for(it = objects.begin(); it!=objects.end();it++)
        {
            Object * obj = *it;
            if(obj)
            {
                for(int i=0;i<MAX_COLORS_TRACKED;i++)
                {
                    Blob_info blob=obj->GetAveragedBlobInfo(timestamp, i);
                    std::list<Blob_info*> blobs=obj->GetBlobs(timestamp, i);
                    std::list<Blob_info*>::iterator it;
                    for(it=blobs.begin();it!=blobs.end();it++)
                    {
                        Blob_info * blob = *it;
                        if(blob->sys_timestamp!=-1)
                        {
                            fl_color(colors[i]);
                            fl_rect(blob->offset.x -  blob->size.x / 2 + orig_x,
                                    blob->offset.y - blob->size.y / 2 + orig_y,
                                    blob->size.x,
                                    blob->size.y);
                            fl_color(FL_WHITE);
                            /*fl_rect(blob->offset.x + startx - 2,
                              blob->offset.y + starty - 2,
                              4,
                              4);*/
                            fl_line(blob->offset.x -10 + orig_x, blob->offset.y + orig_y,
                                    blob->offset.x + 10 + orig_x, blob->offset.y + orig_y);
                            fl_line(blob->offset.x + orig_x, blob->offset.y - 10 + orig_y,
                                    blob->offset.x+ orig_x, blob->offset.y + 10 + orig_y);
                            sprintf(str, "%d", obj->id);
                            fl_color(FL_YELLOW);
                            fl_draw(str,blob->offset.x + orig_x, blob->offset.y + orig_y);

                        }
                    }
                }
            }
        }
    }

    fl_color(FL_BLACK);
    sprintf(str, "(%d %d) -- (%d %d)", region_x1-startx, region_y1-starty, region_x1-startx-width/2, region_y1-starty - height/2);
    fl_draw(str,700, 300);

}

//event handler
int ImageBox::handle(int event)
{
    Fl_Window::handle(event);
    switch(event)
    {
        case FL_MOVE:
            break;
        case FL_PUSH:
            break;
        case FL_RELEASE:
            if(Fl::event_x() > startx && Fl::event_x() < startx + width
                    && Fl::event_y()>starty && Fl::event_y() < starty + height)
            {
                region_x1 = Fl::event_x();
                region_y1 = Fl::event_y();
                redraw_overlay();
            }
            break;
        case FL_FOCUS:
        case FL_UNFOCUS:
            //.... Return 1 if you want keyboard events, 0 otherwise
            return 1;
        case FL_KEYBOARD:
            switch(Fl::event_key())
            {
                case FL_Up:
                    StepForward(NULL,NULL);
                    break; 
                case FL_Down:
                    StepBackward(NULL,NULL);
                    break;
                default:
                    return 0;
            }
            return 1;
        default:
            break;
    }

    return 1;

}



//--------------------------------------------
int main(int argc, char **argv) {


    /*for(int i=0;i<10;i++)
      {
      Object * obj = new Object();
      if(obj->LoadRecordsFromFile("object",i))
      {
      objects.push_back(obj);
      obj->Print();
      }
      }
      */


    vector<string> dirs = vector<string>();
    GetLogsDir(dirs);
    for (unsigned int i = 0;i < dirs.size();i++) {
        cout << dirs[i] << endl;
    }


    imgbox =  new ImageBox(900, 600);
    Fl_Button but_start( 70, 520, 80, 40,"Run" );
    Fl_Button but_stop( 220, 520, 80, 40,"Stop" );
    Fl_Button but_stepforward( 370, 520, 80, 40,"StepF" );
    Fl_Button but_stepbackward( 520, 520, 80, 40,"StepB" );
    but_start.callback(Start);
    but_stop.callback(Stop);
    but_stepforward.callback(StepForward);
    but_stepbackward.callback(StepBackward);


    Fl_Input_Choice in(670, 20, 200, 25);
    in.callback(SelectLog);
    for (int i = 0;i < dirs.size();i++)
    {
        in.add(dirs[i].c_str());
    }
    if(dirs.size()>0)
        in.value(0);

    imgbox->end();
    imgbox->show();
    imgbox->redraw_overlay();

    return Fl::run();
}

#define PIXEL_FORMAT V4L2_PIX_FMT_YUYV

void callback(void*input)
{
    Fl::repeat_timeout(0.01, callback);    
    timestamp++;
    imgbox->redraw_overlay();
}

void Start(Fl_Widget* o, void* input)
{
    Fl::add_timeout(0.1, callback, input);
}

void Stop(Fl_Widget * o, void * input)
{
    Fl::remove_timeout(callback);
    timestamp = 0 ;
}

void StepForward(Fl_Widget * o, void * input)
{
    Fl::remove_timeout(callback);
    timestamp++;
    imgbox->redraw_overlay();
}

void StepBackward(Fl_Widget * o, void * input)
{
    Fl::remove_timeout(callback);
    timestamp--;
    imgbox->redraw_overlay();
}

int GetLogsDir (vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(".")) == NULL) 
    {
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) 
    {
        string str(dirp->d_name);
        if(str.compare(0,4,"log-") ==0)
            files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

void SelectLog(Fl_Widget* o, void*)
{
    Fl::remove_timeout(callback);
    imgbox->redraw_overlay();

    Fl_Input_Choice  * in = (Fl_Input_Choice*) o;
    char filename[256];
    sprintf(filename,"./%s/blob_info_raw.log",in->value());
    vm.LoadFromFile(filename);
    timestamp = 0;

}
