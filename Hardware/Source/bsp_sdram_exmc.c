#include "bsp_sdram_exmc.h"
#include "gd32f4xx_exmc.h"
#include "stdio.h"
/* Define mode register content */
/* Burst Length */
#define SDRAM_MODEREG_BURST_LENGTH_1 ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2 ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4 ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8 ((uint16_t)0x0003)

/* Burst Type */
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL  ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED ((uint16_t)0x0008)

/* CAS Latency */
#define SDRAM_MODEREG_CAS_LATENCY_2 ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3 ((uint16_t)0x0030)

/* Write Mode */
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)

#define SDRAM_TIMEOUT                            ((uint32_t)0x0000FFFF)

/**
 * @brief 初始化SDRAM
 *
 * @param sdram_device [EXMC_SDRAM_DEVICE0] 或者 [EXMC_SDRAM_DEVICE1]
 */
void bsp_exmc_sdram_init(uint32_t sdram_device)
{
    uint32_t timeout = 0;

    // 初始化时钟
    rcu_periph_clock_enable(RCU_EXMC);
    //    rcu_periph_clock_enable(RCU_GPIOA);
    //    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);

    // GPIO复用设置
    /* SDNWE(PC0),SDNE0(PC2),SDCKE0(PC3) pin configuration */
    uint32_t config_pin = GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3;
    gpio_af_set(GPIOC, GPIO_AF_12, config_pin);
    gpio_mode_set(GPIOC, GPIO_MODE_AF, GPIO_PUPD_PULLUP, config_pin);
    gpio_output_options_set(GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);

    /* D2(PD0),D3(PD1),D13(PD8),D14(PD9),D15(PD10),D0(PD14),D1(PD15) pin configuration */
    config_pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15;
    gpio_af_set(GPIOD, GPIO_AF_12, config_pin);
    gpio_mode_set(GPIOD, GPIO_MODE_AF, GPIO_PUPD_PULLUP, config_pin);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);

    /* NBL0(PE0),NBL1(PE1),D4(PE7),D5(PE8),D6(PE9),D7(PE10),D8(PE11),D9(PE12),D10(PE13),D11(PE14),D12(PE15) pin configuration */
    config_pin =
        GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
        GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    gpio_af_set(GPIOE, GPIO_AF_12, config_pin);
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_PULLUP, config_pin);
    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);

    /* A0(PF0),A1(PF1),A2(PF2),A3(PF3),A4(PF4),A5(PF5),NRAS(PF11),A6(PF12),A7(PF13),A8(PF14),A9(PF15) pin configuration */
    config_pin =
        GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 |
        GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    gpio_af_set(GPIOF, GPIO_AF_12, config_pin);
    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, config_pin);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);

    /* A10(PG0),A11(PG1),A12(PG2),BA0(PG4),BA1(PG5),SDCLK(PG8),NCAS(PG15) pin configuration */
    config_pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8 | GPIO_PIN_15;
    gpio_af_set(GPIOG, GPIO_AF_12, config_pin);
    gpio_mode_set(GPIOG, GPIO_MODE_AF, GPIO_PUPD_PULLUP, config_pin);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);
    // /* SDNWE(PH5) pin configuration */
    // gpio_af_set(GPIOH, GPIO_AF_12, GPIO_PIN_5);
    // gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_5);
    // gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5);

    /* 检查设置 */
    if (EXMC_SDRAM_DEVICE0 == sdram_device) {
        sdram_device = EXMC_SDRAM_DEVICE0_SELECT;
    } else {
        sdram_device = EXMC_SDRAM_DEVICE1_SELECT;
    }

    // 初始化EXMC SDRAM流程
    // 第一步: 配置延迟
    exmc_sdram_timing_parameter_struct hsdram_timing = {
        .row_to_column_delay      = 2, /* RCD: min=18ns */
        .row_precharge_delay      = 2, /* RPD: min=18ns */
        .write_recovery_delay     = 2, /* WRD: min=1 Clock cycles +6ns */
        .auto_refresh_delay       = 6, /* ARFD: min=60ns */
        .row_address_select_delay = 5, /* RASD: min=42ns , max=120k (ns) */
        .exit_selfrefresh_delay   = 7, /* XSRD: min = 67ns */
        .load_mode_register_delay = 2, /* LMRD: 2 clock cycles */
    };
    // 第二步: configure SDRAM control registers
    exmc_sdram_parameter_struct hsdram_param = {
        .sdram_device         = EXMC_SDRAM_DEVICE0,
        .pipeline_read_delay  = EXMC_PIPELINE_DELAY_2_HCLK,
        .burst_read_switch    = ENABLE,
        .sdclock_config       = EXMC_SDCLK_PERIODS_3_HCLK, // 使用2分频 240MHz/2=120MHz
        .write_protection     = DISABLE,
        .cas_latency          = EXMC_CAS_LATENCY_3_SDCLK, // CAS 也就是CL参数
        .internal_bank_number = EXMC_SDRAM_4_INTER_BANK,
        .data_width           = EXMC_SDRAM_DATABUS_WIDTH_16B,
        .row_address_width    = EXMC_SDRAM_ROW_ADDRESS_13,
        .column_address_width = EXMC_SDRAM_COW_ADDRESS_9,
        .timing               = &hsdram_timing,
    };
    // EXMC SDRAM Initialization
    exmc_sdram_init(&hsdram_param);

    // 第三步: configure CKE high command
    /* configure the SDRAM memory command */
    exmc_sdram_command_parameter_struct sdram_command_init_struct = {
        .bank_select           = sdram_device,
        .command               = EXMC_SDRAM_CLOCK_ENABLE,
        .auto_refresh_number   = EXMC_SDRAM_AUTO_REFLESH_2_SDCLK,
        .mode_register_content = 0,
    };
    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(sdram_device, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    exmc_sdram_command_config(&sdram_command_init_struct);
    // 第四步: 延迟等待就绪
    delay_1ms(1);
    // 第五步: 预充电所有bank
    sdram_command_init_struct.command = EXMC_SDRAM_PRECHARGE_ALL;
    exmc_sdram_command_config(&sdram_command_init_struct);
    // 第六步: 设置自动刷新指令
    sdram_command_init_struct.command             = EXMC_SDRAM_AUTO_REFRESH;
    sdram_command_init_struct.auto_refresh_number = EXMC_SDRAM_AUTO_REFLESH_9_SDCLK;
    exmc_sdram_command_config(&sdram_command_init_struct);
    // 第七步：设置读取模式寄存器
    sdram_command_init_struct.command               = EXMC_SDRAM_LOAD_MODE_REGISTER;
    sdram_command_init_struct.auto_refresh_number   = EXMC_SDRAM_AUTO_REFLESH_2_SDCLK;
    sdram_command_init_struct.mode_register_content = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 |
                                                      SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
                                                      SDRAM_MODEREG_CAS_LATENCY_3 |
                                                      SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                                                      SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(sdram_device, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
    exmc_sdram_command_config(&sdram_command_init_struct);

    /* step 8 : set the auto-refresh rate counter--------------------------------*/
    /* 64ms, 8192-cycle refresh, 64ms/8192=7.81us */
    /* SDCLK_Freq = SYS_Freq/2 */
    /* (7.81 us * SDCLK_Freq) - 20 */
    exmc_sdram_refresh_count_set(761);

    /* wait until the SDRAM controller is ready */
    timeout = SDRAM_TIMEOUT;
    while ((exmc_flag_get(sdram_device, EXMC_SDRAM_FLAG_NREADY) != RESET) && (timeout > 0)) {
        timeout--;
    }
}

/**
 * @brief fill the buffer with specified value
 *
 * @param pbuffer pointer on the buffer to fill
 * @param buffer_lengh size of the buffer to fill
 * @param offset value to fill on the buffer
 */
void fill_buffer(uint8_t *pbuffer, uint16_t buffer_lengh, uint16_t offset)
{
    uint16_t index = 0;

    /* fill the buffer with specified values */
    for (index = 0; index < buffer_lengh; index++) {
        pbuffer[index] = index + offset;
    }
}

/**
 * @brief write a byte buffer(data is 8 bits) to the EXMC SDRAM memory
 *
 * @param sdram_device  specify which a SDRAM memory block is written
 * @param pbuffer pointer to buffer
 * @param writeaddr SDRAM memory internal address from which the data will be written
 * @param numbytetowrite number of bytes to write
 */
void sdram_writebuffer_8(uint32_t sdram_device, uint8_t *pbuffer, uint32_t writeaddr, uint32_t numbytetowrite)
{
    uint32_t temp_addr;

    /* select the base address according to EXMC_Bank */
    if (sdram_device == EXMC_SDRAM_DEVICE0) {
        temp_addr = SDRAM_DEVICE0_ADDR;
    } else {
        temp_addr = SDRAM_DEVICE1_ADDR;
    }

    /* while there is data to write */
    for (; numbytetowrite != 0; numbytetowrite--) {
        /* transfer data to the memory */
        *(uint8_t *)(temp_addr + writeaddr) = *pbuffer++;

        /* increment the address */
        writeaddr += 1;
    }
}

/*!
    \brief      read a block of 8-bit data from the EXMC SDRAM memory
    \param[in]  sdram_device: specify which a SDRAM memory block is written
    \param[in]  pbuffer: pointer to buffer
    \param[in]  readaddr: SDRAM memory internal address to read from
    \param[in]  numbytetoread: number of bytes to read
    \param[out] none
    \retval     none
*/
void sdram_readbuffer_8(uint32_t sdram_device, uint8_t *pbuffer, uint32_t readaddr, uint32_t numbytetoread)
{
    uint32_t temp_addr;

    /* select the base address according to EXMC_Bank */
    if (sdram_device == EXMC_SDRAM_DEVICE0) {
        temp_addr = SDRAM_DEVICE0_ADDR;
    } else {
        temp_addr = SDRAM_DEVICE1_ADDR;
    }

    /* while there is data to read */
    for (; numbytetoread != 0; numbytetoread--) {
        /* read a byte from the memory */
        *pbuffer++ = *(uint8_t *)(temp_addr + readaddr);

        /* increment the address */
        readaddr += 1;
    }
}

#define EXT_SDRAM_ADDR SDRAM_DEVICE0_ADDR
#define EXT_SDRAM_SIZE BSP_SDRAM_SIZE

/**
 * @brief 扫描测试SDRAM
 *
 * @return uint32_t 错误个数
 */
uint32_t bsp_TestExtSDRAM(void)
{
    uint32_t i;
    uint32_t *pSRAM;
    uint8_t *pBytes;
    uint32_t err;

    const uint8_t ByteBuf[4] = {0x55, 0xA5, 0x5A, 0xAA};
    /* 写 SRAM */
    pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
    for (i = 0; i < EXT_SDRAM_SIZE / 4; i++) {
        *pSRAM++ = i;
    }

    /* 读 SRAM */
    err   = 0;
    pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
    for (i = 0; i < EXT_SDRAM_SIZE / 4; i++) {
        if (*pSRAM++ != i) {
            err++;
        }
    }

    if (err > 0) {
        return (4 * err);
    }

    /* 对SDRAM的数据求反并写入 */
    pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
    for (i = 0; i < EXT_SDRAM_SIZE / 4; i++) {
        *pSRAM = ~*pSRAM;
        pSRAM++;
    }

    /* 再次比较SDRAM数据 */
    err   = 0;
    pSRAM = (uint32_t *)EXT_SDRAM_ADDR;
    for (i = 0; i < EXT_SDRAM_SIZE / 4; i++) {
        if (*pSRAM++ != (~i)) {
            err++;
        }
    }

    if (err > 0) {
        return (4 * err);
    }

    /* 测试按字节方式访问 */
    pBytes = (uint8_t *)EXT_SDRAM_ADDR;
    for (i = 0; i < sizeof(ByteBuf); i++) {
        *pBytes++ = ByteBuf[i];
    }

    /* 比较SDRAM数据 */
    err    = 0;
    pBytes = (uint8_t *)EXT_SDRAM_ADDR;
    for (i = 0; i < sizeof(ByteBuf); i++) {
        if (*pBytes++ != ByteBuf[i]) {
            err++;
        }
    }
    if (err > 0) {
        return err;
    }
    return 0;
}
void bsp_sdram_test(void)
{
    uint32_t temp;
    /*向SDRAM写入8位数据*/
    *(uint8_t *)(SDRAM_DEVICE0_ADDR) = (uint8_t)2;
    /*从SDRAM读取数据*/
    temp = *(uint8_t *)(SDRAM_DEVICE0_ADDR);
    printf("8bit data:%u\n", temp);
    /*写/读 16位数据*/
    *(uint16_t *)(SDRAM_DEVICE0_ADDR + 10) = (uint16_t)456;
    temp                                   = *(uint16_t *)(SDRAM_DEVICE0_ADDR + 10);
    printf("16bit data:%u\n", temp);
    /*写/读 32位数据*/
    *(uint32_t *)(SDRAM_DEVICE0_ADDR + 20) = (uint32_t)123;
    temp                                   = *(uint32_t *)(SDRAM_DEVICE0_ADDR + 20);
    printf("32bit data:%u\n", temp);
    printf("Ready For SDRAM RW Test.\n");
    printf("SDRAM TEST finished. Get Wrong %u.\n", bsp_TestExtSDRAM());
}