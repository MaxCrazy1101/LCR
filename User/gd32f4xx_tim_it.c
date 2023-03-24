/**
 * @file gd32f4xx_tim_it.c
 * @author Alex Newton (sharenfan222@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "gd32f4xx_it.h"
#include "systick.h"

/* 变量声明 */
volatile uint32_t ulHighFrequencyTimerCounts = 0;

extern void xPortSysTickHandler(void);
// extern void bsp_per_ms(void);
// extern void bsp_per_10ms(void);

/*!
    \brief    this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{
    // static uint8_t s_counter = 0;

    delay_decrement();
    // bsp_per_ms();
    // FreeRTOS时钟源
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) // 系统已经运行
    {
        xPortSysTickHandler();
    }
}

/**
 * @brief 40 This function handles TIMER0 Break and TIMER8 interrupt.
 */
void TIMER0_BRK_TIMER8_IRQHandler(void)
{
}
/**
 * @brief 41 This function handles TIMER0 Update and TIMER9 interrupt.
 */
void TIMER0_UP_TIMER9_IRQHandler(void)
{
}
/**
 * @brief 42 This function handles TIMER0 Trigger and Commutation and TIMER10 interrupt.
 */
void TIMER0_TRG_CMT_TIMER10_IRQHandler(void)
{
}
/**
 * @brief 43 This function handles TIMER0 Capture Compare interrupt.
 */
void TIMER0_CC_IRQHandler(void)
{
}
/**
 * @brief 44 This function handles TIMER1 interrupt.
 */
void TIMER1_IRQHandler(void)
{
}
/**
 * @brief 45 This function handles TIMER2 interrupt.
 */
void TIMER2_IRQHandler(void)
{
}
/**
 * @brief 46 This function handles TIMER3 interrupt.
 */
void TIMER3_IRQHandler(void)
{
}
/**
 * @brief 59 This function handles TIMER7 Break and TIMER11 interrupt.
 */
void TIMER7_BRK_TIMER11_IRQHandler(void)
{
}
/**
 * @brief 60 This function handles TIMER7 Update and TIMER12 interrupt.
 */
void TIMER7_UP_TIMER12_IRQHandler(void)
{
}
/**
 * @brief 61 This function handles TIMER7 Trigger and Commutation and TIMER13 interrupt.
 */
void TIMER7_TRG_CMT_TIMER13_IRQHandler(void)
{
}
/**
 * @brief 62 This function handles TIMER7_CC_IRQHandler interrupt.
 */
void TIMER7_CC_IRQHandler(void)
{
}
/**
 * @brief 66 This function handles TIMER4 interrupt.
 */
void TIMER4_IRQHandler(void)
{
}
/**
 * @brief 70 This function handles TIMER5 and DAC0 DAC1 Underrun error interrupt.
 */
void TIMER5_DAC_IRQHandler(void)
{
}
/**
 * @brief 71 This function handles TIMER6 interrupt.
 */
void TIMER6_IRQHandler(void)
{
    timer_interrupt_flag_clear(TIMER6, TIMER_INT_UP);
    ulHighFrequencyTimerCounts++;
}
