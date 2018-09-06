#include "timer.h"
#include "./led/led.h"
#include "./protocol/protocol_handle.h"
void timer1_init()
{
    timer_parameter_struct timer_parameter = 
    {
        .prescaler = 2160 - 1,
        .alignedmode = TIMER_COUNTER_EDGE,
        .counterdirection = TIMER_COUNTER_UP,
        .period = 50000,
        .clockdivision = TIMER_CKDIV_DIV1,
    };
    timer_init(TIMER1, &timer_parameter);
    
    timer_interrupt_enable(TIMER1, TIMER_INT_UP);
    nvic_irq_enable(TIMER1_IRQn, 0, 2);
  
    timer_enable(TIMER1);
}


void TIMER1_IRQHandler()
{ 
    led_1s_toggle();
    pro_send_hb();
    timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);
}












