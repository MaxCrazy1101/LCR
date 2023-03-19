#ifndef _BSP_NORFLASH_SPI_H
#define _BSP_NORFLASH_SPI_H

#include "gd32f4xx.h"

void bsp_spi_norflash_init();
uint16_t norflash_send_read_byte(uint16_t data);
/**
 * 读取芯片ID
 * @return
 */
uint8_t norflash_read_DeviceID(void);
uint32_t norflash_read_JEDEC_ID(void);
uint16_t norflash_read_MDevice_ID(void);
#endif //_BSP_FLASH_EXMC_H
