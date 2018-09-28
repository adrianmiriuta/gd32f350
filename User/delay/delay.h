#ifndef __DELAY_H__
#define __DELAY_H__


#include "gd32f3x0.h"

void delay_init(void);
void delay_xus(uint32_t xus);
void delay_xms(uint32_t xms);

#endif


