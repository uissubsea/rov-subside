/**
 *-------------------------------------------------
 * file interrupt_methodes.c
 *
 * By Aksel Larsen Rasmussen
 * -------------------------
 * Contains main methods called by interrupt handler
 *
 *-------------------------------------------------
 */

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

//own files
#include "methode_pointer.h"
#include "extern_global_variables.h"


//-------------------------------------------------
// Fills the array width the data from the USART
void fillUsartInterfaceDataArray(void)
{
  int i_=0;
  for (i_=0; i_<11; i_++)
  {
	  usartInterfaceDataArray_[i_]=changeRange1(getUsartData(i_));
  }
}

//-------------------------------------------------
//makes an 0 to 250 char value to an 0 to 1000 uint16_t value (need +1000 in the end because we need 1000-2000 in output)
int32_t changeRange1(char xValvue_)
{
  /*
   * the math:
   *y2-y1=a(x2-x1)
   *=>y2=a*(x2-x1)+y1
   *2000-1000=a(250-0)
   *=> a=1000/250=4
   */
  int32_t yVavlue_;
  yVavlue_=(int32_t) xValvue_;
  yVavlue_=(yVavlue_*0.8)-100;
  return yVavlue_;
}

//-------------------------------------------------

// calculate vectors and set puls-width
void changeThrusterSpeed (void)
{
  //Fills the array with values from the USART
  fillUsartInterfaceDataArray();

  //Calculate the width for each timer signal
  vectorCalculations();

  /*set's the width of the timer signals
  (value from 1000-2000 = signal width 10-20ms, at 50hz)
  (thruster 1 to 7)
  */
  setTrusterWidth1(getWidthValue (0));
  setTrusterWidth2(getWidthValue (1));
  setTrusterWidth3(getWidthValue (2));
  setTrusterWidth4(getWidthValue (3));
  setTrusterWidth5(getWidthValue (4));
  setTrusterWidth6(getWidthValue (5));
  setTrusterWidth7(getWidthValue (6));

}
