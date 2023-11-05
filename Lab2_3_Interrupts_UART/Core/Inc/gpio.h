#ifndef __GPIO_H
#define __GPIO_H

#define LED_ON()    GPIOB->BSRR = GPIO_BSRR_BS_7;     //Turn led on
#define LED_OFF()    GPIOB->BSRR = GPIO_BSRR_BR_7;    //Turn led off
#define LED_SWAP()    GPIOB->ODR ^= GPIO_ODR_ODR_7;   //Toggle led

void led_init(void);

#endif /* __GPIO_H */