/*
 * File:   timerPwm.h
 * Author: Vincent
 *
 * Created on 28 octobre 2013, 02:01
 */

#ifndef TIMER_H
#define	TIMER_H

/*** INCLUDES *****************************************************************/

    #include <plib.h>
    #include "software.h"

/*** MACROS *******************************************************************/

    #define PB_DIV                  100000
    #define PRESCALE                4
    #define TOGGLES_PER_SEC         1
    #define T2_TICK                 (SYS_FREQ/PB_DIV/PRESCALE/TOGGLES_PER_SEC)

/*** VAR GLOBAL *****************************************************************/
// volatile unsigned int flagPwm;
unsigned int flagTraitement;


/*** PROTOTYPES ***************************************************************/

/***************************************************************************//**
 * Configuration du timer 3
 ******************************************************************************/
void timerInit(void);

/***************************************************************************//**
 * Configuration des interruptions
 ******************************************************************************/
void timerIntConfig(void);

#endif	/* TIMER_H */

