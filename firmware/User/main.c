/**
 ******************************************************************************
 * @file    main.c
 * @author  MCU Application Team
 * @brief   Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
 * All rights reserved.</center></h2>
 *
 * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
  * Badge 8.8

  Modified by Electronic Cats - Yoshio Garcia (YoshiDev22)
  Modifications:
  - LED sequences added
  - Add Function: HAL_GPIO_OnPin
  - Add Function: HAL_GPIO_OffPin
  - Adding pin definition arrays


 */

// Badge 8.8

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx_bsp_printf.h"
#include <stdint.h>

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t delay0 = 10, delay = 50, delay2 = 250, delay3 = 100, delay4 = 25, delay5=1000;
uint16_t delay1 = 600, interimPeriod = 100;
uint8_t times = 0, init = 0;
uint8_t sequenceNumber = 1, timesSecretCode = 2, bitNumber = 0;
uint8_t ledQuantity = 5;          //Set how many LED have your Shitty Addon

// Pin Definition 
uint32_t ports[] = {GPIOA, GPIOA, GPIOA, GPIOF, GPIOA};
uint8_t pins[] = {0x0020, 0x0002, 0x0080, 0x0001, 0x0040}; // PA5, PA1, PA7, PF0, PA6  - Each Badge have its own order. Indicator=PA6
uint8_t indicatorPos=4;

uint8_t message[] = {"8.8"};    //Secret Code


/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_LedConfig(void);


// Functions
void HEX2NIBBLE()
{
  uint8_t nibble1, nibble2;
  for (uint8_t i = 0; i < sizeof(message) - 1; i++)
  {
    nibble1 = message[i] & 0x0F;
    nibble2 = message[i] >> 4;
    bitNumber += 1;
    blinkBitNumber();
    setBits(nibble1);
    setBits(nibble2);
    ledsOff();
  }
}

void setBits(uint8_t nibble)
{
  uint8_t nibbleAux = nibble;
  for (uint8_t i = 0; i < 4; i++)
  {
    if (nibbleAux & 0x01) // LED ON
    {
      HAL_GPIO_OnPin(ports[i], pins[i]);
    }
    else
    {
      HAL_GPIO_OffPin(ports[i], pins[i]);
    }
    nibbleAux = nibble >> i + 1;
  }
  HAL_Delay(750);
}

void blinkBitNumber()
{
  for (uint8_t i = 0; i < 2; i++)
  {
    HAL_GPIO_OnPin(ports[indicatorPos], pins[indicatorPos]);
    HAL_Delay(delay2);
    HAL_GPIO_OffPin(ports[indicatorPos], pins[indicatorPos]);
    HAL_Delay(delay2);
  }
}

// Sequence 1
void crossSequence()
{
  HAL_GPIO_OnPin(ports[0], pins[0]); // Start with PA5
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(ports[0], pins[0]);
  HAL_GPIO_OnPin(ports[2], pins[2]);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(ports[2], pins[2]);
  HAL_GPIO_OnPin(ports[1], pins[1]);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(ports[1], pins[1]);
  HAL_GPIO_OnPin(ports[3], pins[3]);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(ports[3], pins[3]); // Turn off PF0
  HAL_Delay(delay2);
}

void crossSequence2()
{
  HAL_GPIO_OnPin(ports[0], pins[0]); // Start with PF0
  HAL_GPIO_OnPin(ports[2], pins[2]); // Start with PA7
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(ports[0], pins[0]);
  HAL_GPIO_OffPin(ports[2], pins[2]);
  HAL_GPIO_OnPin(ports[1], pins[1]);
  HAL_GPIO_OnPin(ports[3], pins[3]);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(ports[1], pins[1]);
  HAL_GPIO_OffPin(ports[3], pins[3]);
}

void followSequence()
{
  HAL_GPIO_OnPin(ports[0], pins[0]); // Start with PA5
  HAL_Delay(delay3);
  HAL_GPIO_OnPin(ports[1], pins[1]);
  HAL_GPIO_OnPin(ports[3], pins[3]);
  HAL_Delay(delay3);
  HAL_GPIO_OffPin(ports[0], pins[0]); // Turn off PA5
  HAL_GPIO_OnPin(ports[2], pins[2]);
  HAL_Delay(delay3);
  HAL_GPIO_OffPin(ports[1], pins[1]); // Turn off PA5
  HAL_GPIO_OffPin(ports[3], pins[3]);
  HAL_Delay(delay3);
  HAL_GPIO_OffPin(ports[2], pins[2]); // Turn off PA7
  HAL_Delay(delay3);
  //Reverse
  /*HAL_GPIO_OnPin(ports[2], pins[2]); // Start with PA7
  HAL_Delay(delay3);
  HAL_GPIO_OnPin(ports[1], pins[1]);
  HAL_GPIO_OnPin(ports[3], pins[3]);
  HAL_Delay(delay3);
  HAL_GPIO_OffPin(ports[2], pins[2]); 
  HAL_GPIO_OnPin(ports[0], pins[0]);
  HAL_Delay(delay3);
  HAL_GPIO_OffPin(ports[1], pins[1]); 
  HAL_GPIO_OffPin(ports[3], pins[3]);
  HAL_Delay(delay3);
  HAL_GPIO_OffPin(ports[0], pins[0]); // Turn off PA5
  HAL_Delay(delay2);*/
}

