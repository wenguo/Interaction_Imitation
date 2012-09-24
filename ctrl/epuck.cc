#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <math.h>


#include "spicomm.h"
#include "support.h"
#include "utils.hh"
#include "global.h"
#include "epuck.hh"


using namespace std;

int g_logtofile(0);
int g_turning_speed(10);
extern int userQuit;
extern char * g_host;


#ifdef LAPTOP
#define PIXEL_FORMAT V4L2_PIX_FMT_YUYV
const char *video_device = "/dev/video0";
#else
#define PIXEL_FORMAT V4L2_PIX_FMT_UYVY
const char *video_device = "/dev/video1";
#endif
const char *color_filename = "../colors.txt";
const char *state_name[STATE_COUNT]={"Observing", "GreetingA", "GreetingB", "Searching", "RandomWalk", "Signalling", "ByeBye", "Unknown"};

const int avoid_weightleft[8] ={ -10, -10, -5, 0, 0, 5, 10, 10};
const int avoid_weightright[8] = {10, 10, 5, 0, 0, -5, -10, -10};

pthread_mutex_t Robot::spi_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Robot::spi_cond =PTHREAD_COND_INITIALIZER;
pthread_mutex_t Robot::vision_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t Robot::vision_cond =PTHREAD_COND_INITIALIZER;


Robot::Robot(const char * str)
{
    cout<<"Create robot "<<endl;

    bumped = 0;
    randomwalk_count = 0;

    img_width=320;
    img_height=240;

    searching_object_id = -1;

    for (int i = 0;i < NUM_IRS;i++)
        proximity[i] = 0;

    current_action_seq = NULL;

    if(str!=NULL)
        name = strdup(str);
    else
        name = NULL;

    if(name !=NULL)
    {
        if(strcmp(name, "robot A")==0)
        {
            this->role = ACTOR_A;
            InitGreetingA();
            this->current_state = SEARCHING;
            this->last_state = SEARCHING;
        }
        else if(strcmp(name, "robot B")==0)
        {
            this->role = ACTOR_B;
            InitGreetingB();
            this->current_state = SEARCHING;
            this->last_state = SEARCHING;
        }
        else if(strcmp(name, "robot C")==0)
        {
            this->role = OBSERVER;
            this->current_state = OBSERVING;
            this->last_state = OBSERVING;
        }
        else
        {
            this->role = UNKNOWN_ROLE;
            this->current_state = UNKNOWN_STATE;
            this->last_state = UNKNOWN_STATE;
        }
    }
    else
    {
        this->role = UNKNOWN_ROLE;
        this->current_state = UNKNOWN_STATE;
        this->last_state = UNKNOWN_STATE;
    }

    frame.hdr.type = RawImageFrame::ImageTypeRawYUV;
    frame.hdr.width = img_width;
    frame.hdr.height = img_height;

    vm = new VisualMemory(img_width, img_height);

//init parse buffer
    subscribed = false;
}

Robot::~Robot()
{
    cout<<"Destroy robot "<<endl;
    if(name!=NULL)
        free(name);
    if(vm!=NULL)
        delete vm;
}

bool Robot::Initialise()
{
    cout<<"Init "<<endl;

#ifndef LAPTOP
    //init spi
    spi_device = init_spi();

    if(spi_device == -1)
    {
        printf("Fail to initialise SPI interface, exit\n");
        return false;
    }

#endif
    //init vision
    int trial = 0;
    while(!cap.init(video_device,1,img_width,img_height,PIXEL_FORMAT))
    {
#ifndef LAPTOP
        printf("Error initializing camera");
        system("modprobe -r poX030");
        system("modprobe -r atmel_isi");
        system("modprobe  poX030");
#endif
        if(trial++ >=3)
        {
            printf("no success to load the camera driver, quit the program\n");
            return false;
        }
    }


    if(!vision.initialize(img_width, img_height))
    {
        printf("Error initializing vision");
        return false;
    }
    if(!vision.loadOptions(color_filename))
    {
        printf("Error loading color file");
        return false;
    }


    pthread_create(&spi_thread, NULL, SPIComm, this);
    pthread_create(&vision_thread, NULL, BlobDetection, this);

    //init network
  //  pthread_create(&monitor_thread, NULL, Monitor, this);
    subscriptionIPC = new IPC::IPC();
    subscriptionIPC->SetCallback(Subscribe, this);
    subscriptionIPC->Start(g_host, PORT_SERVER, false);
    char hostname[64];
    gethostname(hostname,64);
    subscriptionIPC->SendData(REQ_SUBSCRIPTION, (uint8_t*)hostname, strlen(hostname));

    return true;

}

