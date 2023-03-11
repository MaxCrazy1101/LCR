/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef GD32F4XX_LIBOPT_H
#define GD32F4XX_LIBOPT_H

/* Comment the line below to disable peripheral header file inclusion */
#include "RTE_Components.h"

#ifdef RTE_DEVICE_STDPERIPHERALS_ADC
#include "gd32f4xx_adc.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_CAN
#include "gd32f4xx_can.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_CRC
#include "gd32f4xx_crc.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_CTC
#include "gd32f4xx_ctc.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_DAC
#include "gd32f4xx_dac.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_DBG
#include "gd32f4xx_dbg.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_DCI
#include "gd32f4xx_dci.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_DMA
#include "gd32f4xx_dma.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_ENET
#include "gd32f4xx_enet.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_EXMC
#include "gd32f4xx_exmc.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_EXTI
#include "gd32f4xx_exti.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_FMC
#include "gd32f4xx_fmc.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_FWDGT
#include "gd32f4xx_fwdgt.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_GPIO
#include "gd32f4xx_gpio.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_I2C
#include "gd32f4xx_i2c.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_IPA
#include "gd32f4xx_ipa.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_IREF
#include "gd32f4xx_iref.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_MISC
#include "gd32f4xx_misc.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_PMU
#include "gd32f4xx_pmu.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_RCU
#include "gd32f4xx_rcu.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_RTC
#include "gd32f4xx_rtc.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_SDIO
#include "gd32f4xx_sdio.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_SPI
#include "gd32f4xx_spi.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_SYSCFG
#include "gd32f4xx_syscfg.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_TIMER
#include "gd32f4xx_timer.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_TLI
#include "gd32f4xx_tli.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_TRNG
#include "gd32f4xx_trng.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_USART
#include "gd32f4xx_usart.h"
#endif
#ifdef RTE_DEVICE_STDPERIPHERALS_WWDGT
#include "gd32f4xx_wwdgt.h"
#endif

#endif /* GD32F4XX_LIBOPT_H */

