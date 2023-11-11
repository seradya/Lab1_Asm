
#include "stm32f1xx.h"
#include "rcc.h"


void sysclk_init(void)
{
    // Enable HSI
	RCC->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY)){};

	// Enable Prefetch Buffer
	FLASH->ACR |= FLASH_ACR_PRFTBE;

	// Flash 2 wait state
	FLASH->ACR &= ~FLASH_ACR_LATENCY;
	FLASH->ACR |= FLASH_ACR_LATENCY_2;

	// HCLK (AHBCLK) = SYSCLK/1
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	// PCLK2 (APB2CLK) = HCLK/1
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

	// PCLK1 (APB1CLK) = HCLK/1
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;

	// PLL configuration: PLLCLK = HSI/2 * 9 = 36 MHz
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;
	RCC->CFGR |= RCC_CFGR_PLLMULL9;

	// Enable PLL
	RCC->CR |= RCC_CR_PLLON;

	// Wait till PLL is ready
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {};

	// Select PLL as system clock source (SYSCLK = PLLCLK)
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	// Wait till PLL is used as system clock source
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL){};
}