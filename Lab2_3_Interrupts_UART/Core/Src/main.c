
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "gpio.h"
#include "rcc.h"
#include "usart.h"

bool CommandRecieved;
char RxBuffer[256];
char TxBuffer[256];

int main(void)
{

  memset(RxBuffer,0,256);
  sysclk_init();        //System clock initializing 
  led_init();           //Initializing GPIO port for led
  tim2_init();          //initializing TIM2
  btn_init();           //User button initializingd
  usart_init();         //USART2 initialization

  while(true)
  {
    if(CommandRecieved)
    {
      ExecuteCommand();
    }
  }


}

void ExecuteCommand(void)
{
  CommandRecieved = false;
  SendString(RxBuffer);
  memset(RxBuffer,0,256);
}

void delay(uint32_t value)
{
  for(volatile uint32_t i = 0; i < value; i++);
}