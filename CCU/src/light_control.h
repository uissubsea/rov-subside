/**
 * @file		light_control.h
 * @author		Sletten
 * @version		v0.0.1
 * @date		11.03.2014
 * @brief
 *
 *
 *
 *
 * @history
 *
 */






#ifndef _LIGHT_CONTROL_H_
#define _LIGHT_CONTROL_H_


void lightControlInit(void);
void lightGpioInit(void);
void lightTimerInit(void);

int increaseLightDim(int inLight);
int decreaseLightDim(int inLight);
void setLightDim(int inLight, int inDim);
int getLightDim(int inLight);


#endif
