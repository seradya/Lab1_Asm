
#include "stm32f1xx.h"
#include "tim.h"

#define TIM3_CLK 1800000

extern uint8_t angle;

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

void tim3_pwm_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;		//Включить тактирование TIM3

	//Частота APB1 для таймеров = APB1Clk * 2 = 32МГц * 2 = 64МГц
	TIM3->PSC = 20-1;										//Предделитель частоты (64МГц/64000 = 1кГц)
	//TIM3->ARR = 100-1;											//Модуль счёта таймера (1кГц/1000 = 1с)
	//TIM3->CCR2 = 50-1;											//на каком числе переключение
	tim3_set_freq(50);
	tim3_set_angle(0);
	TIM3->CCER |= TIM_CCER_CC2E;								//разблокируем выход
	TIM3->CCMR1 |= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2PE);		//режим ШИМ1 + preload en									
	TIM3->CR1 |= TIM_CR1_CEN;									//Включить таймер

}

void tim3_set_freq(uint8_t freq_HZ)
{
	TIM3->ARR = (uint16_t)((TIM3_CLK)/freq_HZ);
}

void tim3_set_angle(uint8_t angle_deg)
{
	TIM3->CCR2 = (uint16_t)(1350 + (angle_deg*19));
	angle = angle_deg;
}