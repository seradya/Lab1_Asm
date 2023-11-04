
#include <stdbool.h>
#include "main.h"
#include "gpio.h"

int main(void)
{

  led_init();           //Initializing GPIO port for led

  while(true)
  {
    LED_SWAP();
    delay(100000);
  }


}

void delay(uint32_t value)
{
  for(volatile uint32_t i = 0; i < value; i++);
}