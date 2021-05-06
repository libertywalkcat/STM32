/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"


int main(void)
{
	MainSystemClock();
	PWMs();
	while(1){}

}
void MainSystemClock(void){
RCC_DeInit();
RCC->CR |= RCC_CR_HSEON;
FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable);
FLASH_SetLatency(FLASH_Latency_2);
RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
RCC_PLLCmd(ENABLE);
RCC_HCLKConfig(RCC_SYSCLK_Div1);
RCC_PCLK2Config(RCC_HCLK_Div1);
RCC_PCLK1Config(RCC_HCLK_Div2);}

void PWMs(void){
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	GPIOA->CRH &= ~GPIO_CRH_CNF10;
	GPIOA->CRH &= ~GPIO_CRH_MODE10;
	GPIOA->CRH |= GPIO_CRH_MODE10_1;
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	TIM1->PSC = 7199;
	TIM1->ARR = 3700;
	TIM1->CCR3 =2500;
	TIM1->BDTR |= TIM_BDTR_MOE;
	TIM1->CCMR2 = TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
	TIM1->CCER |=TIM_CCER_CC3E;
	TIM1->CR1 &= ~TIM_CR1_DIR;
	TIM1->CR1 &= ~TIM_CR1_CMS;
	TIM1->CR1 |= TIM_CR1_CEN;
}

