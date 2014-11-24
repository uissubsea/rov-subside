/**
 * @file		camera_control.c
 * @author		Stian Sandve
 * @version		v0.0.1
 * @date		08.08.2014
 * @brief
 * @history
 *
 */

#include "camera_control.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

/*
 * Servo array
 * 0: timer CCR output
 * 1: center position of servo
 * 2: current position of servo
 */

int servo = CENTER;

void servo_control_init()
{
	init_servo_gpio();
	init_servo_timer();
}

void init_servo_gpio()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |
							   RCC_APB2Periph_AFIO, ENABLE);

		GPIO_InitTypeDef itd;

		itd.GPIO_Pin = GPIO_Pin_6;
		itd.GPIO_Mode = GPIO_Mode_AF_PP;
		itd.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &itd);
}

void init_servo_timer()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitTypeDef timTbItd;

	timTbItd.TIM_Period = 20000;
	timTbItd.TIM_Prescaler = (uint16_t) 24 - 1;
	timTbItd.TIM_ClockDivision = 0;
	timTbItd.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &timTbItd);

	TIM_OCInitTypeDef timOcItd;

	timOcItd.TIM_OCMode = TIM_OCMode_PWM1;
	timOcItd.TIM_OutputState = TIM_OutputState_Enable;
	timOcItd.TIM_Pulse = 1500;
	timOcItd.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM4, &timOcItd);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);

	TIM_Cmd(TIM4, ENABLE);
}

void move_servo(int dir)
{
	switch(dir)
	{
	case DIR_CLOCKWISE:
		if(servo <= MAX_DEFLECTION - MOVE)
		{
			servo = servo + MOVE;
		}
		break;
	case DIR_COUNTER_CLOCKWISE:
		if(servo >= MIN_DEFLECTION + MOVE)
		{
			servo = servo - MOVE;
		}
		break;
	case DIR_CENTER:
		servo = CENTER;
		break;
	}
	set_servo_pos(servo);
}

void set_servo_pos(int pos)
{
	if(pos <= MAX_DEFLECTION && pos >= MIN_DEFLECTION)
	{
		TIM4->CCR1 = pos;
	}
}

void center_servo()
{
	set_servo_pos(CENTER);
}

int get_servo_pos()
{
	return (((servo - MIN_DEFLECTION) * 250) / (MAX_DEFLECTION - MIN_DEFLECTION));
}
