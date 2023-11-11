
#include "stm32f1xx.h"
#include "usart.h"
#include "string.h"



void usart_init(void)
{    //PA2 - Tx, PA3 -Rx    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;       //Clock enable for usart2     RCC->AHBENR |= RCC_AHBENR_GPIOAEN;          //Clock enable for GPIOA    GPIOA->MODER &= ~GPIO_MODER_MODER2;         //PA2 Mode bits reset    GPIOA->MODER &= ~GPIO_MODER_MODER3;         //PA3 Mode bits reset    GPIOA->MODER |= GPIO_MODER_MODER2_1;        //PA2 alternate function    GPIOA->MODER |= GPIO_MODER_MODER3_1;        //PA2 alternate function    GPIOA->AFR[0] &=  ~GPIO_AFRL_AFSEL2;        //GPIO AFRL PA2 reset bits    GPIOA->AFR[0] &=  ~GPIO_AFRL_AFSEL3;        //GPIO AFRL PA2 reset bits             GPIOA->AFR[0] |= 0x7 << 8;                  //Set AF7 for port 2    GPIOA->AFR[0] |= 0x7 << 12;                 //Set AF7 for port 3    //APB2 CLK = 32 MHx => BRR value = 17.4    //17 = 0x11; 0.4*16 = 6.4 => 0x116    USART2->BRR = 0x116;                        //Baud rate register value    USART2->CR1 |= USART_CR1_TE;                //Enable transmitter    USART2->CR1 |= USART_CR1_RE;                //Enable reciever    USART2->CR1 |= USART_CR1_UE;                //Enable USART    USART2->CR1 |= USART_CR1_RXNEIE;            //Enbale interrupt when rx not empty    NVIC_SetPriority(USART2_IRQn, 1);    NVIC_EnableIRQ(USART2_IRQn);
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;						//включить тактирование альтернативных ф-ций портов
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;					//включить тактирование UART2

	GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);		//PA2 на выход
	GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_CNF2_1);

	GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);		//PA3 - вход
	GPIOA->CRL |= GPIO_CRL_CNF3_0;

	/*****************************************
	Скорость передачи данных - 115200
	Частота шины APB1 - 36МГц

	1. USARTDIV = 32'000'000/(16*57600) = 39.0
	2. 34 = 0x27
	3. 16*0 = 0
	4. Итого 0x270
	*****************************************/
	USART2->BRR = 0x270;

	USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
	USART2->CR1 |= USART_CR1_RXNEIE;						//разрешить прерывание по приему байта данных

	NVIC_EnableIRQ(USART2_IRQn);
}

void SendString(char *str)
{
    uint16_t i;

	strcat(str,"\r\n");									//добавляем символ конца строки

	for (i = 0; i < strlen(str); i++)
	{
		USART2->DR = str[i];								//передаём байт данных
		while ((USART2->SR & USART_SR_TC)==0) {};			//ждём окончания передачи
	}
}