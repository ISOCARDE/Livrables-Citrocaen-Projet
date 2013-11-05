/*
 * File:   timerPwm.h
 * Author: Vincent
 *
 * Created on 28 octobre 2013, 02:01
 */

/*** INCLUDES *****************************************************************/
#include "includes.h"

/*** INTERRUPTS ***************************************************************/
/***************************************************************************//**
 * Vecteur d'interruption du timer 2
 ******************************************************************************/
__ISR(_TIMER_2_VECTOR, ipl2) Timer2Handler(void) {

    // On baisse le flag
    mT2ClearIntFlag();
    
    mPORTAToggleBits( BIT_1 );
    // Début de traitement
    flagTraitement = 1;

}
/*** FUNCTIONS ****************************************************************/
/***************************************************************************//**
 * Configuration du timer 2
 ******************************************************************************/
void timerInit(void) {
    OpenTimer2( T2_ON | T2_SOURCE_INT | T2_PS_1_1, T2_TICK  );

    PORTSetPinsDigitalOut(IOPORT_A, BIT_1 ); // Definition des sorties

    PORTClearBits(IOPORT_A, BIT_1); // Initialisation ? 0 les portes


}

/***************************************************************************//**
 * Configuration des interruptions associées au timer 3
 ******************************************************************************/
void timerIntConfig(void) {
    // PWM a une priorité de 2,
    // car il est vital qu'il soit traité immédiatement
     ConfigIntTimer2( T2_INT_ON | T2_INT_PRIOR_2 );
}

