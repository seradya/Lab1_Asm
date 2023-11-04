
#include "stm32l1xx.h"
#include "gpio.h"

void led_init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;      //Clock enable for GPIOB
    GPIOB->MODER &= GPIO_MODER_MODER7;      //Reser PB7 bits in GPIO_MODER register
    GPIOB->MODER |= GPIO_MODER_MODER7_0;    //Enable output mode for PB7

}