#ifndef BSP_LCD_H
#define BSP_LCD_H
#ifdef __cplusplus
extern "C" {
#endif
#include "gd32f4xx_direct_io.h"
//-----------------LCD端口定义----------------

/* PB10 CLK
 * PB11 LCD_RES
 * PB12 LCD_DC
 * PB13 LCD_BLK
 * PB15 MOSI
 * */

#define LCD_RES_Clr() PBout(11) = 0 // RES
#define LCD_RES_Set() PBout(11) = 1

#define LCD_DC_Clr()  PBout(12) = 0 // DC
#define LCD_DC_Set()  PBout(12) = 1

// #define LCD_CS_Clr()  GPIO_ResetBits(GPIOA, GPIO_Pin_3) // CS
// #define LCD_CS_Set()  GPIO_SetBits(GPIOA, GPIO_Pin_3)

#define LCD_BLK_Clr() PBout(13) = 0 // BLK
#define LCD_BLK_Set() PBout(13) = 1

void LCD_GPIO_Init(void);                             // 初始化GPIO
void LCD_Writ_Bus(u8 dat);                            // spi时序
void LCD_WR_DATA8(u8 dat);                            // 写入一个字节
void LCD_WR_DATA(u16 dat);                            // 写入2个字节
void LCD_WR_REG(u8 dat);                              // 写入寄存器
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2); // 设置目标地址
void LCD_Init(void);                                  // LCD初始化

#ifdef __cplusplus
}
#endif
#endif /* BSP_LCD_H */