//
// Created by Captain.L on 2023/3/12.
//

#include <stdio.h>
#include "bsp_norflash_spi.h"
#include "gd32f4xx_spi.h"
#include "gd32f4xx_direct_io.h"

#define BANK0_NOR1_ADDR          ((uint32_t)0x64000000)
#define BANK_NORFLASH_ADDR       BANK0_NOR1_ADDR

#define BLOCKERASE_TIMEOUT       ((uint32_t)0x00A00000)
#define CHIPERASE_TIMEOUT        ((uint32_t)0x30000000)
#define PROGRAM_TIMEOUT          ((uint32_t)0x00001400)

#define ADDR_SHIFT(A)            (BANK_NORFLASH_ADDR + (2 * (A)))
#define NOR_WRITE(Address, Data) (*(__IO uint16_t *)(Address) = (Data))

#define W25X_FLASH_PAGE_SIZE     256

#define DUMMY                    0xFF
#define W25X_MDEVICE_ID          0X90
#define W25X_DEVICE_ID           0XAB
#define W25X_JEDEC_ID            0X9F
#define W25X_SECTOR_ERASE        0X20
#define W25X_BLOCK_ERASE_32K     0X52
#define W25X_BLOCK_ERASE_64K     0XD8
#define W25X_WRITE_ENABLE        0X06
#define W25X_WRITE_DISABLE       0X04
#define W25X_READ_STATUS_REG     0X05
#define W25X_PAGE_PROGRAM        0X02

#define WIP_FLAG                 0X01
void bsp_spi_norflash_init()
{
    rcu_periph_clock_enable(RCU_SPI4);
    rcu_periph_clock_enable(RCU_GPIOF);

    // GPIO复用设置
    // SPI 除了CS 引脚不需要上拉。
    // CS引脚已经在外部电路硬件上拉
    {
        uint32_t config_pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
        gpio_af_set(GPIOF, GPIO_AF_5, config_pin);
        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, config_pin);
        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);
        //        config_pin = GPIO_PIN_8;
        //        gpio_af_set(GPIOF, GPIO_AF_5, config_pin);
        //        gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, config_pin);
        //        gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);
    }
    // 配置SPI4
    // 支持 SPI 总线的工作模式 0（0，0）和 3（1，1）。
    // 模式 0 和模式 3 的主要区别在于常态时的 CLK信号，当 SPI 主机已准备好数据还没传输到串行 Flash 中，对于模式 0 CLK 信号常态为低。
    // 设备数据传输是从高位开始，数据传输的格式为 8bit，数据采样从第二个时间边沿开始，空闲状态时，时钟线 CLK 为高电平。
    {
        spi_i2s_deinit(SPI4);
        spi_parameter_struct spi_init_struct;
        spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
        spi_init_struct.device_mode          = SPI_MASTER;
        spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
        spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
        spi_init_struct.nss                  = SPI_NSS_SOFT;
        spi_init_struct.prescale             = SPI_PSC_16;
        spi_init_struct.endian               = SPI_ENDIAN_MSB;
        spi_init(SPI4, &spi_init_struct);
    }
    // 开启SPI4
    spi_nss_output_enable(SPI4);
    spi_enable(SPI4);
}

uint16_t norflash_send_read_byte(uint16_t data)
{
    uint8_t retry = 0;

    while (spi_i2s_flag_get(SPI4, SPI_FLAG_TBE) == RESET) // 检查指定的SPI标志位设置与否:发送缓存空标志位
    {
        //        retry++;
        //        if (retry > 200) return 0;
    }
    spi_i2s_data_transmit(SPI4, data); // 通过外设SPIx发送16bit

    while (spi_i2s_flag_get(SPI4, SPI_FLAG_RBNE) == RESET) // 检查指定的SPI标志位设置与否:接受缓存非空标志位
    {
        //        retry++;
        //        if (retry > 200) return 0;
    }
    return spi_i2s_data_receive(SPI4); // 返回通过SPIx最近接收的数据
}

