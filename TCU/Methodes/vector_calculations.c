/**
 *-------------------------------------------------
 * file vector_calculations.c
 *
 * By Aksel Larsen Rasmussen
 * -------------------------
 * Contains methods for h/v vector and puls-with scaling
 *-------------------------------------------------
 */

#include "stm32f10x.h"
#include "math.h"

//our own
#include "methode_pointer.h"
#include "extern_global_variables.h"



// declaration of arrays -------------------------

// This array is made for giving the horizontal thrusters the right directions.
// The parameters follows the joystick's direction were the X-axis is "east/west",
// Y-axis is "north/south" and "C/CCW" is the clockwise/counterclockwise rotation direction
int32_t horizontalDirectionArray_[4][3] = // Array for horizontal thruster directions
{

		//E/W, 	N/S,  CW/CCW
		{ 1,	 -1,	 1},  		// Horizontal thruster 1
		{-1,	 -1,	-1},	  	// Horizontal thruster 2
		{ 1,	  1, 	-1},  		// Horizontal thruster 3
		{-1,	  1,  	 1}  		// Horizontal thruster 4
};


// This array is made for giving the vertical thrusters the right directions.
// The parameters follows the ROVs position in the vertical direction.
// "roll" is for left/right tilt and "pitch" is for front/back tilt
// This array will be used in later versions
int32_t verticalDirectionArray_[3][2]=
{
		//roll, pitch
		{ 1,	1},	// vertical thruster 1
		{-1,	1},	// vertical thruster 2
		{ 0,   -1}	// vertical thruster 3
};

int32_t horisontalThrusterDataArray_[3][4]; //Constructing array for horizontal thrusters
int32_t verticalThrusterDataArray_[3][3]; //Constructing array for vertical thrusters
uint16_t widthDataArray_[7]; // pulse-width result array


//-------------------------------------------------
// Calculates horizontal and vertical results
// and scales result for use in pulse-width modulation.
void vectorCalculations(void)
{
	// vector calc
	horisontalValvuesCalculation();
	verticalValvuesCalculation();
	// scale to pulse-width
	int i_;
	for(i_=0;i_<7;i_++)
	{
		if(i_<4)
		{
			widthDataArray_[i_]=(uint16_t)(((horisontalThrusterDataArray_[2][i_])*5)+1500);
		}
		else {
			widthDataArray_[i_]=(uint16_t) (((verticalThrusterDataArray_[2][i_-4])*5)+1500);

		}
	}
}

//-------------------------------------------------
// Get the value of widthDataArray[thruster_nr]
uint16_t getWidthValue (int thrusterNum_)
{
	return (uint16_t) (widthDataArray_[thrusterNum_]);
}

//-------------------------------------------------
// Calculate horizontal vectors using direction array
// and scaled values from USART
void horisontalValvuesCalculation (void)
{
	int i_;
	int j_;
	int32_t highest_=0;

	for (i_=0;i_<4; i_++)
	{
		//X=north to south
		int32_t X= (int32_t) (horizontalDirectionArray_[i_][0] * usartInterfaceDataArray_[0]);
		//Y=east to west
		int32_t Y= (int32_t) (horizontalDirectionArray_[i_][1] * usartInterfaceDataArray_[1]);
		//R=clockwise to counter clockwise
		int32_t R= (int32_t) (horizontalDirectionArray_[i_][2] * usartInterfaceDataArray_[2]);
		//Sum of directions
		horisontalThrusterDataArray_[0][i_]=(X+Y+R);

		horisontalThrusterDataArray_[1][i_]=abs(horisontalThrusterDataArray_[0][i_]);

		if (horisontalThrusterDataArray_[1][i_]>highest_)
		{
			highest_=horisontalThrusterDataArray_[1][i_];
		}
	}
	if (highest_>100)
	{
		highest_=(highest_/100);
	}
	else
	{
		highest_=1;
	}

	for (j_=0;j_<4;j_++){
		horisontalThrusterDataArray_[2][j_]=horisontalThrusterDataArray_[0][j_]/highest_;
	}
}

//-------------------------------------------------
// Calculate vertical vectors using balanced values from USART
void verticalValvuesCalculation (void)
{
	//For Joystick testing
	verticalThrusterDataArray_[2][0]=-1 * usartInterfaceDataArray_[3]/2;
	verticalThrusterDataArray_[2][1]=-1 * usartInterfaceDataArray_[3]/2;
	verticalThrusterDataArray_[2][2]=-1 * usartInterfaceDataArray_[3];
}
