
#include "stm32l1xx.h"
#include "it.h"
#include "gpio.h"
#include "main.h"

void TIM2_IRQHandler(void)
{
    TIM2->SR &= ~TIM_SR_UIF;        //Clearing update interrupt flag
    LED_SWAP();
}

void EXTI0_IRQHandler(void)
{
    delay(1000);                    //Debouncing
    EXTI->PR |= EXTI_PR_PR0;        //Clearing trigger request
    TIM2->CR1 ^= TIM_CR1_CEN;       //Toggle TIM2
}