/**
 * @file		uart_com.c
 * @author		Sletten
 * @version		v0.0.1
 * @date		21.01.2014
 * @brief
 *
 *
 *
 *
 * @history
 *				21.01.2014	-	added first psudocode for usart communication
 *
 */


#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "misc.h"


unsigned char startData = 255;
unsigned char stopData = 251;
unsigned char mcuData[20]; //6 rec, 6 send

char rec = 0; // start recieving?
char done = 0; // done recieving?
char i = 0;


void usartInit(void);
void usart1Config(void);
void usartInteruptConfig(void);
char getUsartData(char get);


void USART1_IRQHandler(void)
{
    //ta i mot data
    if ((USART1->SR & USART_FLAG_RXNE) != (u16)RESET)
	{
    	unsigned inData = USART_ReceiveData(USART1);

    	if(inData == startData)
		{
			rec = 1;
			i = 0;
		}
		else if(inData == stopData /*|| i >= 6*/) //mcu: 6 tcu: 11
		{
			done = 1;
		}
		else if(rec)
		{
			mcuData[i++] = inData;
		}
	}

    //send data
    if(done)
    {
    	//set rs write enable
    	GPIO_WriteBit(GPIOA, GPIO_Pin_11, Bit_SET);


    	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    	{
    	}

    	USART_SendData(USART1, startData);

		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{
		}
		i = 0;
		while(i <= 5) //mcu: 6 tcu 7
		{
			USART_SendData(USART1, mcuData[i]);

			while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			{
			}

			i++;
		}

		USART_SendData(USART1, stopData);

		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{
		}

		//reset rs write enable
		GPIO_WriteBit(GPIOA, GPIO_Pin_11, Bit_RESET);

		rec = 0; // start recieving?
	    done = 0; // done recieving?
	    i = 0;
    }
}

char getUsartData(char get)
{
	if(get >= 11)
		return 0;

	return mcuData[get];
}



void usartInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);


	usart1Config();
	usartInteruptConfig();

}


void usart1Config(void)
{
	USART_InitTypeDef usartStruct;

	usartStruct.USART_BaudRate = 128000;
	usartStruct.USART_WordLength = USART_WordLength_8b;
	usartStruct.USART_StopBits = USART_StopBits_1;
	usartStruct.USART_Parity = USART_Parity_No;
	usartStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;


	USART_Init(USART1, &usartStruct);

	// enable usart
	USART_Cmd(USART1, ENABLE);
}

void usartInteruptConfig(void)
{


	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

