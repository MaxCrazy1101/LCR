/*!
    \file    gd32f4xx_it.c
    \brief   interrupt service routines

    \version 2016-08-15, V1.0.0, firmware for GD32F4xx
    \version 2018-12-12, V2.0.0, firmware for GD32F4xx
    \version 2020-09-30, V2.1.0, firmware for GD32F4xx
    \version 2022-03-09, V3.0.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f4xx_it.h"
#include "stdio.h"
#include "lvgl.h"

#define ERROR_INFO "\r\nEnter HardFault_Handler, System Halt.\r\n"

/*!
    \brief    this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}

/*!
    \brief    this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    printf(ERROR_INFO);
    while (1) {
    }
}

/*!
    \brief    this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1) {
    }
}

/*!
    \brief    this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while (1) {
    }
}

/*!
    \brief    this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while (1) {
    }
}
/* FreeRTOS Internal Defined */
#ifndef USE_FREERTOS
/*!
    \brief    this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
}
/*!
    \brief    this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{
}
#endif

/*!
    \brief    this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void)
{
}

/**
 * @brief This function handles EXTI line0 interrupt.
 */
void EXTI0_IRQHandler(void)
{
    // if (exti_interrupt_flag_get(EXTI_0) == SET) // 中断标志位为1
    // {
    //     if (BSP_KEY_IN == 1) // 按键按下
    //     {
    //         /* 按键按下操作的功能 */
    //         gpio_bit_toggle(PORT_LED2, PIN_LED2); // led电平状态翻转
    //         printf("key press!\r\n");             // 串口打印key press!
    //     } else {                                  // 按键释放
    //         /* 按键松开操作的功能 */
    //         printf("key release!\r\n"); // 串口打印key release!
    //     }
    //     exti_interrupt_flag_clear(EXTI_0); // 清中断标志位
    // }
}

/**
 * @brief 31 This function handles DMA0 channel4 interrupt.
 */
void DMA0_Channel4_IRQHandler(void)
{
    // printf("In DMA0_Channel4_IRQHandler\n");
    extern lv_disp_drv_t *disp_drv_p;
    if (dma_interrupt_flag_get(DMA0, DMA_CH4, DMA_INT_FLAG_FTF) == SET) {
        /* 传输完成中断 */
        dma_interrupt_flag_clear(DMA0, DMA_CH4, DMA_INT_FLAG_FTF); // 清除中断标志
        dma_interrupt_disable(DMA0, DMA_CH4, DMA_CHXCTL_FTFIE);    // 关闭中断
        dma_channel_disable(DMA0, DMA_CH4);                        // 失能dma
        // spi_i2s_data_frame_format_config(SPI1, SPI_FRAMESIZE_8BIT);
        lv_disp_flush_ready(disp_drv_p);
    }
}

/**
 * @brief 31 This function handles ADC interrupt.
 */
void ADC_IRQHandler(void)
{
    printf("In ADC_IRQHandler\n");
    if (adc_interrupt_flag_get(ADC1, ADC_INT_FLAG_EOC)) {
        /* 传输完成中断 */
        uint16_t tmp = UINT16_MAX;
        while (tmp--) {
        };
        adc_interrupt_flag_clear(ADC1, ADC_INT_FLAG_EOC);
    }
}

/**
 * @brief 47 This function handles I2C0_EV interrupt.
 */
void I2C0_EV_IRQHandler(void)
{
}
/**
 * @brief 48 This function handles I2C0_ER interrupt.
 */
void I2C0_ER_IRQHandler(void)
{
}