/**
 * @file bsp_sdram_exmc.h
 * @author Alex Newton (sharenfan222@gmail.com)
 * @brief 对于梁山派开发板SDRAM的设置
 * @version 0.1
 * @date 2023-03-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _BSP_SDRAM_EXMC_H
#define _BSP_SDRAM_EXMC_H

#include "gd32f4xx.h"
#include "systick.h"

#define SDRAM_DEVICE0_ADDR ((uint32_t)0xC0000000)
#define SDRAM_DEVICE1_ADDR ((uint32_t)0xD0000000)

#define BSP_SDRAM_SIZE     0x100000

void bsp_init_extsdram(uint32_t sdram_device);
uint32_t bsp_TestExtSDRAM(void);
void bsp_sdram_test(void);
#endif /* _BSP_SDRAM_FMC_H */