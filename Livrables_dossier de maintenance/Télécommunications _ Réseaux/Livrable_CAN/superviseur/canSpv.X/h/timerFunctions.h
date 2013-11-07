/**
* @file timerFunctions.h
* @brief gestion du timer 4 sur pic32
* @author Alain WERCK
* @date 25/10/2013
*/

#ifndef _TIMER_FUNCTIONS_H
#define _TIMER_FUNCTIONS_H

volatile char timerRequeteEnCours;
volatile char timerConsigneEnCours;
volatile char renvoi;
volatile char timerInviteEnCours;
volatile short timerAvantNouvelleInvite;

void initTimer4(void);
BOOL isDemiSecondUp(void);
BOOL is100MSecondUp(void);
void checkTimer(void);

#endif
