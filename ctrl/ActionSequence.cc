#include "ActionSequence.hh"
#include <stdio.h>
#include <string.h>

int g_sensor_triggered_threshold(30);
int g_sensor_triggered_min_interval(50);
int g_sensor_triggered_counts(4);

ActionSequence::ActionSequence(const char * str, int lspeed, int rspeed, int d, int s)
{
    leftspeed = lspeed;
    rightspeed = rspeed;
    duration = d;
    sensor_triggered = s;

    lapsed_time = 0;
    num_sensor_triggered = 0;
    last_triggered_time = 0;

    triggered_hist = new Hist(8);

    if(str!=NULL)
        name=strdup(str);

    if(d <=0 && s<=0)
        printf("please check perception conditions");
    else
        printf("create action sequence: %s %d %d %d %d\n", name, leftspeed, rightspeed, duration, sensor_triggered);
}

ActionSequence::~ActionSequence()
{
    printf("Destroy ActionSequence\n");
    if(name!=NULL) 
    {
        free(name);
    }
    if(triggered_hist!=NULL)
    {	
        delete triggered_hist;
    }
}



bool ActionSequence::Update(int proximity1, int proximity2)
{
    lapsed_time++;

    if(duration <= 0)
    {
        //do nothing
        if(sensor_triggered>0)
        {
            //monitor number of triggered times (windows size 8)
            if(proximity1 >= g_sensor_triggered_threshold || proximity2 >= g_sensor_triggered_threshold)
                triggered_hist->Push(1);
            else
                triggered_hist->Push(0);

            if(triggered_hist->Sum() > g_sensor_triggered_counts)
            {
                if(last_triggered_time ==0 || lapsed_time - last_triggered_time > g_sensor_triggered_min_interval)
                {
                    last_triggered_time = lapsed_time;
                    num_sensor_triggered++;
                    if(num_sensor_triggered >= sensor_triggered)
                        return true;
                }
            }
            triggered_hist->Print();
        }

    }
    else
    {
        if(lapsed_time >= duration)
            return true;
    }

    return false;
}

ActionSequenceList::ActionSequenceList()
{
    front = NULL;
    back = NULL;
}
ActionSequenceList::~ActionSequenceList()
{
    printf("Destroy ActionSequenceList\n");
}

void ActionSequenceList::Push_Back(ActionSequence* seq)
{
    printf("Push back\n");
    Node * node = new Node;
    node->as = seq;
    node->next = NULL;
    if(front==NULL)
    {
        front = node;
        back = node;
    }
    else
    {
        back->next = node;
        back = node;
    }

}

void ActionSequenceList::Pop_Front()
{
    printf("Pop front\n");
    if(front != NULL)
    {
        Node * next = front->next;
        if(front == back)
            back = NULL;
        delete front;
        front = next;
    }

}

bool ActionSequenceList::Empty()
{
    return front == NULL;
}
