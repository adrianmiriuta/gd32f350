#ifndef __FLASH_DEV_H__
#define __FLASH_DEV_H__

#include "stdint.h"
#include "spi.h"



#if USE_SPI0

#define FLASH_CS_SET()          gpio_bit_set(F_PORT, F_CS_PIN) 
#define FLASH_CS_RESET()        gpio_bit_reset(F_PORT, F_CS_PIN)

#else
#define FLASH_CLK_SET()         gpio_bit_set(F_PORT, F_CLK_PIN) 
#define FLASH_CLK_RESET()       gpio_bit_reset(F_PORT, F_CLK_PIN)

#define FLASH_CS_SET()          gpio_bit_set(F_PORT, F_CS_PIN) 
#define FLASH_CS_RESET()        gpio_bit_reset(F_PORT, F_CS_PIN)

#define FLASH_MO_SET()          gpio_bit_set(F_PORT, F_MO_PIN) 
#define FLASH_MO_RESET()        gpio_bit_reset(F_PORT, F_MO_PIN)

#define FLASH_READ_MI()         gpio_input_bit_get(F_PORT, F_MI_PIN)
#endif





#define FLASH_PAGE_SIZE 			  0X100		
#define FLASH_SECTOR_SIZE 			  0X1000	

#define W25X_WRITEENABLE		      0X06		
#define W25X_WRITEDISABLE		      0X04		
#define W25X_READSTATUSREG		      0X05		
#define W25X_WRITESTATUSREG		      0X01	
#define W25X_READDATA			      0X03		
#define W25X_FASTREADDATA		      0X0B		
#define W25X_FASTREADDUAL		      0X3B		 
#define W25X_PAGEPROGRAM		      0X02		
#define W25X_BLOCKERASE			      0XD8	
#define W25X_SECTORERASE		      0X20		
#define W25X_CHIPERASE			      0XC7		
#define W25X_POWERDOWN			      0XB9		
#define W25X_RELEASEPOWERDOWN		  0XAB		
#define W25X_DEVICEID			      0XAB		
#define W25X_MANUFACTDEVICEID		  0X90		
#define W25X_JEDECDEVICEID		      0X9F 
#define W25X_READUNIQUEID			  0X4B		

#define W25X_RESETENABLE              0X66
#define W25X_RESETCMD                 0X99
#define WIP_FLAG					  0X01		
#define WEL_FLAG					  0X02     
#define DUMMY_BYTE				      0XFF	

/*************************************************/
#define FlashMID_Winbond		      0xEF      

#define FlashMID      FlashMID_Winbond



void flash_read_buf(uint8_t * , uint32_t , uint16_t );
void flash_write_buf(uint8_t * , uint32_t , uint16_t );
void flash_erase_xsector(uint32_t addr, uint32_t sector_n);

void flash_power_down(void);
void flash_wakeup(void);
void flash_erase_chip(void);



#endif



