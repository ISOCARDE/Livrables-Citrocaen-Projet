/**
* @file timerFunctions.c
* @brief gestion du ou des timers du PIC32
* @author Alain WERCK
* @date 25/10/2013
*/

#include ".\h\TimerFunctions.h"

static BOOL oneSecondUp;
static UINT32 msecCounter;

/**
* @fn void initTimer1(void)
* @brief initialisation du timer 1
*/
void initTimer1(void){
	
	T1CON = 0x0;            // Basic Timer Operation
	PR1 = TIMER1_PERIOD;	// Timer period in TimerFunctions.h

	IFS0CLR = 0x10;		// Clear interrupt flag and enable
	IEC0SET = 0x10;		// timer 1 interrupt
	IPC1bits.T1IP = 4;	// Timer 1 priority is 4

	oneSecondUp = FALSE;	// Intialize the one second flag
	msecCounter = 0;	// and the millisecond counter

	T1CONSET = 0x8000;	// Start the timer

}


/**
* @fn BOOL isOneSecondUp(void)
* @brief retourne TRUE si 1 sec a expiré depuis le dernière fois que la fonction a retourner un TRUE
*/
BOOL isOneSecondUp(void){
	
	BOOL result;

	if (oneSecondUp == TRUE){
		result = TRUE;	
		oneSecondUp = FALSE;
	}
	else{
		result = FALSE;
	}
	
	return(result);
}

void __attribute__((vector(4), interrupt(ipl4), nomips16)) Timer1InterruptHandler(void){

        /*** This is the Timer 1 ISR */
	IFS0CLR = 0x10; 	// Clear the Interrupt Flag
	
	msecCounter ++;		// Increment millisecond counter.
	
	if(msecCounter == ONE_SECOND_MSEC){
		oneSecondUp = TRUE;	/* Indicate that one second is up	*/
		msecCounter = 0;	/* Reset the millisecond counter.	*/
	}


}
