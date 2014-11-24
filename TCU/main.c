/**
 *-------------------------------------------------
 * file main.c
 *
 * By Aksel Larsen Rasmussen
 * -------------------------
 * Contains main method.
 *-------------------------------------------------
 */
#include "stm32f10x.h"

//own files
#include "methode_pointer.h"
#include "global_variables.h"

// main function for this program.
int main(void) {
	// delay for other systems to start
	//timeDelay(startupDelay_);

	// prepare/initialize
	initialization();

	// loop infinite..
	while(1)
	{
	}
}

//time Delay 1ms per nTime
void timeDelay(volatile uint32_t nTime) {
	uint32_t timingDelay = nTime;
	while(timingDelay != 0);
}
