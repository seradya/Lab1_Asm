
#include "stm32f1xx.h"
#include "usart.h"
#include "string.h"

void usart_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	  // вкл тактирование GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;	  // включить тактирование альтернативных ф-ций портов
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // включить тактирование UART2

	GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2); // очистка настройки PA2
	GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1); // alternate func, output 2 MHz

	GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3); // PA3 - вход
	GPIOA->CRL |= GPIO_CRL_CNF3_0;

	/*****************************************
	Скорость передачи данных - 115200
	Частота шины APB1 - 36МГц

	1. USARTDIV = 36'000'000/(16*57600) = 39.0
	2. 39 = 0x27
	3. 16*0 = 0
	4. Итого 0x270
	*****************************************/
	USART2->BRR = 0x270;

	USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
	USART2->CR1 |= USART_CR1_RXNEIE; // разрешить прерывание по приему байта данных

	NVIC_EnableIRQ(USART2_IRQn);
}

void SendString(char *str)
{
	uint16_t i;

	strcat(str, "\r\n"); // добавляем символ конца строки

	for (i = 0; i < strlen(str); i++)
	{
		USART2->DR = str[i]; // передаём байт данных
		while ((USART2->SR & USART_SR_TC) == 0)
		{
		}; // ждём окончания передачи
	}
}