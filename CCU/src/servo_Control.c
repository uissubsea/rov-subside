/**
 * @file		servo_Control.c
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


#include "servo_Control.h"

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"


#define SERVO_COUNT 4

unsigned int servoPos[SERVO_COUNT];


void servoControlInit(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	servoGpioInit();
	servoTimerInit();
}
void servoGpioInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |
						   RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef itd;


	itd.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	itd.GPIO_Mode = GPIO_Mode_AF_PP;
	itd.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &itd);

}
void servoTimerInit(void)
{
	TIM_TimeBaseInitTypeDef timTbItd;

	timTbItd.TIM_Period = 48000;
	timTbItd.TIM_Prescaler = (uint16_t) (SystemCoreClock / 2400000) - 1;
	timTbItd.TIM_ClockDivision = 0;
	timTbItd.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &timTbItd);

	TIM_OCInitTypeDef timOcItd;

	timOcItd.TIM_OCMode = TIM_OCMode_PWM1;
	timOcItd.TIM_OutputState = TIM_OutputState_Enable;
	timOcItd.TIM_Pulse = 2500;
	timOcItd.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM4, &timOcItd);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_OC2Init(TIM4, &timOcItd);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_OC3Init(TIM4, &timOcItd);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_OC4Init(TIM4, &timOcItd);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);

	TIM_Cmd(TIM4, ENABLE);
}

void setServoPos(int inServo, int inPos)
{
	switch(inServo)
	{
	case 1:
		TIM4->CCR1 = inPos;
		break;
	case 2:
		TIM4->CCR2 = inPos;
		break;
	case 3:
		TIM4->CCR3 = inPos;
		break;
	case 4:
		TIM4->CCR4 = inPos;
		break;
	}
}
int getServoPos(int inServo)
{
	if(inServo > 0 &&inServo <= SERVO_COUNT)
		return servoPos[inServo];
	return 0;
}
