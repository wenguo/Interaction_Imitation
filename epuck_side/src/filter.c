/*
 * filter.c
 *
 *  Created on: 5 Nov 2009
 *      Author: wliu
 */

#include "filter.h"
#include "support.h"
#include "ir.h"
#include <math.h>
#include <stdint.h>

/*
   signal frequency: 32 Hz
   sampling frequency: 250Hz
   bandpass lowfrequency: 30Hz
   bandpass highfrequency: 35Hz

   using following command to obtain the [b,a] coefficient in Matlab
   [b,a]=butter(1,[30/125 35/125])
   */

#define LENGTH 32 //rolling average windows size, must be the result of power(2,n)
#define SHIFT_LENGTH 5
#define K 14     //filter scalling
float af[3]={1,-1.2906,0.8816};
float bf[3]={0.0592,0,-0.0592};


int16_t a[3]={0};  //have to use 32 integer to avoid overflow of multiple operation
int16_t b[3]={0};

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

  int16_t sum[2];	//32 bits data for accumulator


  filterIn[index][2] = filterIn[index][1];
  filterIn[index][1] = filterIn[index][0];
  filterIn[index][0] = value;

  filterOut[index][2] = filterOut[index][1];
  filterOut[index][1] = filterOut[index][0];

  //clear the hardware accumulator
  RESLO=0;
  RESHI=0;

  //use hardware multiplier to calculate the output
  MACS = b[0];
  OP2 = filterIn[index][0];
  MACS = b[1];
  OP2 = filterIn[index][1];
  MACS = b[2];
  OP2 = filterIn[index][2];
  MACS = -a[1];
  OP2 = filterOut[index][1];
  MACS = -a[2];
  OP2 = filterOut[index][2];

  sum[0] = RESLO;
  sum[1] = RESHI;

  //rescale
  filterOut[index][0] = (int16_t) ((*((int32_t*)sum)) >> K);
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

/*
   signal frequency: 20 Hz
   sampling frequency: 250Hz
   bandpass lowfrequency: 16Hz
   bandpass highfrequency: 25Hz

   using following command to obtain the [b,a] coefficient in Matlab
   [b,a]=butter(1,[60/125 70/125])
   */
//////////////////////below for testing
#define LENGTH1 32 //rolling average windows size, must be the result of power(2,n)
#define SHIFT_LENGTH1 5
#define K1 14      //filter scalling
float af1[3]={1,0.1124,0.7757};
float bf1[3]={0.1122,0,-0.1122};

int16_t a1[3]={0};
int16_t b1[3]={0};

static int16_t filterIn1[NUM_IR][3]={0};
static int16_t filterOut1[NUM_IR][3]={0};

static int16_t valueHist1[NUM_IR][LENGTH1]={0};
static char valPointer1[NUM_IR]={0};
static int32_t result1[NUM_IR]={0};

void init_filter1()
{
  int i=0;
  for(i=0;i<3;i++)
  {
    a1[i]=(int16_t)(af1[i]*(1<<K1));
    b1[i]=(int16_t)(bf1[i]*(1<<K1));
  }
}

void reset_filter1()
{
  int i=0;
  int j=0;

  for(i=0;i<NUM_IR;i++)
  {
    for(j=0;j<3;j++)
    {
      filterIn1[i][j]=0;
      filterOut1[i][j]=0;
    }
  }
}

int16_t filter1(int16_t index, int16_t value) {

  int16_t sum1[2]; //64 bits data for accumulator

  filterIn1[index][2] = filterIn1[index][1];
  filterIn1[index][1] = filterIn1[index][0];
  filterIn1[index][0] = value;

  filterOut1[index][2] = filterOut1[index][1];
  filterOut1[index][1] = filterOut1[index][0];

  //clear the hardware accumulator
  RESLO=0;
  RESHI=0;

  //use hardware multiplier to calculate the output
  MACS = b1[0];
  OP2 = filterIn1[index][0];
  MACS = b1[1];
  OP2 = filterIn1[index][1];
  MACS = b1[2];
  OP2 = filterIn1[index][2];
  MACS = -a1[1];
  OP2 = filterOut1[index][1];
  MACS = -a1[2];
  OP2 = filterOut1[index][2];

  sum1[0] = RESLO;
  sum1[1] = RESHI;
  //rescale
  filterOut1[index][0] = (int16_t) ((*(int32_t*)sum1) >> K1);
  return filterOut1[index][0];
}

int16_t rollingAvg1(int16_t index, int16_t value)
{

  int16_t retVal;

  int16_t absvalue;

  //get absolute value
  absvalue = value > 0 ? value : -value;

  //take away the old value and put the new one
  result1[index] = result1[index] - valueHist1[index][valPointer1[index]] + absvalue;
  valueHist1[index][valPointer1[index]] =  absvalue;
  valPointer1[index]++;
  if(valPointer1[index]>=LENGTH1)
    valPointer1[index] = 0;
  retVal = (int16_t)(result1[index] >>SHIFT_LENGTH1); //using shift instead of division operator, pow(2,6)=64 -- the length of the window*/
  return retVal;
}
