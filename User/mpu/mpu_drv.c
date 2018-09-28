/**
 ****************************************************************
 * @file  mpu_drv.c
 * @brief mpu driver
 **************************************************************** 
 */
#include "platform/platform.h" 
#include "user_iic/profile_iic.h"
#include "mpu_drv.h"
#include "delay/delay.h"

/**
 * @addtogroup USER_DRIVER
 * @{
 */

/**
 * @defgroup MPU_DRIVER
 * @{
 */

/**
 * @defgroup MPU_PRIVATE_INTERFACE
 * @{
 */
#define MPU_ENABLE 1 
 
static void mpu_clk_output(uint8_t status)
{
#if MPU_ENABLE    
    if(status == 0x0)
	{
        gpio_bit_reset(MPU_PORT, MPU_CLK);
	}
	else
	{
	    gpio_bit_set(MPU_PORT, MPU_CLK);
	}
#endif
}

static void mpu_sda_output(uint8_t status)
{
#if MPU_ENABLE     
    if(status == 0x0)
	{
        gpio_bit_reset(MPU_PORT, MPU_SDA);
	}
	else
	{
	    gpio_bit_set(MPU_PORT, MPU_SDA);
	}
#endif    
}

static void mpu_sda_dir(uint8_t dir)
{
#if MPU_ENABLE    
    if(dir == IIC_SDA_INPUT)
    {
        gpio_mode_set(MPU_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, MPU_SDA);
    }
    else if(dir == IIC_SDA_OUTPUT)
    {
        gpio_mode_set(MPU_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, MPU_SDA);
        gpio_output_options_set(MPU_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, MPU_SDA);
    }
#endif      
}

static uint8_t mpu_sda_read()
{
#if MPU_ENABLE      
    if(RESET == gpio_input_bit_get(MPU_PORT, MPU_SDA))
    {
        return 0;
    }
    else
    {
        return 1;
    }
#else
    return 0;
#endif    
}

static void mpu_iic_delay()
{
	delay_xus(10);
}

static iic_info_t  gs_iic_info = 
{
    .iic_clk_pin = mpu_clk_output,
    .iic_sda_pin = mpu_sda_output,
    .iic_sda_pin_dir = mpu_sda_dir,
    .iic_sda_pin_read = mpu_sda_read,
    .delay = mpu_iic_delay
};



/**
 * @}
 */ 

/**
 * @defgroup 3DH_PUBLIC_INTERFACE 3DH DRIVER PUBLIC FUNCTIONS
 * @{
 */
#ifndef MPU_DEVICE_ADDRESS 
#define MPU_DEVICE_ADDRESS 0xD0
#endif

uint8_t mpu_drv_read_reg(uint8_t reg)
{
    uint8_t temp;
    i_iic_read_data_mem(&gs_iic_info, MPU_DEVICE_ADDRESS, reg, &temp);
    return temp;
}

int mpu_drv_write_reg(uint8_t reg, uint8_t dat)
{
    return i_iic_write_data_mem(&gs_iic_info, MPU_DEVICE_ADDRESS, reg, dat);
}

int mpu_drv_read_buf(uint8_t reg, uint8_t * buf, uint8_t len)
{
    return i_iic_read_data_buf(&gs_iic_info, MPU_DEVICE_ADDRESS, reg, buf, len);   
}

int mpu_drv_write_buf(uint8_t reg, uint8_t * buf, uint8_t len)
{
    return i_iic_write_data_buf(&gs_iic_info, MPU_DEVICE_ADDRESS, reg, buf, len);   
}
/**
 * @}
 */ 
 
/**
 * @}
 */
 
/**
 * @}
 */



