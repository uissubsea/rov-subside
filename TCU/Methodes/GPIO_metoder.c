/**
 *-------------------------------------------------
 *file GPIO_methodes.c
 *
 * By Aksel Larsen Rasmussen
 * -------------------------
 * Contains method for GPIO initialization
 *
 * Based on "GPIO_Bink.c", by CooCox 
 *-------------------------------------------------
 */

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//own files
#include "methode_pointer.h"

void gpioInit(void)
{
	// PA0-3 and PC6-8 is initialized in GPIO_timer_config()
	// PA9 and 10 is initalized in usart1Config()

	GPIO_InitTypeDef   gpioInitStruct;

	//Clock for GPIO C
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);


	//Configures PC8 and 9 wich are connected to the LED's
	gpioInitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	gpioInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &gpioInitStruct);
}