void fastFlash()
{
  HAL_GPIO_OnPin(ports[0], pins[0]); // Start with PA5
  HAL_Delay(delay);
  HAL_GPIO_OnPin(ports[1], pins[1]);
  HAL_GPIO_OnPin(ports[3], pins[3]);
  HAL_Delay(delay);
  HAL_GPIO_OffPin(ports[0], pins[0]); // Turn off PA5
  HAL_GPIO_OnPin(ports[2], pins[2]);
  HAL_Delay(delay);
  HAL_GPIO_OffPin(ports[1], pins[1]); // Turn off PA5
  HAL_GPIO_OffPin(ports[3], pins[3]);
  HAL_Delay(delay);
  HAL_GPIO_OffPin(ports[2], pins[2]); // Turn off PA7
  HAL_Delay(delay);
}
/*
void planeSequence()
{
  HAL_GPIO_OnPin(ports[1], pins[1]);
  HAL_Delay(delay1);
  HAL_GPIO_OnPin(ports[2], pins[2]);
  HAL_Delay(delay1);
  HAL_GPIO_OnPin(ports[3], pins[3]);
  HAL_Delay(delay1);
  for (int8_t i = 0; i < 5; i++)
  {
    togglePlane();
  }
}

void togglePlane()
{
  HAL_GPIO_TogglePin(ports[1], pins[1]);
  HAL_GPIO_TogglePin(ports[2], pins[2]);
  HAL_GPIO_TogglePin(ports[3], pins[3]);
  HAL_Delay(delay1);
}

// Sequence 2
void planeSequence2()
{
  HAL_GPIO_OnPin(ports[1], pins[1]);
  HAL_Delay(delay3);
  HAL_GPIO_OnPin(ports[3], pins[3]);
  HAL_GPIO_OnPin(ports[0], pins[0]);
  HAL_Delay(delay3);
  HAL_GPIO_OffPin(ports[1], pins[1]);
  HAL_Delay(delay3);
  HAL_GPIO_OnPin(ports[4], pins[4]);
  HAL_GPIO_OffPin(ports[3], pins[3]);
  HAL_GPIO_OffPin(ports[0], pins[0]);
  HAL_Delay(delay3);
  HAL_GPIO_OffPin(ports[4], pins[4]);
  HAL_Delay(delay3);
}

// Sequence 3
void rowSequence()
{
  HAL_GPIO_OnPin(ports[2], pins[2]);
  HAL_Delay(delay3);
  HAL_GPIO_OnPin(ports[1], pins[1]);
  HAL_GPIO_OnPin(ports[3], pins[3]);
  HAL_Delay(delay0);
  HAL_GPIO_OffPin(ports[2], pins[2]);
  HAL_Delay(delay3);
  HAL_GPIO_OnPin(ports[0], pins[0]);
  HAL_GPIO_OnPin(ports[4], pins[4]);
  HAL_Delay(delay0);
  HAL_GPIO_OffPin(ports[1], pins[1]);
  HAL_GPIO_OffPin(ports[3], pins[3]);
  HAL_Delay(delay3);
  HAL_GPIO_OffPin(ports[0], pins[0]);
  HAL_GPIO_OffPin(ports[4], pins[4]);
  HAL_Delay(delay3);
}
*/
// Seqeuence 7
void blinkSequence()
{
  ledsOn();
  HAL_Delay(delay1);
  ledsOff();
  HAL_Delay(delay1);
}

//Sequence 4
void circleSequence()
{
  int8_t i = 0;
  //Forward
  for (i; i < 5; i++)
  {
    uint8_t j=i;
    if (i>0)
    {
      j=i-1;
    }
    HAL_GPIO_OffPin(ports[j], pins[j]);
    HAL_Delay(delay);
    HAL_GPIO_OnPin(ports[i], pins[i]);
    HAL_Delay(delay);
  }

  //Reverse
  i=3;
  for (i; i >= 0; i--)
  {
    uint8_t j=i;
    if (i>=0)
    {
      j=i+1;
    }
    HAL_GPIO_OffPin(ports[j], pins[j]);
    HAL_Delay(delay);
    HAL_GPIO_OnPin(ports[i], pins[i]);
    HAL_Delay(delay);
  }
  i++;
  HAL_GPIO_OffPin(ports[i], pins[i]);
  HAL_Delay(delay);

}


