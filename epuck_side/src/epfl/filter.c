/*
 * filter.c
 *
 *  Created on: 5 Nov 2009
 *      Author: wliu
 */

#include "filter.h"
#include <math.h>

/*
   signal frequency: 32 Hz
   sampling frequency: 250Hz
   bandpass lowfrequency: 30Hz
   bandpass highfrequency: 35Hz

   using following command to obtain the [b,a] coefficient in Matlab
   [b,a]=butter(1,[28/125 33/125])
   */

#define LENGTH 32 //rolling average windows size, must be the result of power(2,n)
#define SHIFT_LENGTH 5
#define K 14     //filter scalling
float af[3]={1,-1.2906,0.8816};
float bf[3]={0.0592,0,-0.0592};

#define NUM_IR 8


int32_t a[3]={0};  //have to use 32 integer to avoid overflow of multiple operation
int32_t b[3]={0};

static int16_t filterIn[NUM_IR][3]={0};
static int16_t filterOut[NUM_IR][3]={0};

static int16_t valueHist[NUM_IR][LENGTH]={0};
static char valPointer[NUM_IR]={0};
static int32_t result[NUM_IR]={0};


void init_filter()
{
  int i=0;
  for(i=0;i<3;i++)
  {
    a[i]=(int16_t)(af[i]* (1<<K));
    b[i]=(int16_t)(bf[i]* (1<<K));
  }
}

void reset_filter()
{
  int i=0;
  int j=0;

  for(i=0;i<NUM_IR;i++)
  {
    for(j=0;j<3;j++)
    {
      filterIn[i][j]=0;
      filterOut[i][j]=0;
    }
  }
}

int16_t filter(int16_t index, int16_t value)
{

  int64_t sum;	//32 bits data for accumulator


  filterIn[index][2] = filterIn[index][1];
  filterIn[index][1] = filterIn[index][0];
  filterIn[index][0] = value;

  filterOut[index][2] = filterOut[index][1];
  filterOut[index][1] = filterOut[index][0];

  sum = b[0] * filterIn[index][0]  + b[1] * filterIn[index][1] + b[2] * filterIn[index][2] - a[1] * filterOut[index][1] - a[2]* filterOut[index][2]; //b[1] is always 0, so emit it

  //rescale
  filterOut[index][0] = (int16_t) (sum >> K);
  return filterOut[index][0];
}

int16_t rollingAvg(int16_t index, int16_t value)
{

  int16_t retVal;

  int16_t absvalue;
  //get absolute value
  absvalue = value > 0 ? value : -value;

  //take away the old value and put the new one
  result[index] = result[index] - valueHist[index][valPointer[index]] + absvalue;
  valueHist[index][valPointer[index]] =  absvalue;
  valPointer[index]++;
  if(valPointer[index]>=LENGTH)
    valPointer[index] = 0;
  retVal = (int16_t)(result[index] >> SHIFT_LENGTH); //using shift instead of division operator, pow(2,6)=64 -- the length of the window
  return retVal;
}
