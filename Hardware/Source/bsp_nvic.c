#include "bsp_nvic.h"

void nvic_config(void)
{
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
    // nvic_irq_enable(ADC_IRQn, 11, 0);
}