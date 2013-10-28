/**
* @file timerFunctions.h
* @brief gestion du ou des timers du PIC32
* @author Alain WERCK
* @date 25/10/2013
*/

#ifndef _TIMER_FUNCTIONS_H
#define _TIMER_FUNCTIONS_H

#include "GenericTypeDefs.h"
#include <p32xxxx.h>

#define TIMER1_PERIOD 	0x1F40	/* For a 0.1 millisecond interval	*/
#define ONE_SECOND_MSEC	0x2710	/* For a 1 second timeout in terms 	*/
								/* of 0.1 milliseconds	*/	
BOOL isOneSecondUp(void);
void initTimer1(void);

#endif