bool Robot::Stop()
{
    cout<<"Robot stopped "<<endl;
    SetSpeed(0,0);
    blinkLEDs(0xFF,0);
    SetIRPulse(0xF,false);

    pthread_mutex_lock(&spi_mutex);
    pthread_cond_signal( &spi_cond );
    pthread_mutex_unlock(&spi_mutex);

    return true;
}

bool Robot::Reset()
{
    cout<<"Robot reset "<<endl;
    reset_robot(spi_device);

    pthread_mutex_lock(&spi_mutex);
    pthread_cond_signal( &spi_cond );
    pthread_mutex_unlock(&spi_mutex);
    return true;
}

void Robot::InitGreetingA()
{
    //Action A
    //go straight
    ActionSequence * as = new ActionSequence("Forward",300,300,0, 1);
    greetingA.Push_Back(as);
    //stop
    as = new ActionSequence("Stop",0,0,30,0);
    greetingA.Push_Back(as);
    //reverse
    as = new ActionSequence("Reverse",-300,-300,50,0);
    greetingA.Push_Back(as);
    //stop
    as = new ActionSequence("Stop",0,0,30,0);
    greetingA.Push_Back(as);
    //forward
    as = new ActionSequence("Forward",300,300,0,1);
    greetingA.Push_Back(as);
    //stop
    as = new ActionSequence("Stop",0,0,100,0);
    greetingA.Push_Back(as);

}

void Robot::InitGreetingB()
{
    //Action B
    //wait until triggered twice
    ActionSequence *as = new ActionSequence("Waiting",0,0,0,2);
    greetingB.Push_Back(as);
    //stop
    as = new ActionSequence("Stop",0,0,30,0);
    greetingB.Push_Back(as);
    //reverse
    as = new ActionSequence("Reverse",-300,-300,50,0);
    greetingB.Push_Back(as);
    //stop
    as = new ActionSequence("Stop",0,0,30,0);
    greetingB.Push_Back(as);
    //forward
    as = new ActionSequence("Forward",300,300,0,1);
    greetingB.Push_Back(as);
    //stop
    as = new ActionSequence("Stop",0,0,10,0);
    greetingB.Push_Back(as);

}

bool Robot::Update(uint64_t ts)
{

    //	blob_data[0] = vm->GetLatestAveragedBlobInfo(ts, 0, 0);
    //	blob_data[0].Print();

    if(role == OBSERVER)
    {
        switch (current_state)
        {
            case OBSERVING:
                Observing();
                break;
            default:
                break;
        }

    }
    else if(role == ACTOR_A)
    {
        switch (current_state)
        {
            case GREETINGA:
                GreetingA();
                break;
            case SEARCHING:
                Searching();
                break;
            case RANDOMWALK:
                RandomWalk();
                break;
            case SIGNALLING:
                Signalling();
                break;
            case BYEBYE:
                ByeBye();
                break;
            default:
                break;
        }

    }
    else if(role == ACTOR_B)
    {
        switch (current_state)
        {
            case GREETINGB:
                GreetingB();
                break;
            case SEARCHING:
                Searching();
                break;
            case SIGNALLING:
                Signalling();
                break;
            case BYEBYE:
                ByeBye();
                break;
            default:
                break;
        }
    }
    else
    {
        Avoidance();
    }

    timestamp = ts;
    pthread_mutex_lock(&spi_mutex);
    pthread_cond_signal( &spi_cond );
    pthread_mutex_unlock(&spi_mutex);

    //PrintProximity();
    //PrintStatus();

    return true; // run again
}

