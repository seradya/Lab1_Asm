
#include "stm32f1xx.h"
#include "gpio.h"

void led_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	//включить тактирование GPIOA

	//очистка полей
	GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
	//и конфигурация
	GPIOA->CRL |= GPIO_CRL_MODE5_1;		//PA5, выход 2МГц
}

void led_init_pwm(void)
{
	//Pin PA7 (TIM3_CN2)
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;						//включить тактирование GPIOA
	GPIOA->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);		//очистка полей
	GPIOA->CRL |= GPIO_CRL_MODE7_1;							//и конфигурация PA5, выход 2МГц
	GPIOA->CRL |= GPIO_CRL_CNF7_1;							//Alternate function push-pullS
}

void btn_init(void)
{
    //Включить тактирование порта GPIOC и альтернативных функций
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;

	/* Настраиваем PC13 на вход, альтернативная функция */
	// Сбрасываем биты конфигурации порта...
	GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
	//...и выставляем так, как нам нужно
	GPIOC->CRH |= GPIO_CRH_CNF13_1;			//Вход с подтяжкой
	GPIOC->BSRR |= GPIO_BSRR_BS13;			//Подтяжка к Vdd

	/* Настройка самого прерывания */

	// Настройка альтернативных фукнций портов.
	// Настройки портов с 12 по 15 хранятся в регистре AFIO_EXTICR4.
	// Регистры объединены в массив AFIO->EXTICR, нумерация массива начинается с нулевого элемента.
	// Поэтому настройки AFIO_EXTICR4 хранятся в AFIO->EXTICR[3]
	AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI13_PC;

	EXTI->FTSR |= EXTI_FTSR_TR13;			//Прерывание по спаду импульса (при нажатии на кнопку)
	EXTI->IMR |= EXTI_IMR_MR13;				//Выставляем маску - EXTI13

	NVIC_EnableIRQ(EXTI15_10_IRQn);			//Разрешаем прерывание
	NVIC_SetPriority(EXTI15_10_IRQn, 0);	//Выставляем приоритет
}