/*
 * filter.h
 *
 *  Created on: 5 Nov 2009
 *      Author: wliu
 */

#ifndef FILTER_H_
#define FILTER_H_
#include <stdint.h>


void init_filter();
int filter(int16_t index, int16_t value);
int16_t rollingAvg(int16_t index, int16_t value);
void reset_filter();

#endif /* FILTER_H_ */

