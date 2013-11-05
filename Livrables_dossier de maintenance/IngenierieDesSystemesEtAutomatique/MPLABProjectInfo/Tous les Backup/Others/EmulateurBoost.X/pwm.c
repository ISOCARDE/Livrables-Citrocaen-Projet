/*
 * File:   pwm.c
 * Author: Vincent
 *
 * Created on 25 octobre 2013, 19:33
 */

/*** INCLUDES *****************************************************************/

#include "includes.h"

/*** INTERRUPTS ***************************************************************/

__ISR(_TIMER_3_VECTOR, ipl5) Timer3Handler(void) {

    // On baisse le flag
    mT3ClearIntFlag();

    // Début de traitement
    flagPwm = 1;
}

/*** FUNCTIONS ****************************************************************/
/***************************************************************************//**
 * Configuration de l'Output Compare 1
 ******************************************************************************/
void pwmInit(void) {

     OpenTimer3( T3_ON | T3_SOURCE_INT | T3_PS_1_1, T3_TICK  );

     OpenOC1( OC_ON | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);

     // Configuration de l'interruption du Timer3
     ConfigIntTimer3( T3_INT_ON | T3_INT_PRIOR_5 );
}

/***************************************************************************//**
 * changement du rapport cyclique PWM
 ******************************************************************************/
void pwmSet(float Pwm){

    if (Pwm < 1)
        Pwm = 1;
    else if (Pwm > T3_TICK)
        Pwm = T3_TICK;
        SetDCOC1PWM(Pwm);
}

/***************************************************************************//**
 * Fermeture de l'Output Compare 1
 ******************************************************************************/
void pwmClose(void) {
    CloseOC1();
}



