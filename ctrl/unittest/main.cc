#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <sys/time.h>
#include <map>
#include <memory>
#include "ActionSequence.hh"
#include "VisualMemory.hh"
#include "utils.hh"
#include <iostream>
template<typename T>
struct track_alloc : std::allocator<T> {
    typedef typename std::allocator<T>::pointer pointer;
    typedef typename std::allocator<T>::size_type size_type;

    template<typename U>
        struct rebind {
            typedef track_alloc<U> other;
        };

    track_alloc() {}

    template<typename U>
        track_alloc(track_alloc<U> const& u)
        :std::allocator<T>(u) {}

    pointer allocate(size_type size, 
            std::allocator<void>::const_pointer = 0) {
        void * p = std::malloc(size * sizeof(T));
        if(p == 0) {
            throw std::bad_alloc();
        }
        return static_cast<pointer>(p);
    }

    void deallocate(pointer p, size_type) {
        std::free(p);
    }
};

typedef std::map< void*, std::size_t, std::less<void*>, 
        track_alloc< std::pair<void* const, std::size_t> > > track_type;

struct track_printer {
    track_type * track;
    track_printer(track_type * track):track(track) {}
    ~track_printer() {
        track_type::const_iterator it = track->begin();
        while(it != track->end()) {
            std::cerr << "TRACK: leaked at " << it->first << ", "
                << it->second << " bytes\n";
            ++it;
        }
    }
};

track_type * get_map() {
    // don't use normal new to avoid infinite recursion.
    static track_type * track = new (std::malloc(sizeof *track)) 
        track_type;
    static track_printer printer(track);
    return track;
}

void * operator new(std::size_t size) throw(std::bad_alloc) {
    // we are required to return non-null
    void * mem = std::malloc(size == 0 ? 1 : size);
    if(mem == 0) {
        throw std::bad_alloc();
    }
    (*get_map())[mem] = size;
    return mem;
}

void operator delete(void * mem) throw() {

    if(get_map()->erase(mem) == 0) {
        // this indicates a serious bug
        std::cerr << "bug: memory at " 
            << mem << " wasn't allocated by us\n";
    }
    std::free(mem);
}


void testVisualMemory();
void testActionSequence();
void testList();
void testTime();
void testObject();
void testTrajectory();

int main(int argc, char **argv)
{
   //testTrajectory();
    //    testObject();
    	testVisualMemory();
    //	testList();
    //	testTime();

}

void testVisualMemory()
{
    Blob_info *blob1[6];
    blob1[0] = new Blob_info(-5, 4, 10,10,1,34, 0);
    blob1[1] = new Blob_info(5, -4, 10,10,1,34, 0);
    blob1[2] = new Blob_info(-3, 4, 10,10,1,46, 0);
    blob1[3] = new Blob_info(3, -4, 10,10,1,46, 0);
    blob1[4] = new Blob_info(-1, 4, 10,10,1,52, 0);
    blob1[5] = new Blob_info(1, -4, 10,10,1,52, 0);
    Blob_info *blob2[6];
    blob2[0] = new Blob_info(-5, 3, 10,10,1,34, 1);
    blob2[1] = new Blob_info(5, -3, 10,10,1,34, 1);
    blob2[2] = new Blob_info(-3, 3, 10,10,1,46, 1);
    blob2[3] = new Blob_info(3, -3, 10,10,1,46, 1);
    blob2[4] = new Blob_info(-1, 3, 10,10,1,52, 1);
    blob2[5] = new Blob_info(1, -3, 10,10,1,52, 1);

    
    Blob_info *blob[12];
    blob[0] = new Blob_info(-5, 4, 10,10,1,34, 0);
    blob[1] = new Blob_info(5, -4, 10,10,1,34, 0);
    blob[2] = new Blob_info(-5, 3, 10,10,1,34, 1);
    blob[3] = new Blob_info(5, -3, 10,10,1,34, 1);
    blob[4] = new Blob_info(-3, 4, 10,10,1,46, 0);
    blob[5] = new Blob_info(3, -4, 10,10,1,46, 0);
    blob[6] = new Blob_info(-3, 3, 10,10,1,46, 1);
    blob[7] = new Blob_info(3, -3, 10,10,1,46, 1);
    blob[8] = new Blob_info(-1, 4, 10,10,1,52, 0);
    blob[9] = new Blob_info(1, -4, 10,10,1,52, 0);
    blob[10] = new Blob_info(-1, 3, 10,10,1,52, 1);
    blob[11] = new Blob_info(1, -3, 10,10,1,52, 1);

    VisualMemory vm(320, 240);
    VisualMemory vm1(320, 240);

    for(int i=0;i<6;i++)
    {
        vm.AddTrackingData(*blob1[i]);
 //       vm.AddTrackingData(*blob2[i]);
    }
/*
    for(int i=0;i<12;i++)
    {
        vm1.AddTrackingData(*blob[i]);
    }
    vm.Print();
    vm1.Print();

   // vm.Log();

    std::cout<<vm.GetLatestAveragedBlobInfo(1, 1)<<std::endl;
    printf(" ---- object 0, channel 1 ---- \n");
    std::cout<<vm.GetLatestAveragedBlobInfo(1,0,1)<<std::endl;
    printf(" ---- object 1, channel 1 ---- \n");
    std::cout<<vm.GetLatestAveragedBlobInfo(1,1,1)<<std::endl;
    printf(" ---- object 0, channel 0 ---- \n");
    std::cout<<vm.GetLatestAveragedBlobInfo(1,0,0)<<std::endl;
    printf(" ---- object 1, channel 0 ---- \n");
    std::cout<<vm.GetLatestAveragedBlobInfo(1,1,0)<<std::endl;
    */
    for(int i=0;i<6;i++)
        delete blob1[i];

    for(int i=0;i<6;i++)
        delete blob2[i];
    for(int i=0;i<12;i++)
        delete blob[i];
}

