#ifndef ACTIONSEQUENCE_HH
#define ACTIONSEQUENCE_HH

#include "utils.hh"
#include <stdlib.h>
#include <stdio.h>

class ActionSequence
{
    public:
        ActionSequence(const char * str, int leftspeed, int rightspeed, int duration, int num_sensor_triggered);
        ~ActionSequence();
        bool Update(int proximity1, int proximity2=0);
        inline int LeftSpeed() {return leftspeed;}
        inline int RightSpeed() {return rightspeed;}
		const char* Name() {return name;}

    private:
		char *name;
        //speed
        int leftspeed;
        int rightspeed;
        //perception condition
        int duration;
        int sensor_triggered;

        
        //current condition
        int num_sensor_triggered;
        int last_triggered_time;
        int lapsed_time;
        Hist *triggered_hist;

};

class ActionSequenceList
{
	
	public:

		ActionSequenceList();
		~ActionSequenceList();

		class Node
		{
			public:
				Node(){as = NULL; next=NULL;};
				~Node()
				{
					printf("Destroy node\n");
				}
				ActionSequence * as;
				Node * next;
		};
		
		void Push_Back(ActionSequence*);
		void Pop_Front();
		bool Empty();
		ActionSequence* Front()
		{
			if(front)
				return front->as;
			else
				return NULL;
		}
	private:
		Node *front;
		Node *back;
		
};

#endif
