/**
 * @file		main.c
 * @author		Sletten
 * @version		v0.0.1
 * @date		21.01.2014
 * @brief		Main file for Manipulator Control Unit
 *
 *
 *
 *
 * @history
 *				21.01.2014	-	added first psudocode for full software
 *
 */

#include "stm32f10x_usart.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"

#include "servo_Control.h"


void gpioInit(void);
void usartInit(void);

char getUsartData(char get);

void pwmInit(void);

int manPos = 3000;


void systickInit(void);



int main(void)
{
	//init system

	//init timer

	//init watchdog

	/* Initialize Leds mounted on STM32 board */
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Initialize LED which connected to PC6,9, Enable the Clock*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);



	gpioInit();

	usartInit();

	pwmInit();

	systickInit();


	/*
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_TimeBaseInitTypeDef timTbItd;

	// set prescaler to count every millisecond
	timTbItd.TIM_Prescaler = (uint16_t) (SystemCoreClock / 24) - 1;
	timTbItd.TIM_Period = 65535;
	timTbItd.TIM_ClockDivision = TIM_CKD_DIV1;
	timTbItd.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM1, &timTbItd);
	*/

	/*
	TIM_OCInitTypeDef timOcItd;

	timOcItd.TIM_OCMode = TIM_OCMode_Timing;
	timOcItd.TIM_OutputState = TIM_OutputState_Enable;

	TIM_OC1Init(TIM15, &timOcItd);
	*/

	//TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	//TIM_ARRPreloadConfig(TIM1, ENABLE);


	/*
	TIM_Cmd(TIM1, ENABLE);
	TIM1->CR1 |= TIM_CR1_CEN;
	 */






	//Copy from GPIO_Blink example, while testing usart data interupt.


	int i;
	uint16_t tempPwm = 0;
	uint16_t tempTim = TIM1->CNT;
	GPIOC->ODR ^= GPIO_Pin_8;




    while (1)
    {



    	if (0 == TIM1->CNT)
    	{
    		tempTim = TIM1->CNT;
    		GPIOC->ODR ^= GPIO_Pin_8;
    	}


    	//TIM2->CCR1 = getUsartData();

    	//USART_SendData(USART1, 255);

        /* Toggle LEDs which connected to PC6*/
        //GPIOC->ODR ^= GPIO_Pin_8;


        /* delay */
        for(i=0;i<0x10000;i++);

        /* Toggle LEDs which connected to PC9*/

        GPIOC->ODR ^= GPIO_Pin_9;

        /* delay */
        //for(i=0;i<0x10000;i++);
    }
}


/*
 * Interrupt called by the systick,
 * runs communication and CCU tasks.
 */
void SysTick_Handler(void)
{
	//TIM3->CCR1 = getUsartData(1);

	// move manip up/down
	int tempData = getUsartData(1);
	if(tempData > 125)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
		TIM3->CCR1 = (tempData-125) * 8;
	}
	else if(tempData < 125)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
		TIM3->CCR1 = (125-tempData) * 8;
	}
	else
		TIM3->CCR1 = 0;



	// rotate manip gripper
	tempData = getUsartData(0);

	if(tempData > 125)
	{
		manPos += (tempData-125);
	}
	else if(tempData < 125)
	{
		manPos -= (125-tempData);
	}

	if(manPos > 5600)
		manPos = 5600;
	if(manPos < 1800)
		manPos = 1800;

	TIM2->CCR1 = manPos;


	tempData = getUsartData(2);
	if(tempData > 125)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		TIM3->CCR2 = (tempData-125) * 8;
	}
	else if(tempData < 125)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
		TIM3->CCR2 = (125-tempData) * 8;
	}
	else
		TIM3->CCR2 = 0;


	// move toolbox


	tempData = getUsartData(5);
	if(tempData == 7)
	{
		GPIO_WriteBit(GPIOC, GPIO_Pin_4, Bit_SET);
		TIM3->CCR3 = 125 * 8;
	}
	else if(tempData == 9)
	{
		GPIO_WriteBit(GPIOC, GPIO_Pin_4, Bit_RESET);
		TIM3->CCR3 = 125 * 8;
	}
	else
		TIM3->CCR3= 0;


}

/*
 * Initializes the systick timer for interrupt every 20ms
 */
void systickInit(void)
{
	NVIC_InitTypeDef initSystick;

	initSystick.NVIC_IRQChannel = SysTick_IRQn;
	initSystick.NVIC_IRQChannelPreemptionPriority = 0;
	initSystick.NVIC_IRQChannelSubPriority = 0;
	initSystick.NVIC_IRQChannel = ENABLE;

	NVIC_Init(&initSystick);

	// set up SysTick to call interrupt 50 times each second
	SysTick_Config(SystemCoreClock/20);
}
