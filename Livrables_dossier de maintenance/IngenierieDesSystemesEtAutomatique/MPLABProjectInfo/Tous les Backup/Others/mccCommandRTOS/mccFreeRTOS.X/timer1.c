/**
* @file timer.c
* @brief Configuration du timer qui interroge l'ADC tous les 10us
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author GOURDEL Vincent / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

/*** INCLUDES *****************************************************************/
#include "main.h"


/**
 * @fn __ISR(_TIMER_2_VECTOR, ipl2) Timer2Handler(void)
 * @brief Configuration de l'interruption Timer1
 */
//__ISR(_TIMER_2_VECTOR, ipl2) Timer2Handler(void) {
//
//    // On baisse le flag
//    mT2ClearIntFlag();
//
//    mPORTAToggleBits( BIT_1 );
//
//    // Début de traitement
//    flagTraitement = 1;
//
//}
/**
 * @fn void timerInit(void)
 * @brief Initialise le Timer1
 */
void timerInit(void) {

    OpenTimer2( T2_ON | T2_SOURCE_INT | T2_PS_1_1, T2_TICK  );

    PORTSetPinsDigitalOut(IOPORT_A, BIT_1 ); // Definition des sorties

    PORTClearBits(IOPORT_A, BIT_1); // Initialisation ? 0 les portes

}

/**
 * @fn void timerIntConfig(void)
 * @brief Configuration du Timer1
 */
void timerIntConfig(void) {
    // PWM a une priorité de 2,
    // car il est vital qu'il soit traité immédiatement
     ConfigIntTimer2( T2_INT_ON | T2_INT_PRIOR_2 );
}

