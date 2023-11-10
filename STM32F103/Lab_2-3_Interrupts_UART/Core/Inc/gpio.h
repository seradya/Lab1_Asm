#ifndef __GPIO_H
#define __GPIO_H

#define	LED_ON()		GPIOA->BSRR = GPIO_BSRR_BS5
#define	LED_OFF()		GPIOA->BSRR = GPIO_BSRR_BR5
#define LED_SWAP()		GPIOA->ODR ^= GPIO_ODR_ODR5

void led_init(void);
void btn_init(void);
void led_init_pwm(void);

#endif /* __GPIO_H */