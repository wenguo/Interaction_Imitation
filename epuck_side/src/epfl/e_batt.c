#include "math.h"
#include "e_batt.h"
#include "e_ad_conv.h"
#include "e_epuck_ports.h"
#include "e_led.h"
#include <stdlib.h>

extern int e_battery[BATT_SAMP_NB];
extern unsigned int e_last_batt_scan_id;

int e_get_batt()
{
   return e_battery[0];
}

int e_read_batt()
{ 
   long sum = 0;
   int i=0;
   for(i=0;i<BATT_SAMP_NB;i++)
	sum += e_battery[i];
   return sum / BATT_SAMP_NB;
}