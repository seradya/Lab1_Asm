
#include "stm32f1xx.h"
#include "tim.h"

void tim2_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;		//Включить тактирование TIM6

	//Частота APB1 для таймеров = APB1Clk * 2 = 32МГц * 2 = 64МГц
	TIM2->PSC = 64000-1;					//Предделитель частоты (64МГц/64000 = 1кГц)
	TIM2->ARR = 1000-1;						//Модуль счёта таймера (1кГц/1000 = 1с)
	TIM2->DIER |= TIM_DIER_UIE;				//Разрешить прерывание по переполнению таймера
	TIM2->CR1 |= TIM_CR1_CEN;				//Включить таймер

	NVIC_EnableIRQ(TIM2_IRQn);				//Рарзрешить прерывание от TIM2
	NVIC_SetPriority(TIM2_IRQn, 1);			//Выставляем приоритет
}

tim3_pwm_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;		//Включить тактирование TIM3

	//Частота APB1 для таймеров = APB1Clk * 2 = 32МГц * 2 = 64МГц
	TIM3->PSC = 64000-1;										//Предделитель частоты (64МГц/64000 = 1кГц)
	TIM3->ARR = 100-1;											//Модуль счёта таймера (1кГц/1000 = 1с)
	TIM3->CCR2 = 50-1;											//на каком числе переключение
	TIM3->CCER |= TIM_CCER_CC2E;								//разблокируем выход
	TIM3->CCMR1 |= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);		//режим ШИМ1									
	TIM3->CR1 |= TIM_CR1_CEN;									//Включить таймер
	

}