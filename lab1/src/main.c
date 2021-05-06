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

	MainSystemClock();
	pin13();
	while(1){
		GPIOC->ODR ^= GPIO_Pin_13; // Invert C13

		/* delay */

		for(uint32_t i=0;i<0x100000;i++);

		/* Toggle LED which connected to PC13*/

		GPIOC->ODR ^= GPIO_Pin_13;

		/* delay */

		for(uint32_t i=0;i<0x100000;i++);
	}
}
void MainSystemClock(void)

	{

	RCC_DeInit(); // сброс настроек тактового генератора

	RCC->CR |= RCC_CR_HSEON;

	FLASH_PrefetchBufferCmd( FLASH_PrefetchBuffer_Enable);

	FLASH_SetLatency(FLASH_Latency_2);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); // На системную шину подаем тактирование с множителя PLLMUL

	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);// множитель PLL 16 , мультиплексор на HSE 8 МГц / 2 * 16 = 64 МГц на SYSCLK

	// Включаем PLL

	RCC_PLLCmd(ENABLE);

	/* HCLK = SYSCLK */ /* Смотри на схеме AHB Prescaler.*/

	RCC_HCLKConfig(RCC_SYSCLK_Div1);//настраиваем частоту AHB
	// PCLK2 = HCLK
	RCC_PCLK2Config(RCC_HCLK_Div1);//настраиваем частоту APB2 72МГц
	// PCLK1 = HCLK/2
	RCC_PCLK1Config(RCC_HCLK_Div2); // настраиваем частоту APB1 36МГц


	//RCC_ADCCLKConfig(RCC_PCLK2_Div8); //Предделитель ADC

	//В данном случае не задействован

}
void pin13(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Initialize LED which connected to PC13 */

	// Enable PORTC Clock

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* Configure the GPIO_LED pin */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Set C13 to Low level ("0")
}
