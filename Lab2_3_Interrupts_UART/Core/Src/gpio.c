
#include "stm32l1xx.h"
#include "gpio.h"

void led_init(void)
{
    //PB7
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;              //Clock enable for GPIOB

    GPIOB->MODER &= ~GPIO_MODER_MODER7;              //Reset PB7 bits in GPIO_MODER register
    GPIOB->MODER |= GPIO_MODER_MODER7_0;            //Enable output mode for PB7

}

void btn_init(void)
{
    //PA0
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;              //Clock enable for GPIOA
    GPIOA->MODER &= ~GPIO_MODER_MODER0;              //Enable input mode 
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0;              //No pull-up, no pull down

    EXTI->IMR |= EXTI_IMR_MR0;                      //Interrupt request from line 0 is not masked
    EXTI->RTSR |= EXTI_RTSR_TR0;                    //Rising edge trigger enable for line 0

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;           //System configuraton controller clock enable
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;     //Reset EXTI0 bits
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;   //Select PAx source for EXTI0
    
    NVIC_SetPriority(EXTI0_IRQn, 2);
    NVIC_EnableIRQ(EXTI0_IRQn);

}