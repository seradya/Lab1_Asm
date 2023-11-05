
#include <stdbool.h>
#include "main.h"
#include "gpio.h"
#include "rcc.h"

int main(void)
{

  sysclk_init();        //System clock initializing 
  led_init();           //Initializing GPIO port for led
  tim2_init();          //initializing TIM2

  while(true)
  {

  }


}

void delay(uint32_t value)
{
  for(volatile uint32_t i = 0; i < value; i++);
}