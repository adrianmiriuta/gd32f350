/*************************************************************************************************
 *                                     Trochili RTOS Kernel                                      *
 *                                  Copyright(C) 2017 LIUXUMING                                  *
 *                                       www.trochili.com                                        *
 *************************************************************************************************/
#ifndef _TCL_GD32_F350RB_H
#define _TCL_GD32_F350RB_H

/* External Interrupts */
#define  GD32F350RB_WWDGT_IRQn                  (00)
#define  GD32F350RB_LVD_IRQn                    (01)
#define  GD32F350RB_RTC_IRQn                    (02)
#define  GD32F350RB_FMC_IRQn                    (03)
#define  GD32F350RB_RCU_IRQn                    (04)
#define  GD32F350RB_EXTI0_1_IRQn                (05)
#define  GD32F350RB_EXTI2_3_IRQn                (06)
#define  GD32F350RB_EXTI4_15_IRQn               (07)
#define  GD32F350RB_TSI_IRQn                    (08)
#define  GD32F350RB_DMA_Channel0_IRQn           (09)
#define  GD32F350RB_DMA_Channel1_2_IRQn         (10)
#define  GD32F350RB_DMA_Channel3_4_IRQn         (11)
#define  GD32F350RB_ADC_CMP_IRQn                (12)
#define  GD32F350RB_TIMER0_BRK_UP_TRG_COM_IRQn  (13)
#define  GD32F350RB_TIMER0_CC_IRQn              (14)
#define  GD32F350RB_TIMER1_IRQn                 (15)
#define  GD32F350RB_TIMER2_IRQn                 (16)
#define  GD32F350RB_TIMER5_DAC_IRQn             (17)
#define  GD32F350RB_TIMER13_IRQn                (18)
#define  GD32F350RB_TIMER14_IRQn                (19)
#define  GD32F350RB_TIMER15_IRQn                (20)
#define  GD32F350RB_TIMER16_IRQn                (21)
#define  GD32F350RB_I2C0_EV_IRQn                (22)
#define  GD32F350RB_I2C1_EV_IRQn                (23)
#define  GD32F350RB_SPI0_IRQn                   (24)
#define  GD32F350RB_SPI1_IRQn                   (25)
#define  GD32F350RB_USART0_IRQn                 (26)
#define  GD32F350RB_USART1_IRQn                 (27)
#define  GD32F350RB_CEC_IRQn                    (28)
#define  GD32F350RB_I2C0_ER_IRQn                (29)
#define  GD32F350RB_I2C1_ER_IRQn                (30)
#define  GD32F350RB_I2C2_EV_IRQn                (31)
#define  GD32F350RB_I2C2_ER_IRQn                (32)
#define  GD32F350RB_USBFS_WKUP_IRQn             (33)
#define  GD32F350RB_DMA_Channel5_6_IRQn         (34)
#define  GD32F350RB_SPI2_IRQn                   (35)
#define  GD32F350RB_USBFS_IRQn                  (36)
                
extern void EXTI4_15_IRQHandler(void);
#endif
