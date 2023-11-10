
#include "stm32f1xx.h"
#include "it.h"
#include "gpio.h"
#include "main.h"
#include <string.h>
#include <stdbool.h>

extern bool CommandReceived;
extern char RxBuffer[256];


void TIM2_IRQHandler(void)
{
    TIM2->SR &= ~TIM_SR_UIF;			//Сброс флага переполнения
	LED_SWAP();
}

void EXTI15_10_IRQHandler(void)
{
    // Т.к. этот обработчик вызывается, если произшло одно из прерываний EXTI15-EXI10,
	// нужно проверить, кто из них его вызвал.
	if (EXTI->PR & EXTI_PR_PR13) 		// нас интересует EXTI13
	{
		EXTI->PR |= EXTI_PR_PR13;
		delay(10000);					//Задержка для защиты от дребезга контактов
		TIM2->CR1 ^= TIM_CR1_CEN;		//Инвертируем состояние таймера
	}
}

void USART2_IRQHandler(void)
{
    if ((USART2->SR & USART_SR_RXNE)!=0)		//Прерывание по приёму данных?
	{
		uint8_t pos = strlen(RxBuffer);			//Вычисляем позицию свободной ячейки

		RxBuffer[pos] = USART2->DR;				//Считываем содержимое регистра данных

		if ((RxBuffer[pos]== 0x0A) && (RxBuffer[pos-1]== 0x0D))							//Если это символ конца строки
		{
			CommandReceived = true;					//- выставляем флаг приёма строки
			return;								//- и выходим
		}
	}
}