/*!
    \file    main.c
    \brief   led spark with systick

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

#include "gd32f4xx.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"

#include "math.h"
#include "arm_math.h"

#include "gpio.h"
#include "dma.h"
#include "dac.h"
#include "adc.h"
#include "tim.h"

#include "gd32f4xx_gpio.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "tim.h"
// #include "bsp_pwm.h"
#include "bsp_sdram_exmc.h"
#include "bsp_norflash_spi.h"
// #include "retarget.h"

/**
 * @brief 主函数
 *
 * @return int
 */
int main(void)
{
    /* 开启系统配置时钟 */
    rcu_periph_clock_enable(RCU_SYSCFG);

    systick_config();
    gpio_config();
    dma_config();
    dac_config();
    adc_config();
    timer_clk_config();
    tim2_enable();
    tim3_enable();
    tim5_config(240, 10);

    usart_gpio_config();
    // bsp_spi_norflash_init();
    //    basic_timer_config(24000, 10000);
    // pwm_config(240, 10000);
    // bsp_exmc_sdram_init(EXMC_SDRAM_DEVICE0);
    // printf("Initialization Complate!\n");
    // printf("Get Flash ID: %X\n", norflash_read_JEDEC_ID());
    float temperature;
    float vref_value;
    while (1) {
        temperature = (1.43f - adc0_data[0] * 3.3f / 4096) * 1000 / 4.3f + 25;
        vref_value  = (adc0_data[1] * 3.3f / 4096);
        printf("The temperature origin data is %d \r ,Battery Voltage origin data: %d \n", adc0_data[0], adc0_data[1]);
        printf("The temperature data is %2.0f degrees Celsius\r ,Battery Voltage: %5.2f V\n", temperature, vref_value);
        printf("ADC1 Data[1]:%d\n", adc1_data[1]);
        delay_1ms(1000);
    }
}
