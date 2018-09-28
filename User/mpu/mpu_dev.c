
#include "mpu_drv.h"
#include "mpu_dev.h"
#include "delay/delay.h"
#include "string.h"
#include "uart/uart.h"

static void mpu_config(mpu_odr_confg_t odr)
{
    mpu_drv_write_reg(MPU6500_SMPLRT_DIV, 0x00);     //sample div 0    
    if(odr == MPU_ODR_20HZ)
    {
        mpu_drv_write_reg(MPU6500_ACCEL_CONFIG_2, 0x04); //accelerometer odr
        mpu_drv_write_reg(MPU6500_CONFIG, 0x04);         //gyro odr
    }
    else if(odr == MPU_ODR_41HZ)
    {
        mpu_drv_write_reg(MPU6500_ACCEL_CONFIG_2, 0x03); //accelerometer odr
        mpu_drv_write_reg(MPU6500_CONFIG, 0x03);         //gyro odr
    }
    else if(odr == MPU_ODR_92HZ)
    {
        mpu_drv_write_reg(MPU6500_ACCEL_CONFIG_2, 0x02); //accelerometer odr
        mpu_drv_write_reg(MPU6500_CONFIG, 0x02);         //gyro odr
    }
    else
    {
        mpu_drv_write_reg(MPU6500_ACCEL_CONFIG_2, 0x04); //accelerometer odr
        mpu_drv_write_reg(MPU6500_CONFIG, 0x04);         //gyro odr
    }
    
    mpu_drv_write_reg(MPU6500_GYRO_CONFIG, 0x08);    //gyro FS 500dps
    mpu_drv_write_reg(MPU6500_ACCEL_CONFIG, 0x10);   //accelerometer FS 8G
    
    mpu_drv_write_reg(MPU6500_FIFO_EN, 0x00);        //fifo disable
    mpu_drv_write_reg(MPU6500_INT_PIN_CFG, 0x00);    //no int
    mpu_drv_write_reg(MPU6500_USER_CTRL, 0x00);      //dmp and fifo disable 
    
}


static void mpu_read_data(mpu_data_struct_t *pdata)
{
    uint8_t *ptmp = (uint8_t *)pdata;
    uint8_t i = 0;
    uint8_t reg_list[12] = {MPU6500_GYRO_XOUT_L, MPU6500_GYRO_XOUT_H, MPU6500_GYRO_YOUT_L, MPU6500_GYRO_YOUT_H,MPU6500_GYRO_ZOUT_L, MPU6500_GYRO_ZOUT_H,
                         MPU6500_ACCEL_XOUT_L, MPU6500_ACCEL_XOUT_H, MPU6500_ACCEL_YOUT_L, MPU6500_ACCEL_YOUT_H, MPU6500_ACCEL_ZOUT_L, MPU6500_ACCEL_ZOUT_H};
    if(ptmp == NULL)
    {
        return;
    }
    for(i = 0;i < sizeof(mpu_data_struct_t);i++)
    {
        ptmp[i] = mpu_drv_read_reg(reg_list[i]);
    }    
}

static void mpu_read_id()
{
    uint8_t who_am_i = 0;
    mpu_drv_write_reg(MPU6500_PWR_MGMT_1, 0x80);     //all reg reset
    delay_xms(200);    
    who_am_i = mpu_drv_read_reg(MPU6500_WHO_AM_I);
    uart1_write_ch(who_am_i); 
}



int mpu_init()
{
    mpu_read_id();
    mpu_config(MPU_ODR_41HZ);    
    return 0;
}



int mpu_read_buf(uint8_t *pbuf, uint32_t len)
{
    uint32_t r_len = sizeof(mpu_data_struct_t);
    if(pbuf == NULL)
    {
        return -1;
    }
    if(len < r_len)
    {
        return -1;
    }
    memset(pbuf, 0, r_len);
    mpu_read_data((mpu_data_struct_t *)pbuf);
    return r_len;
}



 
 

