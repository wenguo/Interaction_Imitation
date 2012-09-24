#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Overlay_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Image.H>

#include "imagebox.hh"
#include "canvas.hh"

using namespace std;

unsigned int Canvas::timestamp = 0;
const Fl_Color colors[MAX_COLORS_TRACKED]={FL_RED, FL_GREEN};


Canvas::Canvas(int w, int h, UserInput * input, const char * name): 
    Fl_Overlay_Window(w,h, name),
    region_x1(0),
    region_y1(0),
    region_x2(0),
    region_y2(0),
    clicked(0)
{
    int startx = 10;
    int starty = 10;
    int gapx = 1;
    int gapy = 1;
    imageboxes.push_back(new ImageBox(this,startx, starty, 5000));
    imageboxes.push_back(new ImageBox(this,startx+gapx+320, starty, 5001));
    imageboxes.push_back(new ImageBox(this,startx, starty+gapy+240, 5002));
    imageboxes.push_back(new ImageBox(this,startx+gapx+320, starty+gapy+240, 5003));

    capturing = false;

    user_input = input;

};


void Canvas::draw_overlay()
{
    fl_color(FL_BLACK);
    fl_rect(8,8,645,485); // image display region
    fl_rect(10,500,640,80); //button region
    char str[64];
    printf("...");
    fflush(stdout);

    std::list<ImageBox*>::iterator it;
    for(it=imageboxes.begin();it!=imageboxes.end();it++)
    {
        fl_rect((*it)->startx, (*it)->starty, (*it)->img_width, (*it)->img_height);
              {
            fl_draw_image((*it)->img_rgb_buffer, (*it)->startx, (*it)->starty, (*it)->img_width, (*it)->img_height);
            fl_color(FL_RED);
            fl_draw((*it)->name,(*it)->startx + 20, (*it)->starty+20);
            char timestring[64];
            sprintf(timestring, "%d.%d", (int)(*it)->frame.hdr.timestamp.tv_sec, (int)(*it)->frame.hdr.timestamp.tv_usec);
            fl_draw(timestring,(*it)->startx + 250, (*it)->starty+20);
            fl_color(FL_BLACK);

            int orig_x = (*it)->startx+ (*it)->img_width/2;
            int orig_y = (*it)->starty + (*it)->img_height/2;


            for(int i=0;i<MAX_COLORS_TRACKED;i++)
            {
                for(int j=0;j<(*it)->blob_info[i].num_blobs;j++)
                {
                    blob_rect * blob = &(*it)->blob_info[i].blobs[j];
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
                    sprintf(str, "%d", blob->id);
                    fl_color(FL_YELLOW);
                    fl_draw(str,blob->offset.x + orig_x, blob->offset.y + orig_y);
                    fl_color(FL_BLACK);
                }
            }
        }

    }

}

//event handler
int Canvas::handle(int event)
{
    Fl_Window::handle(event);
    switch(event)
    {
        case FL_MOVE:
            break;
        case FL_PUSH:
            break;
        case FL_RELEASE:
            break;
        default:
            break;
    }

    return 1;

}


void Canvas::Snapshot(tm * timeinfo)
{
    std::list<ImageBox*>::iterator it;
    for(it = imageboxes.begin();it!= imageboxes.end();it++)
        (*it)->Snapshot(timestamp);
}

bool Canvas::Capture(tm * timeinfo)
{
    if(capturing)
        return false;

    return true;

}