void Robot::SetSpeed(int lspeed, int rspeed)
{
#ifndef LAPTOP
    pthread_mutex_lock(&spi_mutex);
    setSpeed(lspeed, rspeed);
    pthread_mutex_unlock(&spi_mutex);
#endif

    //	printf("speed: (%d %d)\n",lspeed, rspeed);
}
void Robot::Avoidance()
{
    int leftwheel, rightwheel;

    leftwheel = 400;
    rightwheel = 400;

    for (int i = 0; i < NUM_IRS; i++)
    {
        leftwheel += avoid_weightleft[i] * (proximity[i]>>3);
        rightwheel += avoid_weightright[i] * (proximity[i]>>3);
    }


    leftwheel=0;
    rightwheel=0;

    if(timestamp == 100)
    {
        //SetLED(0xFF,true);
        SetIRPulse(0x1,true);
        //SetIRPulse(true);
    }
    //  if(timestamp == 3000)
    //      SetLED(false);



    SetSpeed(leftwheel, rightwheel);
}

void Robot::GreetingA()
{
    if(current_action_seq == NULL)
    {
        if(!greetingA.Empty())
        {
            current_action_seq = greetingA.Front();
            greetingA.Pop_Front();
            SetSpeed(current_action_seq->LeftSpeed(), current_action_seq->RightSpeed());

        }
        else
        {
            if(blob_hist.Sum()>20 && blob_hist.Sum()<40)
            {

                SetLED(0xFF, true);
                current_state = BYEBYE;
                last_state = GREETINGA;
            }
        }
    }
    else
    {
        if(current_action_seq->Update(proximity_filtered[7])) 
        {
            printf("remove finished action \n");
            delete current_action_seq;
            current_action_seq = NULL;
        }
    }
}
void Robot::GreetingB()
{
    if(current_action_seq == NULL)
    {
        if(!greetingB.Empty())
        {
            current_action_seq = greetingB.Front();
            greetingB.Pop_Front();
            SetSpeed(current_action_seq->LeftSpeed(), current_action_seq->RightSpeed());

        }
        else
        {
            SetLED(0xFF, true);
            current_state = BYEBYE;
            last_state = GREETINGB;
        }
    }
    else
    {
        if(current_action_seq->Update(proximity_filtered[7]))
        {
            delete current_action_seq;
            current_action_seq = NULL;
        }
    }

}

void Robot::RandomWalk()
{
    SetSpeed(-300, -300);

    if(randomwalk_count++ > 90)
    {
        current_state = SEARCHING;
        last_state = RANDOMWALK;
    }

}

void Robot::Searching()
{
    std::list<Object*>::iterator it;
    std::list<Object*> objects = vm->Objects();
    Blob_info blob;


    bool matched = false;
    for(it= objects.begin();it!=objects.end();it++)
    {
        if((*it) && (*it)->id == searching_object_id)
        {
            matched = true;
            blob_data[0] = (*it)->GetLatestAveragedBlobInfo(timestamp, BODY);
            blob = (*it)->GetLatestAveragedBlobInfo(timestamp, LEDS);
            break;
        }
    }

    //not matched? try to search the biggest objects in list
    if(!matched)
    {
        if(!objects.empty())
        {
            blob_data[0] = objects.back()->GetLatestAveragedBlobInfo(timestamp,BODY);
            blob = objects.back()->GetLatestAveragedBlobInfo(timestamp, LEDS);
        }
        else
        {
            blob_data[0] = Blob_info();
            blob = Blob_info();
        }
    }

    blob_hist.Push(blob.size.x>=1 ? 1:0);
 //   blob_hist.Print();

    if(role == ACTOR_A)
    {
        //no blob found?
        if(blob_data[0].size.x<=1)
        {
            SetSpeed(2*g_turning_speed, -2*g_turning_speed);
        }
        else
        {
            if(fabs(blob_data[0].offset.x)>3)
                SetSpeed(g_turning_speed * sign(blob_data[0].offset.x), -g_turning_speed * sign(blob_data[0].offset.x));
            else
            {
                SetSpeed(0,0);
                if(blob_hist.Sum()>20 && blob_hist.Sum()<40)
                {
                    SetLED(0xFF, true);
                    SetIRPulse(0x1, true);
                    current_state = SIGNALLING;
                    last_state =  SEARCHING;
                }
            }
        }

    }
    else if(role == ACTOR_B)
    {
        //no blob found
        if(blob_data[0].size.x <=1)
        {
            SetSpeed(g_turning_speed, -g_turning_speed);
        }
        //blob at certain distance
        else if(blob_data[0].size.x > 50 && blob_data[0].size.x < 180)
        {
            if(fabs(blob_data[0].offset.x)>3)
            {
                SetSpeed(g_turning_speed * sign(blob_data[0].offset.x), -g_turning_speed * sign(blob_data[0].offset.x));
            }
            else
            {
                SetLED(0xFF, true);
                SetIRPulse(0x1, true);
                current_state = SIGNALLING;
                last_state = SEARCHING;
            }
        }
    }
}

