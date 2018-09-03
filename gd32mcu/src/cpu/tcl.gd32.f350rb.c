/*************************************************************************************************
 *                                     Trochili RTOS Kernel                                      *
 *                                  Copyright(C) 2017 LIUXUMING                                  *
 *                                       www.trochili.com                                        *
 *************************************************************************************************/
#include "tcl.types.h"
#include "tcl.config.h"
#include "tcl.various.h"
#include "tcl.kernel.h"

/* 重写库函数 */
void SysTick_Handler(void)
{
    OsKernelEnterIntrState();
    OsKernelTickISR();
    OsKernelLeaveIntrState();
}

/* 重写库函数 */
void EXTI4_15_IRQHandler(void)
{
#if (TCLC_IRQ_ENABLE)
    OsKernelEnterIntrState();
    OsIrqEnterISR(GD32F350RB_EXTI4_15_IRQn);
    OsKernelLeaveIntrState();
#else
    return;
#endif
}
