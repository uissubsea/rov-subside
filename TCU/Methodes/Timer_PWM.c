/**
 *-------------------------------------------------
 * file Timer_PWM.c
 *
 * By Aksel Larsen Rasmussen
 * -------------------------
 * Contains methods to initialize
 * and set timer values for pulse-with modulation
 *
 * Based on:
 * - posts by Clive1 on ST forums,
 * 	 Link:
 * 	 https://my.st.com/public/STe2ecommunities/mcu/Lists/cortex_mx_stm32/Flat.aspx?RootFolder=https://my.st.com/public/STe2ecommunities/mcu/Lists/cortex_mx_stm32/PWM%20Output%20on%20STM32F2XX&FolderCTID=0x01200200770978C69A1141439FE559EB459D7580009C4E14902C3CDE46A77F0FFD06506F5B&currentviews=1974
 *
 *  - "TIM3, channel 3 one pulse mode.c" example by JeoFin
 *
 *  - "TIM_PWMoutput.c"-example  by CooCOx
 *-------------------------------------------------
 */


#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"

//our own
#include "methode_pointer.h"
#include "extern_global_variables.h"

TIM_OCInitTypeDef	timOCInitStructure_; 		//
TIM_TimeBaseInitTypeDef  timTimeBaseStructure_;	//

//-------------------------------------------------
// Set up timers
void timersInit (void)
{
	timerRCCConfig(); //(Must be before timerGPIOConfig!)
	timerGPIOConfig();

	//timer parameter variables
	pwmTimerPeriode_ = 20000-1;//6666-1;
	pwmPrescalerValue_ = 24-1; //72-1;

	/* Time base configuration */
	timTimeBaseStructure_.TIM_Period = pwmTimerPeriode_;
	timTimeBaseStructure_.TIM_Prescaler = pwmPrescalerValue_;
	timTimeBaseStructure_.TIM_ClockDivision = TIM_CKD_DIV1;
	timTimeBaseStructure_.TIM_CounterMode = TIM_CounterMode_Up;

	//initialization of timer 2 and timer 3
	TIM_TimeBaseInit(TIM2, &timTimeBaseStructure_);
	TIM_TimeBaseInit(TIM3, &timTimeBaseStructure_);

	//TIM2 - channel 1 (PA0)----------------------------------------------------<--
	timOCInitStructure_.TIM_OCMode = TIM_OCMode_PWM1;
	timOCInitStructure_.TIM_OutputState = TIM_OutputState_Enable;
	timOCInitStructure_.TIM_Pulse = pwmWidth1_;//endre her
	timOCInitStructure_.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM2, &timOCInitStructure_);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

	//TIM2 - channel 2 (PA1)----------------------------------------------------<--
	timOCInitStructure_.TIM_OutputState = TIM_OutputState_Enable;
	timOCInitStructure_.TIM_Pulse = pwmWidth2_;//endre her

	TIM_OC2Init(TIM2, &timOCInitStructure_);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	//TIM2 - channel 3 (PA2)----------------------------------------------------<--
	timOCInitStructure_.TIM_OutputState = TIM_OutputState_Enable;
	timOCInitStructure_.TIM_Pulse = pwmWidth3_;//endre her

	TIM_OC3Init(TIM2, &timOCInitStructure_);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

	//TIM2 - channel 4 (PA3)----------------------------------------------------<--
	timOCInitStructure_.TIM_OutputState = TIM_OutputState_Enable;
	timOCInitStructure_.TIM_Pulse = pwmWidth4_;//endre her

	TIM_OC4Init(TIM2, &timOCInitStructure_);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	//-----------------------------------------------------------------------------

	//TIM3 - channel 1 (PA6)----------------------------------------------------<--
	timOCInitStructure_.TIM_OCMode = TIM_OCMode_PWM1;
	timOCInitStructure_.TIM_OutputState = TIM_OutputState_Enable;
	timOCInitStructure_.TIM_Pulse = pwmWidth5_;//endre her
	timOCInitStructure_.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM3, &timOCInitStructure_);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	//TIM3 - channel 2 (PA7)----------------------------------------------------<--
	timOCInitStructure_.TIM_OutputState = TIM_OutputState_Enable;
	timOCInitStructure_.TIM_Pulse = pwmWidth6_;//endre her

	TIM_OC2Init(TIM3, &timOCInitStructure_);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

	//TIM3 - channel 3 (PB0)----------------------------------------------------<--
	timOCInitStructure_.TIM_OutputState = TIM_OutputState_Enable;
	timOCInitStructure_.TIM_Pulse = pwmWidth7_;//endre her

	TIM_OC3Init(TIM3, &timOCInitStructure_);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	//-----------------------------------------------------------------------------

	//TIM2 enable counter
	TIM_Cmd(TIM2, ENABLE);
	//TIM3 enable counter
	TIM_Cmd(TIM3, ENABLE);
}


//-------------------------------------------------
// config RCC - enable timers
void timerRCCConfig(void)
{
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/*TIM3 clock enabled*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

}

//-------------------------------------------------
// config GPIO output
void timerGPIOConfig(void)
{
	/*GPIO A and GPIO B enabled to timer*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitTypeDef GPIOInitStruct;

	/*Configures PA0, PA1, PA2 and PA3 as PWMoutput's for timer 2
	 * and PA6 and PA7 as PWMoutputs for timer 3*/
	GPIOInitStruct.GPIO_Pin = (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
			|GPIO_Pin_6|GPIO_Pin_7);
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIOInitStruct);

	/*Configures PB0 as PWMoutput's for timer 3*/
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB, &GPIOInitStruct);
}

//-------------------------------------------------
// Set puls-width 1
void setTrusterWidth1(uint16_t width_)
{
	pwmWidth1_=width_;

	//set width of TIM2- channel 1
	TIM2->CCR1 = width_;
}

//-------------------------------------------------
// Set puls-width 2
void setTrusterWidth2 (uint16_t width_)
{
	pwmWidth2_=width_;
	//set width of TIM2- channel 2
	TIM2->CCR2 = width_;
}

//-------------------------------------------------
// Set puls-width 3
void setTrusterWidth3 (uint16_t width_)
{
	pwmWidth3_=width_;
	//set width of TIM2- channel 3
	TIM2->CCR3 = width_;
}

//-------------------------------------------------
// Set puls-width 4
void setTrusterWidth4 (uint16_t width_)
{
	pwmWidth4_=width_;
	//set width of TIM2- channel 4
	TIM2->CCR4 = width_;
}

//-------------------------------------------------
// Set puls-width 5
void setTrusterWidth5 (uint16_t width_)
{
	pwmWidth5_=width_;
	//set width of TIM3- channel 1
	TIM3->CCR1 = width_;
}

//-------------------------------------------------
// Set puls-width 6
void setTrusterWidth6 (uint16_t width_)
{
	pwmWidth6_=width_;
	//set width of TIM3- channel 2
	TIM3->CCR2 = width_;
}

//-------------------------------------------------
// Set puls-width 7
void setTrusterWidth7(uint16_t width_)
{
	pwmWidth7_=width_;
	//set width of TIM3- channel 3
	TIM3->CCR3 = width_;
}

