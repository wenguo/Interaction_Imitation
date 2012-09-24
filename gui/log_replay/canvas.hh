#ifndef CANVAS_HH
#define CANVAS_HH

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Overlay_Window.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Input_Choice.H>

#include <list>

#include "imagebox.hh"

struct UserInput
{
    Fl_Value_Slider *sliders[9];
    Fl_Input_Choice *channel_selection;
    Fl_Input_Choice *client_selection;
};

class Canvas : public Fl_Overlay_Window
{
    public:
        Canvas(int w, int h, UserInput * input, const char * name); 
        void draw_overlay();
        int handle(int event);
        ~Canvas(){};
        int region_x1; //selection region
        int region_y1;
        int region_x2;
        int region_y2;

        int startx;
        int starty;

        int clicked;

        UserInput *user_input;

        static unsigned int timestamp;
        std::list<ImageBox*> imageboxes;

        void Snapshot(tm * timeinfo);
        bool Capture(tm *timeinfo);

        bool capturing;
        char logfolder[256];
};


#endif
