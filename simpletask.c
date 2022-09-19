/* simpletask.c:
    Author : Naren Subburaj and Pritesh Panchal 
 */
 
 #include <stdio.h>
 #include <stdint.h>
 #include "common.h"


static uint32_t counter = 0;

void gpiob_init(void)
{
  RCC->AHB1ENR |= (1U<<1);

  GPIOB->MODER |= (1U<<6);
  GPIOB->MODER &=~(1U<<7);

  GPIOB->MODER |= (1U<<8);
  GPIOB->MODER &=~(1U<<9);

  GPIOB->MODER |= (1U<<10);
  GPIOB->MODER &=~(1U<<11);

  GPIOB->MODER |= (1U<<20);
  GPIOB->MODER &=~(1U<<21);
}

void pwm_SPEAKERinit(void)
{
  RCC->AHB1ENR |= (1U<<0);

  GPIOA->MODER |= (1U<<11);
  GPIOA->MODER &=~(1U<<10);

  GPIOA->AFR[0] |= (1U<<20);
  GPIOA->AFR[0] &=~(1U<<21);
  GPIOA->AFR[0] &=~(1U<<22);
  GPIOA->AFR[0] &=~(1U<<23);

  RCC->APB1ENR |= (1U<<0);

  TIM2->PSC = 50 - 1;

  TIM2->ARR = 0;

  TIM2->CNT = 0;

  TIM2->CCMR1 |= (1U<<4);
  TIM2->CCMR1 |= (1U<<5);
  TIM2->CCMR1 &=~(1U<<6);

  TIM2->CCMR1 &=~(1U<<0);
  TIM2->CCMR1 &=~(1U<<1);

  TIM2->CCER = (1U<<0);


  TIM2->CCR1 = 30;

  TIM2->CR1 |= (1U<<0);

}

static uint32_t counter;

void TaskCounter(void)
{
  if(counter >=1 && counter <=10 ){
    if(counter >=0){
    
    printf("The counter is %ld\n",counter);
    switch(counter)
  { 
  case 1:
  //speaker = 300;
      TIM2->ARR = 300 - 1;
      GPIOB->ODR &=~(1U<<3);
      GPIOB->ODR &=~(1U<<5);
      GPIOB->ODR &=~(1U<<4);
      GPIOB->ODR |= (1U<<10);
      GPIOA->ODR &=~ (1U<<5);
      break;
      
  case 2:
  // speaker = 400;
  TIM2->ARR = 400 - 1;
      GPIOB->ODR &=~ (1U<<3);
      GPIOB->ODR &=~(1U<<5);
      GPIOB->ODR |= (1U<<4);
      GPIOB->ODR &=~(1U<<10);
      break;

  case 3:
   //speaker = 500;
    TIM2->ARR = 500 - 1;
      GPIOB->ODR &=~ (1U<<3);
      GPIOB->ODR &=~ (1U<<5);
      GPIOB->ODR |= (1U<<4);
      GPIOB->ODR |= (1U<<10);
      break;
      
  case 4:
  // speaker = 600;
     TIM2->ARR = 600 - 1;
      GPIOB->ODR &=~(1U<<3);
      GPIOB->ODR |= (1U<<5);
      GPIOB->ODR &=~(1U<<4);
      GPIOB->ODR &=~(1U<<10);
      break;

  case 5:
  // speaker = 700;
    TIM2->ARR = 700 - 1;
      GPIOB->ODR &=~(1U<<3);
      GPIOB->ODR |= (1U<<5);
      GPIOB->ODR &=~(1U<<4);
      GPIOB->ODR |= (1U<<10);
      break;

  case 6:
   //speaker = 800;
    TIM2->ARR = 800 - 1;
      GPIOB->ODR &=~(1U<<3);
      GPIOB->ODR |= (1U<<5);
      GPIOB->ODR |= (1U<<4);
      GPIOB->ODR &=~(1U<<10);
      break;

  case 7:
  // speaker = 900;
    TIM2->ARR = 900 - 1;
      GPIOB->ODR &=~(1U<<3);
      GPIOB->ODR |= (1U<<5);
      GPIOB->ODR |= (1U<<4);
      GPIOB->ODR |= (1U<<10);
      break;

  case 8:
  // speaker = 1000;
  TIM2->ARR = 1000 - 1;
      GPIOB->ODR |= (1U<<3);
      GPIOB->ODR &=~(1U<<5);
      GPIOB->ODR &=~(1U<<4);
      GPIOB->ODR &=~(1U<<10);
      break;

  case 9:
   //speaker = 1100;
  TIM2->ARR = 1100 - 1;
      GPIOB->ODR |= (1U<<3);
      GPIOB->ODR &=~(1U<<5);
      GPIOB->ODR &=~(1U<<4);
      GPIOB->ODR |= (1U<<10);
      break;

  case 10:
   //speaker = 1200;
  TIM2->ARR = 1200 - 1;
      GPIOB->ODR |= (1U<<3);
      GPIOB->ODR &=~(1U<<5);
      GPIOB->ODR |= (1U<<4);
      GPIOB->ODR &=~(1U<<10);
      break;     

  default:
      GPIOB->ODR &=~(1U<<3);
      GPIOB->ODR &=~(1U<<5);
      GPIOB->ODR &=~(1U<<4);
      GPIOB->ODR &=~(1U<<10);
      GPIOA->ODR &=~ (1U<<5);
      break;
    }
        HAL_Delay(500);
  counter--;

  }
  }
}



ParserReturnVal_t CmdCount(int mode)
{

  uint32_t val;

  if(mode != CMD_INTERACTIVE) return CmdReturnOk;

  fetch_uint32_arg(&val);

    if(val >= 1 && val <= 10) {

      counter = val;

    return CmdReturnBadParameter1;
  }
  else{
    printf("Please enter value between 1 to 10.\n");
  }

    RCC->APB1ENR |= (1U<<0);
  return CmdReturnOk;
}

ADD_CMD("count",CmdCount,"  Enter the count value between 1 to 100")