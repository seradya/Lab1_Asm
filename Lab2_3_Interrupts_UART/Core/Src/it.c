
#include "stm32l1xx.h"
#include "it.h"
#include "gpio.h"
#include "main.h"
#include <string.h>
#include <stdbool.h>

extern bool CommandRecieved;
extern char RxBuffer[256];


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

void USART2_IRQHandler(void)
{
    
    if((USART2->SR & USART_SR_RXNE) != 0)
    {
        uint8_t pos = strlen(RxBuffer);
        RxBuffer[strlen(RxBuffer)] = USART2->DR;
        if (RxBuffer[pos]==0x0A && (RxBuffer[pos-1] == 0x0D) )
        {
            CommandRecieved = true;
            return;
        }
    }
}