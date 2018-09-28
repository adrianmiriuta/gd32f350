#include "delay.h"

#define DELAY_US_FACTOR     108

void delay_init()
{
    systick_clksource_set(SYSTICK_CLKSOURCE_HCLK);
}


//xus < 155344
void delay_xus(uint32_t xus)
{
    uint32_t xtick = xus * DELAY_US_FACTOR;
    if(xus > 155000)
    {
        return;
    }
    SysTick->LOAD = xtick - 1;
    SysTick->VAL  = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; 
    while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0x0);
}

//xms < 155
void delay_xms(uint32_t xms)
{
    uint32_t xtick = xms * DELAY_US_FACTOR * 1000;
    if(xms > 155)
    {
        return;
    } 
    SysTick->LOAD = xtick - 1;
    SysTick->VAL  = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; 
    while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0x0); 
}