void Robot::Signalling()
{
    SetSpeed(0, 0);

    std::list<Object*>::iterator it;
    std::list<Object*> objects = vm->Objects();
    Blob_info blob;

    bool matched = false;
    for(it= objects.begin();it!=objects.end();it++)
    {
        if((*it) && (*it)->id == searching_object_id)
        {
            matched = true;
            blob = (*it)->GetLatestAveragedBlobInfo(timestamp, LEDS);
            break;
        }
    }

    //not matched? try to search the biggest objects in list
    if(!matched)
    {
        if(!objects.empty())
            blob = objects.back()->GetLatestAveragedBlobInfo(timestamp,LEDS);
        else
            blob = Blob_info();
    }

    blob_hist.Push(blob.size.x>=1 ? 1:0);
 //   blob_hist.Print();


    if(role == ACTOR_A)
    {
        //if no signalling detected, start to greeting
        if(blob_hist.Sum() <= 0)
        {
            //		InitGreetingA();
            SetLED(0xFF, false);
            blob_hist.Reset();
            current_state = GREETINGA;
            last_state = SIGNALLING;
        }
    }
    else if(role == ACTOR_B)
    {
        //if detects synchronisation signalling, stop signalling and start to greeting
        if(blob_hist.Sum()>20)// && blob_hist.Sum()<40)
        {
            //InitGreetingB();
            SetLED(0xFF, false);
            blob_hist.Reset();
            current_state = GREETINGB;
            last_state = SIGNALLING;
        }
    }
}

void Robot::ByeBye()
{
    SetSpeed(0, 0);

    std::list<Object*>::iterator it;
    std::list<Object*> objects = vm->Objects();
    Blob_info blob;

    bool matched = false;
    for(it= objects.begin();it!=objects.end();it++)
    {
        if((*it) && (*it)->id == searching_object_id)
        {
            matched = true;
            blob = (*it)->GetLatestAveragedBlobInfo(timestamp, LEDS);
            break;
        }
    }

    //not matched? try to search the biggest objects in list
    if(!matched)
    {
        if(!objects.empty())
            blob = objects.back()->GetLatestAveragedBlobInfo(timestamp,LEDS);
        else
            blob = Blob_info();
    }

    blob_hist.Push(blob.size.x >= 1 ? 1 : 0);


    if(role == ACTOR_A)
    {
        //if no signalling detected, start to walkaway
        if(blob_hist.Sum() < 0)
        {
            SetLED(0xFF, false);
            SetIRPulse(0x1, false);
            blob_hist.Reset();
            randomwalk_count=0;
            current_state = RANDOMWALK;
            last_state = BYEBYE;
        }
    }
    else if(role == ACTOR_B)
    {
        //if detects synchronisation signalling, stop signalling and start to search again
        if(blob_hist.Sum()>20)// && blob_hist.Sum()<40)
        {
            SetLED(0xFF, false);
            SetIRPulse(0x1, false);
            blob_hist.Reset();
            current_state = SEARCHING;
            last_state = BYEBYE;
        }
    }
}


void Robot::Observing()
{
    //   printf("blob[0] -- %d %d\t", blob_data[0].offset_x, blob_data[0].offset_x);
    //   printf("blob[1] -- %d %d\n", blob_data[1].offset_x, blob_data[1].offset_x);
}

