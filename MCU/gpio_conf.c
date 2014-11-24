/**
 * @file		gpio_conf.c
 * @author		Sletten
 * @version		v0.0.1
 * @date		21.01.2014
 * @brief
 *
 *
 *
 *
 * @history
 *				21.01.2014	-
 */

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
//#include "misc.h"


void gpioInit(void);
void gpioPeriphInit(void);
void gpioUsartInit(void);




void gpioInit(void)
{
	gpioPeriphInit();
	gpioUsartInit();
}

void gpioPeriphInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}
void gpioUsartInit(void)
{
	GPIO_InitTypeDef gpioStruct;

	// initsierer gpioa pin 9 for usart1 TX
	gpioStruct.GPIO_Pin = GPIO_Pin_9;
	gpioStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioStruct);

	// initsierer gpioa pin 10 for usart1 RX
	gpioStruct.GPIO_Pin = GPIO_Pin_10;
	gpioStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpioStruct);


	//Write enable
	gpioStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioStruct.GPIO_Speed = GPIO_Speed_50MHz;
	gpioStruct.GPIO_Pin = GPIO_Pin_11;

	GPIO_Init(GPIOA, &gpioStruct);

}
