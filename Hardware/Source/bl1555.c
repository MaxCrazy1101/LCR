#include "bl1555.h"
void bl1555_config()
{
    uint32_t config_pin  = GPIO_PIN_8;
    uint32_t config_port = GPIOA;
    /* PA8 */
    gpio_mode_set(config_port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, config_pin);
    gpio_output_options_set(config_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, config_pin);
}