void Robot::SetLED(bool on)
{
    printf("BlinkLED %s %s\n", state_name[current_state], state_name[last_state]);
    pthread_mutex_lock(&spi_mutex);
    //setLEDs(0xFF, on);
    if(on)
        blinkLEDs(0xFF,5000);
    else
        blinkLEDs(0xFF,0);
    pthread_mutex_unlock(&spi_mutex);
}

void Robot::SetLED(uint8_t leds, bool on)
{
    printf("SetLED\n");
    pthread_mutex_lock(&spi_mutex);
    setLEDs(leds, on);
    pthread_mutex_unlock(&spi_mutex);

}

void Robot::SetIRPulse(bool on)
{
    printf("SetIRPulse %s %s\n", state_name[current_state], state_name[last_state]);
    SetIRPulse(0b1001, on);
}

void Robot::SetIRPulse(uint8_t pulse, bool on)
{
    printf("SetIRPulse\n");
    pthread_mutex_lock(&spi_mutex);
    setIRPulses(pulse, on);
    pthread_mutex_unlock(&spi_mutex);

}
//below defined functions for debugging
void Robot::PrintProximity()
{
    printf("%d:%s IR --[", this->timestamp, this->name);
    for (int i = 0;i < NUM_IRS;i++)
        printf(" %d", this->proximity[i]);
    printf("]\n");
    printf("%d:%s Proximity_filtered --[", this->timestamp, this->name);
    for (int i = 0;i < NUM_IRS;i++)
        printf(" %d", this->proximity_filtered[i]);
    printf("]\n");
}

void Robot::PrintStatus()
{
    printf("%d:%s in state [%s] (%d - %d)\n", this->timestamp,
            this->name, state_name[this->current_state], this->current_state, STATE_COUNT);
}

void Robot::Log()
{
    vm->Log();
}


void * Robot::SPIComm(void * ptr)
{
    printf("SPI comm thread is running\n");

    Robot *robot = (Robot*)ptr;

    while(1)
        //while(userQuit!=1)
    {
        pthread_mutex_lock(&spi_mutex);
        pthread_cond_wait( &spi_cond, &spi_mutex );
#ifndef LAPTOP
        update(robot->spi_device);
#endif
        get_ir_data(robot->proximity, NUM_IRS);
        get_proximity_filtered_data(robot->proximity_filtered, NUM_IRS);
        pthread_mutex_unlock(&spi_mutex);
    }
#ifndef LAPTOP
    update(robot->spi_device);
#endif

    printf("SPI comm thread is exiting\n");
    return NULL;
}

void *Robot::BlobDetection(void * ptr)
{
    printf("Blob detection thread is running\n");

    Robot *robot = (Robot*)ptr;
    static int count = 0;

    timeval starttime, sys_time;
    gettimeofday(&starttime, NULL);

    while(userQuit!=1)
    {
//#if !defined(LAPTOP) 
        count++;
        pthread_mutex_lock(&vision_mutex);
        robot->img = robot->cap.captureFrame();
        if(robot->img !=NULL)
        {
            robot->frame.hdr.timestamp = robot->img->timestamp;
            robot->frame.data = robot->img->data;
            robot->vision.processFrame(reinterpret_cast<image_pixel*>(robot->img->data));
            if(robot->timestamp %10 ==0)
            {
                //	printf("processed frame @ %d fps\n", count);
                count=0;
            }
        }
        robot->cap.releaseFrame(robot->img);

        gettimeofday(&sys_time, NULL);

        for(int ch=0;ch<MAX_COLORS_TRACKED;ch++)
        {
            rgb c = robot->vision.getColorVisual(ch);
            CMVision::region* reg = robot->vision.getRegions(ch);
            int index=0;

            while(reg)
            {
                robot->vm->AddTrackingData(reg->x1, reg->y1, reg->x2, reg->y2, robot->timestamp, (sys_time.tv_sec - starttime.tv_sec)*1000 + sys_time.tv_usec/1000 , ch);
                reg = reg->next;
                index++;
                if(index >= MAX_OBJECTS_TRACKED) 
                    break;
            }
        }

        pthread_mutex_unlock(&vision_mutex);
//#endif
    }

    printf("Blob detection thread is exiting\n");
    return NULL;
}

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


