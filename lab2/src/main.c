/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

int main(void)
{
	pininit();
	MainSystemClock();
	timerEN();
	while(1){

	}
}
void MainSystemClock(void)

	{

	RCC_DeInit(); 

	RCC->CR |= RCC_CR_HSEON;

	FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable);

	FLASH_SetLatency(FLASH_Latency_2);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

	RCC_PLLCmd(ENABLE);

	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2); 


}
void pininit(void){
	RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC -> CRH &= ~GPIO_CRH_CNF13;
	GPIOC -> CRH |= GPIO_CRH_MODE13;
}

void timerEN(void){
	RCC->APB1ENR |= RCC_APB2ENR_TIM1EN;
	TIM2->PSC = 7199; 
	TIM2->ARR = 5499; 
	TIM2->DIER |= TIM_DIER_UIE; 
	TIM2->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_UP_IRQn); 
}
void TIM1_UP_IRQHANDLER(void){
	TIM2->SR &= ~TIM_SR_UIF; 
	GPIOC->ODR ^= GPIO_ODR_ODR13;
}
