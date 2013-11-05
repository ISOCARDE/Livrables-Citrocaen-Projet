/**
* @file timerFunctions.h
* @brief gestion du ou des timers du PIC32
* @author Alain WERCK
* @date 25/10/2013
*/

#ifndef _TIMER_FUNCTIONS_H
#define _TIMER_FUNCTIONS_H

volatile char alea;
static BOOL demiSecondUpForLed;
volatile short timerDecoBoost;
void initTimer4(void);
BOOL isDemiSecondUp(void);
BOOL is100MSecondUp(void);
void checkTimer(void);

#endif
