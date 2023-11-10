
#include "stm32l1xx.h"
#include "rcc.h"


void sysclk_init(void)
{
    // Enable HSI
	RCC->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY)){};

    //64 bit flash memory access
    FLASH->ACR |= FLASH_ACR_ACC64;

	// Enable Prefetch
	FLASH->ACR |= FLASH_ACR_PRFTEN;

	// Flash one wait state
	FLASH->ACR |= FLASH_ACR_LATENCY;

	// HCLK = SYSCLK
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	// PCLK2 = HCLK
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

	// PCLK1 = HCLK
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;

	// PLL configuration: PLLCLK = HSI*4/2 = 64 MHz
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;      //HSI sourse
	RCC->CFGR |= RCC_CFGR_PLLMUL4;      //Multiplication factor 4
    RCC->CFGR |= RCC_CFGR_PLLDIV2;      //Division 2

	// Enable PLL
	RCC->CR |= RCC_CR_PLLON;

	// Wait till PLL is ready
	while((RCC->CR & RCC_CR_PLLRDY) == 0) {};

	// Select PLL as system clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	// Wait till PLL is used as system clock source
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL){};
}