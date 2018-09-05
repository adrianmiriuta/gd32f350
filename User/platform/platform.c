#include "platform.h"
#include "./delay/delay.h"



void platform_clock_enable()
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART0);
    rcu_periph_clock_enable(RCU_USART1);
    rcu_periph_clock_enable(RCU_SPI0);
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
    /**
     *  SPI0  PA5(CLK)&PA6(MISO)&PA7(MOSI)     PA4(CS)
     */
#if USE_SPI0     
    gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_5);
    gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_6);
    gpio_af_set(GPIOA, GPIO_AF_0, GPIO_PIN_7);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_5);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_5);
    
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_6);
    
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7); 
#else  
    gpio_mode_set(F_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, F_CLK_PIN);
    gpio_output_options_set(F_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, F_CLK_PIN);  
    gpio_mode_set(F_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, F_MI_PIN);
    gpio_mode_set(F_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, F_MO_PIN);
    gpio_output_options_set(F_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, F_MO_PIN); 
    gpio_bit_reset(F_PORT, F_CLK_PIN);
    gpio_bit_reset(F_PORT, F_MO_PIN);
#endif
    gpio_mode_set(F_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, F_CS_PIN);
    gpio_output_options_set(F_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, F_CS_PIN);
    gpio_bit_set(F_PORT, F_CS_PIN);
}


void test_pin()
{
    gpio_bit_set(GPIOA, GPIO_PIN_4);
    gpio_bit_set(GPIOA, GPIO_PIN_5);
    gpio_bit_set(GPIOA, GPIO_PIN_7);  
    delay_xms(100);    
    delay_xms(100); 
    delay_xms(100); 
    delay_xms(100); 
    delay_xms(100); 
    gpio_bit_reset(GPIOA, GPIO_PIN_4);
    gpio_bit_reset(GPIOA, GPIO_PIN_5);
    gpio_bit_reset(GPIOA, GPIO_PIN_7);
    delay_xms(100);    
    delay_xms(100); 
    delay_xms(100); 
    delay_xms(100); 
    delay_xms(100);    
}






