/**
 * @file		tim_conf.c
 * @author		Sletten
 * @version		v0.0.1
 * @date		03.02.2014
 * @brief
 *
 *
 *
 *
 * @history
 *
 */

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"


void pwmInit(void);
void pwmGpioInit(void);




void pwmInit(void)
{
	pwmGpioInit();


	/*
	TIM_TimeBaseInitTypeDef timTbItd;
	

	timTbItd.TIM_Period = 48000;
	timTbItd.TIM_Prescaler = (uint16_t) (SystemCoreClock / 2400000) - 1;
	timTbItd.TIM_ClockDivision = 0;
	timTbItd.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &timTbItd);
	TIM_TimeBaseInit(TIM3, &timTbItd);

	TIM_OCInitTypeDef timOcItd;

	timOcItd.TIM_OCMode = TIM_OCMode_PWM1;
	timOcItd.TIM_OutputState = TIM_OutputState_Enable;
	timOcItd.TIM_Pulse = 0;
	timOcItd.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM3, &timOcItd);

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM3, ENABLE);

	TIM_Cmd(TIM3, ENABLE);
	*/

	{
		TIM_TimeBaseInitTypeDef timTbItd;

		timTbItd.TIM_Period = 1000;
		timTbItd.TIM_Prescaler = (uint16_t) (SystemCoreClock / 24000000) - 1;
		timTbItd.TIM_ClockDivision = 0;
		timTbItd.TIM_CounterMode = TIM_CounterMode_Up;

		TIM_TimeBaseInit(TIM3, &timTbItd);

		TIM_OCInitTypeDef timOcItd;

		timOcItd.TIM_OCMode = TIM_OCMode_PWM1;
		timOcItd.TIM_OutputState = TIM_OutputState_Enable;
		timOcItd.TIM_Pulse = 0;
		timOcItd.TIM_OCPolarity = TIM_OCPolarity_High;


		TIM_OC1Init(TIM3, &timOcItd);
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

		TIM_OC2Init(TIM3, &timOcItd);
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

		TIM_OC3Init(TIM3, &timOcItd);
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

		TIM_OC4Init(TIM3, &timOcItd);
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

		TIM_ARRPreloadConfig(TIM3, ENABLE);

		TIM_Cmd(TIM3, ENABLE);
	}


	{
		TIM_TimeBaseInitTypeDef timTbItd;

		timTbItd.TIM_Period = 48000;
		timTbItd.TIM_Prescaler = (uint16_t) (SystemCoreClock / 2400000) - 1;
		timTbItd.TIM_ClockDivision = 0;
		timTbItd.TIM_CounterMode = TIM_CounterMode_Up;

		TIM_TimeBaseInit(TIM2, &timTbItd);

		TIM_OCInitTypeDef timOcItd;

		timOcItd.TIM_OCMode = TIM_OCMode_PWM1;
		timOcItd.TIM_OutputState = TIM_OutputState_Enable;
		timOcItd.TIM_Pulse = 2500;
		timOcItd.TIM_OCPolarity = TIM_OCPolarity_High;

		TIM_OC1Init(TIM2, &timOcItd);
		TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

		TIM_OC2Init(TIM2, &timOcItd);
		TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

		TIM_ARRPreloadConfig(TIM2, ENABLE);

		TIM_Cmd(TIM2, ENABLE);
	}
}


void pwmGpioInit(void)
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
						   RCC_APB2Periph_GPIOB |
	                       RCC_APB2Periph_AFIO, ENABLE);

	// sette opp gpio pinnene som skal bli brukt til owm utganger.
	/*
	 * Tim2 ch 1 og 2, på pinne PA0 og PA1, PA2 og PA 3 blir brukt av USART modul 2
	 *
	 * Tim3 ch 1-4
	 *
	 */

	

	GPIO_InitTypeDef itd;


	itd.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7;
	itd.GPIO_Mode = GPIO_Mode_AF_PP;
	itd.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &itd);

	itd.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &itd);

}
