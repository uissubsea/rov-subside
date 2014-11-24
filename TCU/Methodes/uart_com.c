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

//added in TCU, by Aksel and Svein Morten
#include "methode_pointer.h"
#include "extern_global_variables.h"

unsigned char startData_ = 255;
unsigned char stopData_ = 251;
unsigned char mcuData_[18]; //6 rec, 6 send

char rec_ = 0; // start recieving?
char done_ = 0; // done recieving?
char i_ = 0;


void usartInit(void);
void usart1Config(void);
void usartInteruptConfig(void);
char getUsartData(char get);


void USART1_IRQHandler(void)
{

	//if ((USART1->SR & USART_FLAG_TXE) /*!= (u16)RESET*/)
	//{
	//	GPIOC->ODR ^= GPIO_Pin_9;
	//}

	//ta i mot datagb
	if ((USART1->SR & USART_FLAG_RXNE) != (u16)RESET)
	{
		unsigned inData = USART_ReceiveData(USART1);
		if(inData == startData_)
		{
			rec_ = 1;
			i_ = 0;
		}
		else if(inData == stopData_ || i_ >= 11) //mcu: 6 tcu: 11
		{
			done_ = 1;
		}
		else if(rec_)
		{
			mcuData_[i_++] = inData;
		}

	}


	//send data
	if(done_)
	{
		//set rs write enable
		GPIO_WriteBit(GPIOA, GPIO_Pin_11, Bit_SET);
		//GPIOA->ODR |= GPIO_Pin_11;


		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{
		}

		USART_SendData(USART1, startData_);

		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{
		}
		i_ = 0;
		while(i_ <= 6) //mcu: 6 tcu 7
		{
			USART_SendData(USART1, mcuData_[i_]);

			while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			{
			}

			i_++;
		}

		USART_SendData(USART1, stopData_);

		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{
		}

		//reset rs write enable
		GPIO_WriteBit(GPIOA, GPIO_Pin_11, Bit_RESET);
		//GPIOA->ODR ^= GPIO_Pin_11;

		rec_ = 0; // start recieving?
		done_ = 0; // done recieving?
		i_ = 0;


		//added in TCU, by Aksel and Svein Morten.
		changeThrusterSpeed();
	}
}

char getUsartData(char get)
{
	if(get > 11)
		return 0;

	return mcuData_[get];
}



void usartInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);


	usart1Config();
	usartInteruptConfig();

}


void usart1Config(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


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

	USART_InitTypeDef usartStruct;


	/*
	 * copy from usart_rxtx example
	 *
	 * USART1 configured as follow:
	        - BaudRate = 115200 baud
	        - Word Length = 8 Bits
	        - One Stop Bit
	        - No parity
	        - Hardware flow control disabled (RTS and CTS signals)
	        - Receive and transmit enabled
	        - USART Clock disabled
	        - USART CPOL: Clock is active low
	        - USART CPHA: Data is captured on the middle
	        - USART LastBit: The clock pulse of the last data bit is not output to
	                         the SCLK pin
	 */

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
	// TODO: lese seg opp, og forstå det som skjer under

	// kopi fra usart rxtx eksempel

	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	//USART_ITConfig(USART1, USART_IT_TC, DISABLE);

}

