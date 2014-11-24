/**
 * @file		main.c
 * @author		Sletten
 * @version		v0.0.1
 * @date		20.01.2014
 * @brief		Main file for Central Control Unit
 *
 *
 *
 *
 * @history
 *				20.01.2014	-	added first psudocode for full software
 *
 */


/*
 * Main file for the CCU system.
 *
 *
 */

#include "stm32f10x.h"
#include "misc.h"

#include "com.h"
#include "light_control.h"
#include "servo_Control.h"
#include "camera_control.h"


void systickInit(void);
void runCcuSystems(void);

int main(void)
{
	comInit();
	lightControlInit();
	servoControlInit();
	cameraControlInit();
	systickInit();

    while(1)
    {
    }
}


/*
 * Interrupt called by the systick,
 * runs communication and CCU tasks.
 */
void SysTick_Handler(void)
{
	communicate();

	runCcuSystems();
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

/*
 * performs routine tasks for the CCU
 */
void runCcuSystems(void)
{
	/*
	 * Control camera servos
	 *
	 */

	// check pilot hat-switch for input
	switch(getData(5))
	{
	case 8: // button up
		moveCamera(1, 1); // move camera 1 up
		break;
	case 4: // button down
		moveCamera(1, 2); // move camera 1 down
		break;
	case 1: // button right
	case 2: // button left
		moveCamera(1, 3); // set normal camera 1 position
		break;
	}

	// check co-pilot hat-switch for input
	switch(getData(5)) //11
	{
	case 8: // button up
		moveCamera(2, 1); // move camera 1 up
		break;
	case 4: // button down
		moveCamera(2, 2); // move camera 1 down
		break;
	case 1: // button right
	case 2: // button left
		moveCamera(2, 3); // set normal camera 1 position
		break;
	}


	/*
	 * Dimming lights
	 *
	 */

	// check pilot button for input
	switch(getData(4))
	{
	case 6:
		increaseLightDim(3);
		break;
	case 4:
		decreaseLightDim(3);
		break;
	}
}







