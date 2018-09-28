/**
 ****************************************************************
 * @file  mpu_drv.h
 * @brief mpu driver
 **************************************************************** 
 */
#ifndef __MPU_DRV_H__
#define __MPU_DRV_H__

#include "stdint.h"

/**
 * @addtogroup USER_DRIVER
 * @{
 */

/**
 * @addtogroup MPU_DRIVER 
 * @{
 */



/**
 * @addtogroup MPU_PUBLIC_INTERFACE
 * @{
 */

uint8_t mpu_drv_read_reg(uint8_t reg);
int mpu_drv_write_reg(uint8_t reg, uint8_t dat);
int mpu_drv_read_buf(uint8_t reg, uint8_t * buf, uint8_t len);
int mpu_drv_write_buf(uint8_t reg, uint8_t * buf, uint8_t len);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#endif



