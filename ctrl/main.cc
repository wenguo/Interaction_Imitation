#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

#include "support.h"
#include "epuck.hh"
#include "args.hh"

#define ON 1
#define OFF 0

char * g_name("robot A");

uint32_t currentTime = 0;
uint32_t lastupdateTime = 0;

int userQuit = 0;
void signalHandler(int dummy);
void timerHandler(int dymmy);

void *stopRobot(void *ptr);

int main(int argc, char*argv[])
{
	parse_args(argc, argv);
	//set signal handler to capture "ctrl+c" event
	if (signal(SIGINT, signalHandler) == SIG_ERR)
	{
		printf("signal(2) failed while setting up for SIGINT");
		return -1;
	}

	if (signal(SIGTERM, signalHandler) == SIG_ERR)
	{
		printf("signal(2) failed while setting up for SIGTERM");
		return -1;
	}

	if (signal(SIGALRM, timerHandler)==SIG_ERR)
	{
		printf("signal(2) failed while setting up for SIGALRM");
		return -1;
	}

	Robot *robot=new Robot(g_name);
	if(!robot->Initialise())
	{
		printf("ERROR!!! Fail to initialise robot\n");
		return -1;
	}


	//creat thread  monitering button 1
	//pthread_t thread;
	//pthread_create(&thread,NULL,stopRobot,NULL);

	//set timer to be every 100 ms
	struct itimerval tick;
	memset(&tick, 0, sizeof(tick));
	tick.it_value.tv_sec = 0;
	tick.it_value.tv_usec = 100000;
	tick.it_interval.tv_sec = 0;
	tick.it_interval.tv_usec = 100000;

	//set timer
	if (setitimer(ITIMER_REAL, &tick, NULL))
	{
		printf("Set timer failed!!\n");
	}


	//main loop
	while (userQuit != 1)
	{
		//block until timer event occurs
		while(currentTime==lastupdateTime)
		{
			usleep(5000);
		}
		lastupdateTime = currentTime;
		//robot update
		robot->Update(currentTime);
	}
	printf("clean up\n");

	robot->Stop();

	usleep(1000000);

	robot->Log();

	delete robot;
	//stop robot
	//


	return 0;
}

void signalHandler(int dummy)
{
	printf("Ctrl+C captured, exit program!\n");
	// set_speed(fd,0,0);
	set_board_led(1, OFF);
	userQuit = 1;
}

void *stopRobot(void* ptr)
{
	printf("pthread is running\n");
	while(1)
	{
		userQuit=1;
	}
        return NULL;
}

void timerHandler(int dummy)
{
	currentTime++;
}
