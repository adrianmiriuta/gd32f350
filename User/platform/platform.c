#include "platform.h"




void platform_clock_enable()
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART0);
    rcu_periph_clock_enable(RCU_USART1);
}


void platform_gpio_init()
{
    /**
     *   USART1 GPIO INIT  PA2&PA3
     */    
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_2);
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_3);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_2);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_2);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_3);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_3);
    /**
     *   USART0 GPIO INIT  PA9&PA10
     */ 
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9);
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_10);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_9);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_10);
      
}









