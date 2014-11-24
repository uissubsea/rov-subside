/**
 * @file		camera_control.h
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


#ifndef _CAMERA_CONTROL_H_
#define _CAMERA_CONTROL_H_

void cameraControlInit();

void moveCamera(int inCamera, int inMove);
int getCameraTilt(int inCamera);

#endif
