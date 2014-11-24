/**
 * @file		light_control.c
 * @author		Sletten
 * @version		v0.0.1
 * @date		11.03.2014
 * @brief
 *
 *
 *
 *
 * @history
 *
 */


#include "light_control.h"

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"



#define DEFAULT_PERIOD 1000
#define DEFAULT_PRESCALER (SystemCoreClock / 24000000) - 1

#define LIGHT_COUNT 6

#define INC_AMOUNT 50 // amount to increase dutycycle
#define DEC_AMOUNT 50 // amount to decrease dutycycle


int lightDim[LIGHT_COUNT];


void lightControlInit(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	lightGpioInit();
	lightTimerInit();

}
void lightGpioInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
						   RCC_APB2Periph_GPIOB |
						   RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef itd;


	// Gpio pinner for timer 2 ch1 og ch2, og timer 3 ch 1 og 2
	itd.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_6 | GPIO_Pin_7;
	itd.GPIO_Mode = GPIO_Mode_AF_PP;
	itd.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &itd);
	// Gpio pinner for timer 3 ch 3 og ch 4
	itd.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &itd);


	// timer 2 ch3 og 4 pinnene pa2 og pa3 er i bruk av usart2.
}
void lightTimerInit(void)
{
	TIM_TimeBaseInitTypeDef timTbItd;

	timTbItd.TIM_Period = DEFAULT_PERIOD;
	timTbItd.TIM_Prescaler = (uint16_t) DEFAULT_PRESCALER;
	timTbItd.TIM_ClockDivision = 0;
	timTbItd.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM2, &timTbItd);
	TIM_TimeBaseInit(TIM3, &timTbItd);

	TIM_OCInitTypeDef timOcItd;

	timOcItd.TIM_OCMode = TIM_OCMode_PWM1;
	timOcItd.TIM_OutputState = TIM_OutputState_Enable;
	timOcItd.TIM_Pulse = 0;
	timOcItd.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM2, &timOcItd);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_OC2Init(TIM2, &timOcItd);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_OC1Init(TIM3, &timOcItd);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_OC2Init(TIM3, &timOcItd);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_OC3Init(TIM3, &timOcItd);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_OC4Init(TIM3, &timOcItd);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_ARRPreloadConfig(TIM3, ENABLE);

	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

int increaseLightDim(int inLight)
{
	setLightDim(inLight, getLightDim(inLight) + INC_AMOUNT);

	return getLightDim(inLight);
}
int decreaseLightDim(int inLight)
{
	setLightDim(inLight, getLightDim(inLight) - DEC_AMOUNT);

	return getLightDim(inLight);
}
void setLightDim(int inLight, int inDim)
{
	if(inDim <= DEFAULT_PERIOD && inDim >= 0)
	{
		if(inLight > 0 && inLight <= LIGHT_COUNT)
		{
			lightDim[inLight] = inDim;

			switch(inLight)
			{
			case 1:
				TIM2->CCR1 = inDim;
				break;
			case 2:
				TIM2->CCR2 = inDim;
				break;
			case 3:
				TIM3->CCR1 = inDim;
				break;
			case 4:
				TIM3->CCR2 = inDim;
				break;
			case 5:
				TIM3->CCR3 = inDim;
				break;
			case 6:
				TIM3->CCR4 = inDim;
				break;
			}
		}
	}

}
int getLightDim(int inLight)
{
	return lightDim[inLight];
}
