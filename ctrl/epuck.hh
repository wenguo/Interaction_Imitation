#ifndef EPUCK_H
#define EPUCH_H

#include <stdint.h>
#include <list>

#include "capture.h"
#include "cmvision.h"
#include "global.h"
#include "ActionSequence.hh"
#include "VisualMemory.hh"

#include "bytequeue.h"
#include "lolmsg.h"
#include "ipc.hh"

#define NUM_IRS	8               //number of ir proximity sensor
#define NUM_BLOB_CHANNELS               3
#define MAX_OBJECTS_TRACKED             3


enum fsm_state_t{OBSERVING=0, GREETINGA,GREETINGB, SEARCHING, RANDOMWALK, SIGNALLING, BYEBYE, UNKNOWN_STATE, STATE_COUNT};

enum role_t{OBSERVER, ACTOR_A, ACTOR_B, UNKNOWN_ROLE};

class Robot
{
    public:
        Robot(const char * n = NULL);
        ~Robot();
        bool Initialise();
        bool Update(uint64_t timestamp);
        bool Stop();
        bool Reset();
        void Log();

        void InitGreetingA();
        void InitGreetingB();

        void Avoidance();
        void GreetingA();
        void GreetingB();
        void Observing();
        void RandomWalk();
        void Searching();
        void Signalling();
        void ByeBye();


        void SetSpeed(int lspeed, int rspeed);
        void SetLED(bool on);
        void SetLED(uint8_t leds, bool on=true);
        void SetIRPulse(uint8_t pulses, bool on=true);
        void SetIRPulse(bool on=true);
        void PrintProximity();
        void PrintStatus();

        static void * SPIComm(void * ptr);
        static void * BlobDetection(void *ptr);
        static void * Monitor(void *ptr);

    private:
        fsm_state_t current_state, last_state, previous_state;
        role_t role;

        char *name;
        int proximity[NUM_IRS];
        int proximity_filtered[NUM_IRS];
        Blob_info blob_data[MAX_OBJECTS_TRACKED];
        unsigned char bumped;


        ActionSequence * current_action_seq;
        ActionSequenceList  greetingA;
        ActionSequenceList  greetingB;


        int searching_object_id;

        //std::list<ActionSequence *> greetingA;
        //std::list<ActionSequence *> greetingB;
        //std::list<ActionSequence*>::iterator action_seq_index;

        int randomwalk_count;

        uint32_t timestamp;


        pthread_t spi_thread;
        pthread_t vision_thread;
        static pthread_mutex_t spi_mutex;
        static pthread_cond_t spi_cond;
        static pthread_mutex_t vision_mutex;
        static pthread_cond_t vision_cond;

        int spi_device;

        Capture cap;
        CMVision vision;
        const Capture::Image *img;
        RawImageFrame frame;
        int img_width;
        int img_height;
        Hist blob_hist;

        VisualMemory *vm;

        bool subscribed;
	
        IPC::IPC *subscriptionIPC;
	IPC::IPC *monitoringIPC;
	static void Subscribe(const LolMessage*msg, void *ptr);
	static void Monitoring(const LolMessage*msg, void *ptr);


};

void addBlob(int x1, int y1, int x2, int y2, unsigned char * img, int width, int height, rgb color);

#endif
