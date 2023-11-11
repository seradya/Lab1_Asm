#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "gpio.h"
#include "rcc.h"
#include "usart.h"

bool CommandReceived;
char RxBuffer[256];
char TxBuffer[256];
uint8_t angle;


int main(void)
{

  memset(RxBuffer,0,256);
  sysclk_init();        //System clock initializing 
  led_init();           //Initializing GPIO port for led
  led_init_pwm();       //Initialize GPIO for PWM

  //tim2_init();          //initializing TIM2
  tim3_pwm_init();      //Init TIM3 in PWM mode

  btn_init();           //User button initializingd
  usart_init();         //USART2 initialization

  while(true)
  {
    if(CommandReceived)
    {
      ExecuteCommand();
    }
  }


}

void ExecuteCommand(void)
{
  CommandReceived = false;

  if(strncmp(RxBuffer, "*IDN?", 5) == 0)
  {
    strcpy(TxBuffer,"BMSTU, IU4, Lab3");
  }

  else if(strncmp(RxBuffer, "Start", 5) == 0)
  {
    TIM2->CR1 |= TIM_CR1_CEN;
    strcpy(TxBuffer,"Ok, start");
  }

  else if(strncmp(RxBuffer, "Stop", 4) == 0)
  {
    TIM2->CR1 &= ~TIM_CR1_CEN;
    strcpy(TxBuffer,"Ok, stop");
  }

  else if(strncmp(RxBuffer, "Period", 6) == 0)
  {
    //Period 1000
    uint16_t tmp;
    sscanf(RxBuffer, "%*s %hu", &tmp);
    if((tmp >= 100) && (tmp <= 5000))
    {
      TIM2->ARR = tmp - 1;
      TIM2->CNT = 0;
      strcpy(TxBuffer,"Ok, period is set");
    }
    else
    {
      strcpy(TxBuffer,"Period out of range!");
    }
    
  }

  else
  {
    strcpy(TxBuffer,"Unknown command!");
  }


  SendString(TxBuffer);
  memset(RxBuffer,0,256);
  memset(TxBuffer,0,256);
}

void delay(uint32_t value)
{
  for(volatile uint32_t i = 0; i < value; i++);
}