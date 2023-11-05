
#include "stm32l1xx.h"
#include "it.h"
#include "gpio.h"

void TIM2_IRQHandler(void)
{
    TIM2->SR &= ~TIM_SR_UIF;
    LED_SWAP();
}