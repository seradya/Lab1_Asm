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

  memset(RxBuffer, 0, 256);
  sysclk_init(); // System clock initializing
  led_init();    // Initializing GPIO port for led
  tim2_init();   // initializing TIM2
  btn_init();    // User button initializingd
  usart_init();  // USART2 initialization
  tim3_afio_init();
  tim3_pwm_init();

  while (true)
  {
    if (CommandReceived)
    {
      ExecuteCommand();
    }
  }
}

void ExecuteCommand(void)
{
  CommandReceived = false;

  if (strncmp(RxBuffer, "*IDN?", 5) == 0)
  {
    strcpy(TxBuffer,"Serebrennikov AN\n\rDobrotinAA\n\rIU4-71B\n\r");
  }
  else if (strncmp(RxBuffer, "LEFT", 4) == 0)
  {
    
    strcpy(TxBuffer, "Ok, LEFT");
    tim3_set_angle(180);
    angle = 180;
  }
  else if (strncmp(RxBuffer, "RIGHT", 5) == 0)
  {
    
    strcpy(TxBuffer, "Ok, RIGHT");
    tim3_set_angle(0);
    angle = 0;
  }
  else if (strncmp(RxBuffer, "ANG ", 4) == 0)
  {
    uint16_t ang;
    sscanf(RxBuffer, "%*s %hu", &ang);
    if (ang > 180)
    {
      strcpy(TxBuffer, "Angle must be in [0:180] range!");
    }
    else
    {
      tim3_set_angle((uint8_t)ang);
      angle = ang;
      strcpy(TxBuffer, "Angle is set.");
    }
  }
  else if (strncmp(RxBuffer, "ANG?", 4) == 0)
  {
    char str[3];
    sprintf(str, "%d", angle);
    strcpy(TxBuffer, "ANG:");
    strcat(TxBuffer, str);
    
  }
  else
  {
    strcpy(TxBuffer, "Unknown command!");
  }

  SendString(TxBuffer);
  memset(RxBuffer, 0, 256);
  memset(TxBuffer, 0, 256);
}

void delay(uint32_t value)
{
  for (volatile uint32_t i = 0; i < value; i++)
    ;
}