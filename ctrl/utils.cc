#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.hh"


double simple_normal_deviate( double mean, double stddev )
{
    double x = 0.0;

    for ( int i = 0; i < 12; i++ )
        x += rand() / (RAND_MAX + 1.0);

    return ( stddev * (x - 6.0) + mean );
}

string convBase(uint16_t v, long base)
{
    string digits = "0123456789abcdef";
    string result;
    if ((base < 2) || (base > 16))
    {
       result = "Error: base out of range.";
    }
    else
    {
       do
       {
         result = digits[v % base] + result;
         v /= base;
       }
       while (v);
    }
    return result;
}

Hist::Hist(uint8_t s )
{
    sum = 0;
    size = s;
    valPointer = 0;
    valueHist = new int[size];
    memset(valueHist, 0, sizeof(int)*size);
}

Hist::~Hist()
{
    if(valueHist)
        delete []valueHist;
}

void Hist::Reset()
{
    sum = 0;
    valPointer = 0;
    memset(valueHist, 0, sizeof(int)*size);
}

void Hist::Resize(uint8_t s)
{
    if(valueHist)
        delete []valueHist;

    sum = 0;
    size = s;
    valPointer = 0;
    valueHist = new int[size];
    memset(valueHist, 0, sizeof(int)*size);

}

void Hist::Push(int value)
{
    sum = sum - valueHist[valPointer] + value;
    valueHist[valPointer] = value;
    valPointer++;
    if (valPointer >= size)
        valPointer = 0;
}

void Hist::Print()
{
    if(valueHist==NULL)
        printf("empty hist buffer!\n");
    else
    {
        printf("Hist: %ld ", sum);
        for(int i=0;i<size;i++)
        {
            printf("%d", valueHist[i]);
        }
        printf("\n");
    }
}
void PrintBuffer(uint8_t *data, int size)
{
    int i;
    printf(" -- buffer:");
    if(!data)
        printf("empty!");
    else
    {
        for(i=0; i<size; i++)
            printf("%#x\t", data[i]);
    }
    printf("\n");
}
