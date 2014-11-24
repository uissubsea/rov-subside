/**
 * @file		servo_Control.h
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



#ifndef _SERVO_CONTROL_
#define _SERVO_CONTROL_


void servoControlInit(void);
void servoGpioInit(void);
void servoTimerInit(void);

int increaseServoPos(int inServo);
int decreaseServoPos(int inServo);
void setServoPos(int inServo, int inPos);
int getServoPos(int inServo);


#endif
