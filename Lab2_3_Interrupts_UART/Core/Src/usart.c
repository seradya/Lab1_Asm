
#include "stm32l1xx.h"
#include "usart.h"
#include "string.h"



void usart_init(void)
{
    //PA2 - Tx, PA3 -Rx
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;       //Clock enable for usart2 
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;          //Clock enable for GPIOA

    GPIOA->MODER &= ~GPIO_MODER_MODER2;         //PA2 Mode bits reset
    GPIOA->MODER &= ~GPIO_MODER_MODER3;         //PA3 Mode bits reset
    GPIOA->MODER |= GPIO_MODER_MODER2_1;        //PA2 alternate function
    GPIOA->MODER |= GPIO_MODER_MODER3_1;        //PA2 alternate function
    GPIOA->AFR[0] &=  ~GPIO_AFRL_AFSEL2;        //GPIO AFRL PA2 reset bits
    GPIOA->AFR[0] &=  ~GPIO_AFRL_AFSEL3;        //GPIO AFRL PA2 reset bits         
    GPIOA->AFR[0] |= 0x7 << 8;                  //Set AF7 for port 2
    GPIOA->AFR[0] |= 0x7 << 12;                 //Set AF7 for port 3

    //APB2 CLK = 32 MHx => BRR value = 17.4
    //17 = 0x11; 0.4*16 = 6.4 => 0x116
    USART2->BRR = 0x116;                        //Baud rate register value
    USART2->CR1 |= USART_CR1_TE;                //Enable transmitter
    USART2->CR1 |= USART_CR1_RE;                //Enable reciever
    USART2->CR1 |= USART_CR1_UE;                //Enable USART
    USART2->CR1 |= USART_CR1_RXNEIE;            //Enbale interrupt when rx not empty

    NVIC_SetPriority(USART2_IRQn, 1);
    NVIC_EnableIRQ(USART2_IRQn);


}

void SendString(char *str)
{
    strcat(str, "\r\n");
    USART2->SR &= ~USART_SR_TC;
    for(uint8_t i = 0; i < strlen(str); i++)
    {
        USART2->DR = str[i];
        while((USART2->SR & USART_SR_TC)==0);
    }
}