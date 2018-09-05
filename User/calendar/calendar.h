#ifndef __CALENDAR_H__
#define __CALENDAR_H__



#include "gd32f3x0.h"


#define BCD2DEC(n)  ((n >> 4) * 10 + (n & 0xf))
#define DEC2BCD(n)  (((n / 10) << 4) + (n % 10))


typedef struct
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t week;
    uint8_t hour;
    uint8_t min;
    uint8_t second;
}calendar_info_t;


void calendar_init(calendar_info_t info);
void calendar_get_date(calendar_info_t *pinfo);


#endif



