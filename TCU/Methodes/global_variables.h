/**
 *-------------------------------------------------
 * file global_variables.h
 *
 * By Aksel Larsen Rasmussen
 * -------------------------
 * Contains declarations of members.
 *-------------------------------------------------
 */

// Data between USART and the Vector calculations
int32_t usartInterfaceDataArray_[11]=
{
		{125},{125},{125},{125}
};

// Time delay
uint32_t startupDelay_ = 100; // startup delay in ms


// Timer variables for pwm
uint16_t pwmTimerPeriode_; //Hz
uint16_t pwmPrescalerValue_;

uint16_t pwmWidth1_=1500;
uint16_t pwmWidth2_=1500;
uint16_t pwmWidth3_=1500;
uint16_t pwmWidth4_=1500;
uint16_t pwmWidth5_=1500;
uint16_t pwmWidth6_=1500;
uint16_t pwmWidth7_=1500;

//--------------------------------------------------

// Til Test av joystick mot PWM signal (fjern i siste versjon før utgivelse)
//unsigned char old_X;
