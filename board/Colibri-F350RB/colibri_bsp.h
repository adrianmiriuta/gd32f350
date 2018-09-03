#ifndef _TCL_COLIBRI_H
#define _TCL_COLIBRI_H

#include "tcl.gd32.f350rb.h"
#include "colibri_bsp_led.h"
#include "colibri_bsp_key.h"
#include "colibri_bsp_uart.h"

#define KEY0_IRQ_ID    GD32F350RB_EXTI4_15_IRQn
#define KEY1_IRQ_ID    GD32F350RB_EXTI4_15_IRQn

extern void EvbSetupEntry(void);
extern void EvbTraceEntry(const char* str);
#define EVB_PRINTF     EvbTraceEntry
#endif /* _TCL_COLIBRI_H */
