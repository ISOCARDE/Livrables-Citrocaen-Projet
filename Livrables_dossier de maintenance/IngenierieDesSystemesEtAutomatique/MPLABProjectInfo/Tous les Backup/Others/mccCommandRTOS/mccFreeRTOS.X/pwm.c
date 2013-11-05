/**
* @file pwm.c
* @brief Configuration du signal Pwm
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
 * @fn void __ISR(_TIMER_2_VECTOR, IPL2SOFT) Timer2Handler(void)
 * @brief Définie l'interuption du Pwm
 */

//__ISR(_TIMER_3_VECTOR, ipl2) Timer3Handler(void) {
//
//    // On baisse le flag
//    mT3ClearIntFlag();
//
//    // Début de traitement
//    flagPwm = 1;
//}

/**
 * @fn void pwmInit(void)
 * @brief Configuration de l'Output Compare 1 et du Timer1
 */
void pwmInit(void) {

     OpenTimer3( T3_ON | T3_SOURCE_INT | T3_PS_1_1, T3_TICK  );

     OpenOC1( OC_ON | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);

     // Configuration de l'interruption du Timer3
     //ConfigIntTimer3( T3_INT_ON | T3_INT_PRIOR_2 );
}

/**
 * @fn void pwmInit(void)
 * @brief changement du rapport cyclique PWM
 */
void pwmSet(float Pwm){

    if (Pwm < 1)
        Pwm = 1;
    else if (Pwm > T3_TICK)
        Pwm = T3_TICK;
        SetDCOC1PWM(Pwm);
}

/**
 * @fn void pwmInit(void)
 * @brief Fermeture de l'Output Compare 1
 */
void pwmClose(void) {
    CloseOC1();
}

