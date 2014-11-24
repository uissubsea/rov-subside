/**
 * @file		camera_control.c
 * @author		Sletten
 * @version		v0.0.1
 * @date		30.04.2014
 * @brief
 *
 *
 *
 *
 * @history
 *
 */

#include "camera_control.h"

#include "servo_Control.h"



/*
 * Camera array
 * 0: timer CCR output
 * 1: normal position of camera
 * 2: current position of camera
 */
int camera1[3];
int camera2[3];

#define MAX_DEFLECT	5600	// maximum upwards deflection
#define MIN_DEFLECT	1800	// maximum downwards deflection
#define MOVE		50


void updataROV_Data();

void cameraControlInit()
{
	camera1[0] = 4;
	camera1[1] = 4300;
	camera1[2] = camera1[1];
	setServoPos(camera1[0], camera1[2]);

	camera2[0] = 1;
	camera2[1] = 2500;
	camera2[2] = camera2[1];
	setServoPos(camera2[0], camera2[2]);
}


//move camera
//in mov:
// 1: up
// 2: down
// 3: normal position
void moveCamera(int inCamera, int inMove)
{
	if(inCamera == 1)
	{
		switch(inMove)
		{
		case 1:
			if(camera1[2] <= MAX_DEFLECT - MOVE)
			{
				camera1[2] = camera1[2] + MOVE;
			}
			break;
		case 2:
			if(camera1[2] >= MIN_DEFLECT + MOVE)
			{
				camera1[2] = camera1[2] - MOVE;
			}
			break;
		case 3:
			camera1[2] = camera1[1];
			break;
		}
		setServoPos(camera1[0], camera1[2]);
	}
	else if (inCamera == 2)
	{
		switch(inMove)
		{
		case 1:
			if(camera2[2] <= MAX_DEFLECT - MOVE)
			{
				camera2[2] = camera2[2] + MOVE;
			}
			break;
		case 2:
			if(camera2[2] >= MIN_DEFLECT + MOVE)
			{
				camera2[2] = camera2[2] - MOVE;
			}
			break;
		case 3:
			camera2[2] = camera2[1];
			break;
		}
		setServoPos(camera2[0], camera2[2]);
	}
}
int getCameraTilt(int inCamera)
{
	if(inCamera == 1)
	{
		return (((camera1[2] - MIN_DEFLECT) * 250) / (MAX_DEFLECT - MIN_DEFLECT));
	}
	else if(inCamera == 2)
	{
		return (((camera2[2] - MIN_DEFLECT) * 250) / (MAX_DEFLECT - MIN_DEFLECT));
	}
	return 0;
}
