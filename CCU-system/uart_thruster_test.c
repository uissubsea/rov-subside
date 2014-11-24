/**
 * @file		uart_thruster_test.c
 * @author		Sletten
 * @version		v0.0.1
 * @date		17.02.2014
 * @brief
 *
 *
 *
 *
 * @history
 *
 */


#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
//#include "misc.h"


void sendTS(void);


void usartInit(void);
void usart1Config(void);
void usart2Config(void);



void usartInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);


	usart1Config();
	usart2Config();
}

void usart1Config(void)
{
	USART_InitTypeDef usartStruct;

	usartStruct.USART_BaudRate = 56000;
	usartStruct.USART_WordLength = USART_WordLength_8b;
	usartStruct.USART_StopBits = USART_StopBits_1;
	usartStruct.USART_Parity = USART_Parity_No;
	usartStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


	USART_Init(USART1, &usartStruct);

	// enable usart
	USART_Cmd(USART1, ENABLE);
}

void usart2Config(void)
{
	USART_InitTypeDef usartStruct;


		usartStruct.USART_BaudRate = 9600;
		usartStruct.USART_WordLength = USART_WordLength_8b;
		usartStruct.USART_StopBits = USART_StopBits_1;
		usartStruct.USART_Parity = USART_Parity_No;
		usartStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		usartStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


		USART_Init(USART2, &usartStruct);

		// enable usart
		USART_Cmd(USART2, ENABLE);
}
