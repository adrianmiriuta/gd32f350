#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "gd32f3x0.h"

#define USE_SPI0          1


#if USE_SPI0          
#define  F_PORT      GPIOA
#define  F_CS_PIN    GPIO_PIN_4
#else
#define  F_PORT      GPIOA
#define  F_CLK_PIN   GPIO_PIN_5
#define  F_CS_PIN    GPIO_PIN_4
#define  F_MO_PIN    GPIO_PIN_7
#define  F_MI_PIN    GPIO_PIN_6

#endif


void platform_clock_enable(void);
void platform_gpio_init(void);
void test_pin(void);


#endif