void norflash_send_byte(uint16_t data)
{
    uint8_t retry = 0;

    while (spi_i2s_flag_get(SPI4, SPI_FLAG_TBE) == RESET) // 检查指定的SPI标志位设置与否:发送缓存空标志位
    {
        //        retry++;
        //        if (retry > 200) return 0;
    }
    spi_i2s_data_transmit(SPI4, data); // 通过外设SPIx发送16bit
}
static inline void norflash_cs_low()
{
    PFout(6) = 0;
    //    gpio_bit_reset(GPIOF, GPIO_PIN_6);
    //    spi_nss_internal_low(SPI4);
}
static inline void norflash_cs_high()
{
    PFout(6) = 1;
    //    gpio_bit_set(GPIOF, GPIO_PIN_6);
    //    spi_nss_internal_high(SPI4);
}
uint8_t norflash_read_DeviceID(void)
{
    uint16_t Temp = 0;

    norflash_cs_low();
    norflash_send_read_byte(W25X_DEVICE_ID); // 发送读取ID命令
    norflash_send_read_byte(DUMMY);
    norflash_send_read_byte(DUMMY);
    norflash_send_read_byte(DUMMY);
    Temp = norflash_send_read_byte(DUMMY);
    norflash_cs_high();
    return Temp;
}
uint32_t norflash_read_JEDEC_ID(void)
{
    uint32_t temp = 0;
    norflash_cs_low();
    norflash_send_read_byte(W25X_JEDEC_ID); // 发送读取ID命令
    temp |= norflash_send_read_byte(DUMMY) << 16;
    temp |= norflash_send_read_byte(DUMMY) << 8;
    temp |= norflash_send_read_byte(DUMMY);
    norflash_cs_high();
    return temp;
}
uint16_t norflash_read_MDevice_ID(void)
{
    uint16_t temp = 0;
    norflash_cs_low();
    norflash_send_read_byte(W25X_MDEVICE_ID); // 发送读取ID命令
    norflash_send_read_byte(DUMMY);
    norflash_send_read_byte(DUMMY);
    norflash_send_read_byte(DUMMY);
    temp |= norflash_send_read_byte(DUMMY) << 8;
    temp |= norflash_send_read_byte(DUMMY);
    norflash_cs_high();
    return temp;
}
/**
 * 根据Flash的读写要求，在进行写入、扇区擦除、块擦除、整片擦除及写状态寄存器前，都需要发送写使能命令。
 */
void norflash_write_enable()
{
    norflash_cs_low();
    norflash_send_read_byte(W25X_WRITE_ENABLE);
    norflash_cs_high();
}
/**
 * 本函数实质是不断检测Flash状态寄存器的Busy位，直到Flash的内部写时序完成，从而确保下一通信操作正常，这里WIP_Flag宏定义为0x01。
主机通过发送读状态寄存器命令Read Status Register（05h），返回它的8位状态寄存器值。
 本函数检测的就是状态寄存器的Bit0位，即BUSY位。Flash在执行内部写时序的时候，
 除了读状态寄存器的命令，其他一切命令都会忽略，并且BUSY位保持为1，即我们需要等待BUSY位为0的时候，再向FLASH发送其他指令。
 */
void norflash_wait_for_write_end()
{
    uint8_t flash_status;
    norflash_cs_low();
    flash_status = norflash_send_read_byte(W25X_READ_STATUS_REG);
    while ((flash_status & WIP_FLAG) == SET) {
        flash_status = norflash_send_read_byte(DUMMY);
    }
    norflash_cs_high();
}
void norflash_sector_erase(uint32_t sectorAddr)
{
    norflash_write_enable();
    norflash_wait_for_write_end();
    norflash_cs_low();
    norflash_send_read_byte(W25X_SECTOR_ERASE);
    norflash_send_read_byte((sectorAddr & 0xFF0000) >> 16);
    norflash_send_read_byte((sectorAddr & 0xFF00) >> 8);
    norflash_send_read_byte((sectorAddr & 0xFF));
    norflash_cs_high();
    norflash_wait_for_write_end();
}
/**
 *
 * @param pBuffer 需要写入的内容
 * @param addr 写入的地址
 * @param len 需要写入的字节数量
 */
