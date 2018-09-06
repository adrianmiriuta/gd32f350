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









