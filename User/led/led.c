#include "led.h"






void led_1s_toggle()
{
    static uint8_t flag = 0;
    if(flag)
    {
        LED1_ON();
    }
    else
    {
        LED1_OFF();
    }
    flag = !flag;
}


void led2_control(uint8_t n)
{
    if(n)
    {
        LED2_ON();
    }
    else
    {
        LED2_OFF();
    }
}

void led3_control(uint8_t n)
{
    if(n)
    {
        LED3_ON();
    }
    else
    {
        LED3_OFF();
    }
}




