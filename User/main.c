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
#include "bsp_key.h"
#include "bsp_usart.h"
#include "tim.h"
// #include "bsp_pwm.h"
#include "bsp_sdram_exmc.h"
#include "bsp_norflash_spi.h"
// #include "retarget.h"

#ifdef USE_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#endif
#include "my_app.h"

__attribute__((section("CCMRAM"))) uint8_t ucHeap[configTOTAL_HEAP_SIZE];

void bsp_Init(void)
{
    /* 开启系统配置时钟 */
    rcu_periph_clock_enable(RCU_SYSCFG);
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);

    systick_config();
    gpio_config();
    bsp_key_config();
    dma_config();
    dac_config();
    adc_config();
    bsp_init_extsdram(EXMC_SDRAM_DEVICE0);
    timer_clk_config();
    tim2_enable();
    tim3_enable();
    // tim5_config(240, 10);//10us ->10k
    tim6_config(240, 100); // 100us
    usart_gpio_config();
    printf("BSP Init Complete.\n");
}

/**
 * @brief 主函数
 *
 * @return int
 */
int main(void)
{

    /*
     在启动调度前，为了防止初始化 STM32 外设时有中断服务程序执行，这里禁止全局中断(除了 NMI 和 HardFault)。
     这样做的好处是：
     1. 防止执行的中断服务程序中有 FreeRTOS 的 API 函数。
     2. 保证系统正常启动，不受别的中断影响。
     3. 关于是否关闭全局中断，大家根据自己的实际情况设置即可。
     在移植文件 port.c 中的函数 prvStartFirstTask 中会重新开启全局中断。通过指令 cpsie i 开启，__set_PRIMASK(1)
     和 cpsie i 是等效的。
     */
    // __set_PRIMASK(1);

    /* 硬件初始化 */
    bsp_Init();
    /* 进入FreeRTOS */
    app_main();

    // bsp_spi_norflash_init();
    //    basic_timer_config(24000, 10000);
    // pwm_config(240, 10000);
    // bsp_init_extsdram(EXMC_SDRAM_DEVICE0);
    // printf("Initialization Complate!\n");
    // printf("Get Flash ID: %X\n", norflash_read_JEDEC_ID());

    /*
    如果系统正常启动是不会运行到这里的，运行到这里极有可能是用于定时器任务或者空闲任务的
    heap 空间不足造成创建失败，此要加大 FreeRTOSConfig.h 文件中定义的 heap 大小：
    #define configTOTAL_HEAP_SIZE ( ( size_t ) ( 30 * 1024 ) )
    */
    while (1) {
        printf("Error Soft Process. Check FreeRTOS Heap.");
        delay_1ms(1000);
    }
}
