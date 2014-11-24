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

#define DIR_CLOCKWISE			0
#define DIR_COUNTER_CLOCKWISE	1
#define DIR_CENTER				2
#define MAX_DEFLECTION	2750
#define MIN_DEFLECTION	750
#define CENTER 			1750
#define MOVE			50

void servo_control_init();
void move_servo(int dir);
void set_servo_pos(int pos);
void center_servo();
int get_servo_pos();

#endif
