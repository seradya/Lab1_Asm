
#include "stm32f1xx.h"
#include "it.h"
#include "gpio.h"
#include "main.h"
#include <string.h>
#include <stdbool.h>

extern bool CommandRecieved;
extern char RxBuffer[256];


void TIM2_IRQHandler(void)
{
    
}

void EXTI0_IRQHandler(void)
{

}

void USART2_IRQHandler(void)
{

}