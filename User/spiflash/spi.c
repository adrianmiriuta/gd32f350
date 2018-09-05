#include "spi.h"


void spi0_init()
{
#if USE_SPI0    
    spi_parameter_struct spi_parameter = 
    {
        .device_mode = SPI_MASTER,
        .trans_mode = SPI_TRANSMODE_FULLDUPLEX,
        .frame_size = SPI_FRAMESIZE_8BIT,
        .nss = SPI_NSS_SOFT,
        .endian = SPI_ENDIAN_MSB,
        .clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE,
        .prescale = SPI_PSC_2
    };
    
    spi_init(SPI0, &spi_parameter);
    spi_enable(SPI0);
#endif    
}


uint8_t spi0_rw_byte(uint8_t ch)
{
    uint16_t tmp;
    while(spi_i2s_flag_get(SPI0, SPI_FLAG_TBE) == RESET);
    spi_i2s_data_transmit(SPI0, ch);
    while(spi_i2s_flag_get(SPI0, SPI_FLAG_RBNE) == RESET);
    tmp = spi_i2s_data_receive(SPI0);
    return ((uint8_t)(tmp & 0xff));
}


