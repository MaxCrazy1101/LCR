#ifndef _BSP_BASIC_TIMER_H
#define _BSP_BASIC_TIMER_H

#include "gd32f4xx.h"
#include "systick.h"

#define BSP_TIMER_RCU        RCU_TIMER5            // 定时器时钟
#define BSP_TIMER            TIMER5                // 定时器
#define BSP_TIMER_IRQ        TIMER5_DAC_IRQn       // 定时器中断
#define BSP_TIMER_IRQHANDLER TIMER5_DAC_IRQHandler // 定时器中断服务函数

// #define BSP_TIMER_RCU  				RCU_TIMER2					// 定时器时钟
// #define BSP_TIMER      				TIMER2							// 定时器
// #define BSP_TIMER_IRQ  			  TIMER2_IRQn					// 定时器中断
// #define BSP_TIMER_IRQHANDLER  TIMER2_IRQHandler		// 定时器中断服务函数

void timer_clk_config();

void tim2_config(uint16_t prescaler, uint16_t period); // TIMER2定时器配置
void tim2_enable();
void tim2_disable();

void tim3_config(uint16_t prescaler, uint16_t period); // TIMER3定时器配置
void tim3_enable();
void tim3_disable();

void tim5_config(uint16_t prescaler, uint16_t period); // 基本定时器配置

void tim6_config(uint16_t prescaler, uint16_t period); // 基本定时器配置

#endif /* _BSP_BASIC_TIMER_H */