//General Function to turn Off all LEDs
void ledsOff()
{
  for (uint8_t i = 0; i < ledQuantity; i++)
  {
    HAL_GPIO_OffPin(ports[i], pins[i]);
  }
}

//General Function turn On all LEDs
void ledsOn()
{
  for (uint8_t i = 0; i < ledQuantity; i++)
  {
    HAL_GPIO_OnPin(ports[i], pins[i]);
  }
}

//Sequence 5
void randomSequence()
{ 
  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_7);
  HAL_GPIO_OnPin(GPIOF, GPIO_PIN_0);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_7);
  HAL_GPIO_OffPin(GPIOF, GPIO_PIN_0);
  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_5); 
  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_1);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_5); 
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_1);
  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_6);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_6);
  HAL_Delay(delay2);

  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_6);
  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_1);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_1);
  HAL_GPIO_OnPin(GPIOF, GPIO_PIN_0);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(GPIOF, GPIO_PIN_0);
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_6);
  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_7);
  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_5); 
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_7);
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_5);
  HAL_Delay(delay2);

  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_1);
  HAL_GPIO_OnPin(GPIOF, GPIO_PIN_0);
  HAL_Delay(delay2);
  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_7);
  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_5); 
  HAL_Delay(delay2);
  HAL_GPIO_OnPin(GPIOA, GPIO_PIN_6);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_1);
  HAL_GPIO_OffPin(GPIOF, GPIO_PIN_0);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_7);
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_5);
  HAL_Delay(delay2);
  HAL_GPIO_OffPin(GPIOA, GPIO_PIN_6);
}

//Sequence 6
void rouletteSequence()
{
  uint8_t i=0;    //initial
  /*uint8_t f=4;    //final
  if (indicatorPos==0)
  {
    i=1;
    f=5;
  }*/

  //Forward
  HAL_GPIO_OnPin(ports[i], pins[i]);
  HAL_Delay(delay);
  for (i; i < 5; i++)
  {
    HAL_GPIO_OnPin(ports[i], pins[i]);
    HAL_Delay(delay);
  }
  i--;
  //Reverse
  for (i; i > 0; i--)
  {
    HAL_GPIO_OffPin(ports[i], pins[i]);
    HAL_Delay(delay);
  }
  HAL_GPIO_OffPin(ports[i], pins[i]);
  HAL_Delay(delay);
}


void sequences(int sequence)
{
  switch (sequence)
  {
  case 1:
  for (uint8_t c = 1; c < 5; c++)
    {
      crossSequence();
    }
    break;
  case 2:
    for (uint8_t c = 1; c < 8; c++)
    {
      crossSequence2();
    }
    break;
  case 3:
    for (uint8_t c = 1; c < 4; c++)
    {
      followSequence();
    }
    break;
  case 4:
    for (uint8_t c = 1; c < 8; c++)
    {
      fastFlash();
    }
    break;
    
  case 5:
    for (uint8_t c = 1; c < 3; c++)
    {
      circleSequence();
    }
    break;
  case 6:
  for (uint8_t c = 1; c < 3; c++)
    {
    randomSequence();
    }
    break;
  case 7:
  for (uint8_t c = 1; c < 4; c++)
    {
    rouletteSequence();
    }
    break;
  case 8:
    for (uint8_t c = 1; c < 4; c++)
    {
      blinkSequence();
    }
    break;
  default:
    ledsOn();
    sequenceNumber = 1;
    break;
  }
}

int main(void)
{
  HAL_Init();

  APP_LedConfig();

  BSP_USART_Config();

  while (1)
  {
    //ledsOn();
    //HAL_Delay(delay2);
    //ledsOff();
    //HAL_Delay(delay2);
    //allLEDs();
    //rowSequence();
    //blinkSequence();
    //sequences(4);
    //rouletteSequence();
  
    //planeSequence();
    for (uint8_t c = 1; c < 8; c++)
    {
      sequences(c);
      //HAL_Delay(delay2);
    }
  
    for (uint8_t c2 = 0; c2 < timesSecretCode; c2++)
    {
      sequences(8); // Blink Sequence 3 times
      ledsOff();
      HAL_Delay(interimPeriod);
      HEX2NIBBLE();
      HAL_Delay(interimPeriod);
      sequences(4);
    }/**/
  }
}

static void APP_LedConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  __HAL_RCC_GPIOA_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  __HAL_RCC_GPIOF_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
}

void APP_ErrorHandler(void)
{
  while (1)
    ;
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
