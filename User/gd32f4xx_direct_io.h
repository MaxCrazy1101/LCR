#ifndef GD32F4XX_DIRECT_IO_H
#define GD32F4XX_DIRECT_IO_H
#include "gd32f4xx.h"
#define BIT_ADDR(byte_offset, bitnum) (volatile unsigned long *)(0x42000000 + (byte_offset * 32) + (bitnum * 4))

#define GPIOA_OCTL_OFFSET             ((GPIOA + 0x14) - 0x40000000) // PAx输出对应的字节偏移量
#define GPIOA_ISTAT_OFFSET            ((GPIOA + 0x10) - 0x40000000) // PAx输入对应的字节偏移量
#define GPIOB_OCTL_OFFSET             ((GPIOB + 0x14) - 0x40000000) // PBx输出对应的字节偏移量
#define GPIOB_ISTAT_OFFSET            ((GPIOB + 0x10) - 0x40000000) // PBx输入对应的字节偏移量
#define GPIOC_OCTL_OFFSET             ((GPIOC + 0x14) - 0x40000000) // PCx输出对应的字节偏移量
#define GPIOC_ISTAT_OFFSET            ((GPIOC + 0x10) - 0x40000000) // PCx输入对应的字节偏移量
#define GPIOD_OCTL_OFFSET             ((GPIOD + 0x14) - 0x40000000) // PDx输出对应的字节偏移量
#define GPIOD_ISTAT_OFFSET            ((GPIOD + 0x10) - 0x40000000) // PDx输入对应的字节偏移量
#define GPIOE_OCTL_OFFSET             ((GPIOE + 0x14) - 0x40000000) // PEx输出对应的字节偏移量
#define GPIOE_ISTAT_OFFSET            ((GPIOE + 0x10) - 0x40000000) // PEx输入对应的字节偏移量
#define GPIOF_OCTL_OFFSET             ((GPIOF + 0x14) - 0x40000000) // PFx输出对应的字节偏移量
#define GPIOF_ISTAT_OFFSET            ((GPIOF + 0x10) - 0x40000000) // PFx输入对应的字节偏移量
#define GPIOG_OCTL_OFFSET             ((GPIOG + 0x14) - 0x40000000) // PGx输出对应的字节偏移量
#define GPIOG_ISTAT_OFFSET            ((GPIOG + 0x10) - 0x40000000) // PGx输入对应的字节偏移量

#define PAout(n)                      *(BIT_ADDR(GPIOA_OCTL_OFFSET, n))  // PAn输出最终可配置
#define PAin(n)                       *(BIT_ADDR(GPIOA_ISTAT_OFFSET, n)) // PAn输入最终可配置
#define PBout(n)                      *(BIT_ADDR(GPIOB_OCTL_OFFSET, n))  // PBn输出最终可配置
#define PBin(n)                       *(BIT_ADDR(GPIOB_ISTAT_OFFSET, n)) // PBn输入最终可配置
#define PCout(n)                      *(BIT_ADDR(GPIOC_OCTL_OFFSET, n))  // PCn输出最终可配置
#define PCin(n)                       *(BIT_ADDR(GPIOC_ISTAT_OFFSET, n)) // PCn输入最终可配置
#define PDout(n)                      *(BIT_ADDR(GPIOD_OCTL_OFFSET, n))  // PDn输出最终可配置
#define PDin(n)                       *(BIT_ADDR(GPIOD_ISTAT_OFFSET, n)) // PDn输入最终可配置
#define PEout(n)                      *(BIT_ADDR(GPIOD_OCTL_OFFSET, n))  // PEn输出最终可配置
#define PEin(n)                       *(BIT_ADDR(GPIOD_ISTAT_OFFSET, n)) // PEn输入最终可配置
#define PFout(n)                      *(BIT_ADDR(GPIOD_OCTL_OFFSET, n))  // PFn输出最终可配置
#define PFin(n)                       *(BIT_ADDR(GPIOD_ISTAT_OFFSET, n)) // PFn输入最终可配置
#define PGout(n)                      *(BIT_ADDR(GPIOG_OCTL_OFFSET, n))  // PFn输出最终可配置
#define PGin(n)                       *(BIT_ADDR(GPIOG_ISTAT_OFFSET, n)) // PFn输入最终可配置
#endif