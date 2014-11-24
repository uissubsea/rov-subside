/**
 *-------------------------------------------------
 * methode_pointer.h
*
 * By Aksel Larsen Rasmussen
 * -------------------------
 * Contains declarations of methodes.
 *-------------------------------------------------
 */

//[1] Main.c ---------------------------------------
int main(void);
void timeDelay(volatile uint32_t nTime);
//--------------------------------------------------

//[2] initalization.c ------------------------------
void initialization (void);
//--------------------------------------------------

//[3] uart_com.c -----------------------------------
void usartInit(void);
void usart1Config(void);
void usartInteruptConfig(void);
char getUsartData(char get);
//--------------------------------------------------

//[4] Timer_PMW.c ----------------------------------
void initialization_Timers (void);
void timerRCCConfig(void);
void timerGPIOConfig(void);
void setTrusterWidth1(uint16_t width);
void setTrusterWidth2(uint16_t width);
void setTrusterWidth3(uint16_t width);
void setTrusterWidth4(uint16_t width);
void setTrusterWidth5(uint16_t width);
void setTrusterWidth6(uint16_t width);
void setTrusterWidth7(uint16_t width);
//--------------------------------------------------

//[5] GPIO_methodes.c ------------------------------
void gpioInit(void);
//--------------------------------------------------

//[6] interrupt_methodes.c--------------------------
void fillUsartInterfaceDataArray(void);
void changeThrusterSpeed (void);
int32_t changeRange1(char x);
uint16_t changeRange2(char x);
//--------------------------------------------------

//[7] Vector calculations.c ------------------------
void vectorCalculations(void);
uint16_t getWidthValue (int thruster_nr);
void horisontalValvuesCalculation (void);
void verticalValvuesCalculation (void);
//--------------------------------------------------