void testActionSequence()
{

    ActionSequence * current_action_seq = NULL;
    ActionSequenceList  greetingA;

    //go straight
    ActionSequence * as = new ActionSequence("Forward",300,300,20, 0);
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
    as = new ActionSequence("Forward",300,300,20,0);
    greetingA.Push_Back(as);
    //stop
    as = new ActionSequence("Stop",0,0,100,0);
    greetingA.Push_Back(as);

    Hist hist(8);

    int count=0;
    while(1)
    {
        usleep(100000);

        if(count++%3==0)
            hist.Push(0);
        else
            hist.Push(1);
        hist.Print();
        if(current_action_seq == NULL)
        {
            if(!greetingA.Empty())
            {
                current_action_seq = greetingA.Front();
                greetingA.Pop_Front();

                printf(" ---- Select new action sequence ----- %s \n", current_action_seq->Name());

            }
            else
            {
                printf("all action sequence done\n");
                break;
            }
        }
        else
        {
            if(current_action_seq->Update(0,0)==true)
            {
                printf("remove finished action \n");
                delete current_action_seq;
                current_action_seq = NULL;
            }
        }
    }


}

void testList()
{
    list<int> mylist;
    for (int i=1; i<=5; i++) mylist.push_back(i);

    cout << "mylist contains:";
    list<int>::reverse_iterator rit;
    for ( rit=mylist.rbegin() ; rit != mylist.rend(); rit++ )
        cout << " " << *rit;

    cout << endl;
}

void testTime()
{
    timeval sys_time, starttime;
    gettimeofday(&starttime, NULL);
    for(int i=0;i<10;i++)
    {
        usleep(100000);
        gettimeofday(&sys_time, NULL);
        int time=(sys_time.tv_sec - starttime.tv_sec)*1000 +  sys_time.tv_usec/1000;
        printf("%ld %ld -- %ld %ld -- %d\n", sys_time.tv_sec, sys_time.tv_usec, (sys_time.tv_sec- starttime.tv_sec) * 1000, sys_time.tv_usec/1000,time);
    }
}


void testObject()
{
    Object obj;
    obj.LoadRecordsFromFile("object", 0);
    obj.Print();
    obj.LoadRecordsFromFile("object", 1);
    obj.Print();
}

void testTrajectory()
{
    FILE * fp = fopen("blob_info_raw_input.log", "r");
    int n, x,y,w,h,ts,sys_ts,ch;
    VisualMemory *vm=new VisualMemory(320, 240);
    if(fp)
    {
        char line[256];
        while(fgets(line, 256, fp))
        {
            n=sscanf(line, "%d %d %d %d %d %d %d", &x,&y,&w,&h,&ts,&sys_ts,&ch);
            if(n==7)
            {
                vm->AddTrackingData(Blob_info(x,y,w,h,ts,sys_ts,ch));
            }
        }
    }
    else
        printf("failed to open file\n");

    delete vm;

}