void norflash_page_write(uint8_t *pBuffer, uint32_t addr, uint16_t len)
{
    norflash_write_enable();
    norflash_cs_low();
    // 页编程指令
    norflash_send_read_byte(W25X_PAGE_PROGRAM);
    // 发送高8位地址
    norflash_send_read_byte((addr & 0xFF0000) >> 16);
    // 发送中8位地址
    norflash_send_read_byte((addr & 0xFF00) >> 8);
    // 发送低8位地址
    norflash_send_read_byte(addr & 0xFF);
    if (len > W25X_FLASH_PAGE_SIZE) {
        len = W25X_FLASH_PAGE_SIZE;
    }
    while (len--) {
        norflash_send_read_byte(*pBuffer);
        pBuffer++;
    }
    norflash_cs_high();
    norflash_wait_for_write_end();
}

void norflash_buffer_write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
    Addr        = WriteAddr % W25X_FLASH_PAGE_SIZE;
    count       = W25X_FLASH_PAGE_SIZE - Addr;
    NumOfPage   = NumByteToWrite / W25X_FLASH_PAGE_SIZE;
    NumOfSingle = NumByteToWrite % W25X_FLASH_PAGE_SIZE;
    if (Addr == 0) /* WriteAddr is W25X_FLASH_PAGE_SIZE aligned  */
    {
        if (NumOfPage == 0) /* NumByteToWrite < W25X_FLASH_PAGE_SIZE */
        {
            norflash_page_write(pBuffer, WriteAddr, NumByteToWrite);
        } else /* NumByteToWrite > W25X_FLASH_PAGE_SIZE */
        {
            while (NumOfPage--) {
                norflash_page_write(pBuffer, WriteAddr, W25X_FLASH_PAGE_SIZE);
                WriteAddr += W25X_FLASH_PAGE_SIZE;
                pBuffer += W25X_FLASH_PAGE_SIZE;
            }
            norflash_page_write(pBuffer, WriteAddr, NumOfSingle);
        }
    } else /* WriteAddr is not W25X_FLASH_PAGE_SIZE aligned  */
    {
        if (NumOfPage == 0) /* NumByteToWrite < W25X_FLASH_PAGE_SIZE */
        {
            if (NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > W25X_FLASH_PAGE_SIZE */
            {
                temp = NumOfSingle - count;

                norflash_page_write(pBuffer, WriteAddr, count);
                WriteAddr += count;
                pBuffer += count;

                norflash_page_write(pBuffer, WriteAddr, temp);
            } else {
                norflash_page_write(pBuffer, WriteAddr, NumByteToWrite);
            }
        } else /* NumByteToWrite > W25X_FLASH_PAGE_SIZE */
        {
            NumByteToWrite -= count;
            NumOfPage   = NumByteToWrite / W25X_FLASH_PAGE_SIZE;
            NumOfSingle = NumByteToWrite % W25X_FLASH_PAGE_SIZE;

            norflash_page_write(pBuffer, WriteAddr, count);
            WriteAddr += count;
            pBuffer += count;

            while (NumOfPage--) {
                norflash_page_write(pBuffer, WriteAddr, W25X_FLASH_PAGE_SIZE);
                WriteAddr += W25X_FLASH_PAGE_SIZE;
                pBuffer += W25X_FLASH_PAGE_SIZE;
            }

            if (NumOfSingle != 0) {
                norflash_page_write(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

uint8_t W25Qx_TEST()
{
    return 0;
}