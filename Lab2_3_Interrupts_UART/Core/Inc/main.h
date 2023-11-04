
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32l1xx.h"

#define LED_ON()    GPIOB->BSRR = GPIO_BSRR_BS_7;     //Turn led on
#define LED_OFF()    GPIOB->BSRR = GPIO_BSRR_BR_7;    //Turn led off
#define LED_SWAP()    GPIOB->ODR ^= GPIO_ODR_ODR_7;   //Toggle led

void delay(uint32_t value);

#endif /* __MAIN_H */
