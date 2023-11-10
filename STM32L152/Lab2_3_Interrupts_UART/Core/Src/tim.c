
#include "stm32l1xx.h"
#include "tim.h"

void tim2_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;     //Clock enable fo TIM2

    TIM2->PSC = 32000 - 1;                  //Set prescaler
    TIM2->ARR = 1000 - 1;                   //Set period

    TIM2->DIER |= TIM_DIER_UIE;             //Update interrupt enable
    TIM2->CR1 |= TIM_CR1_CEN;               //Counter enable

    NVIC_SetPriority(TIM2_IRQn, 3);
    NVIC_EnableIRQ(TIM2_IRQn);
    
}