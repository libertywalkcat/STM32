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
	ADC();
	float max=1.48;
	float min=1.46;
	float rdacpp=0;
	while(1){
		rdacpp=(RDACP()*3.3)/4096;
		if(rdacpp>min&&rdacpp<max)
		{GPIOC -> BSRR |= GPIO_BSRR_BS13;}
		else
		{GPIOC -> BSRR |= GPIO_BSRR_BR13;}
	}
}
void MainSystemClock(void)

	{

	RCC_DeInit();

	RCC->CR |= RCC_CR_HSEON;

	FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable);

	FLASH_SetLatency(FLASH_Latency_2);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 

	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);/
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

void ADC(void){
	RCC-> APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA -> CRL &= ~GPIO_CRL_MODE3;
	GPIOA -> CRL &= ~GPIO_CRL_CNF3;
	RCC ->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC -> CFGR |=RCC_CFGR_ADCPRE_DIV6;
	ADC1 ->SMPR2 |= ADC_SMPR2_SMP0_0;
	ADC1->SQR1 |=ADC_SQR1_L_0;
	ADC1->SQR3 |=ADC_SQR3_SQ1_0|ADC_SQR3_SQ1_1;
	ADC1->CR2 |= ADC_CR2_CAL;
	while (!(ADC1->CR2 & ADC_CR2_CAL)){};

	ADC1->CR2 |= ADC_CR2_EXTSEL;
	ADC1->CR2 |= ADC_CR2_EXTTRIG;
	ADC1->CR2 |= ADC_CR2_ADON; 
}

int RDACP(void){
ADC1->CR2 |= ADC_CR2_SWSTART;
while(!(ADC1->SR & ADC_SR_EOC)){};
return ADC1->DR;
}


