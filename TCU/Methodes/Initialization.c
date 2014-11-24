/**
 *-------------------------------------------------
 * file initialization.c
 *
 * By Aksel Larsen Rasmussen
 * -------------------------
 * Contains initialization method.
 *-------------------------------------------------
 */

#include "stm32f10x.h"
//own files
#include "methode_pointer.h"
#include "extern_global_variables.h"

//-------------------------------------------------
// Calls initialization of sub systems
void initialization(void)
{
	usartInit();
	timersInit();
	gpioInit();
}
