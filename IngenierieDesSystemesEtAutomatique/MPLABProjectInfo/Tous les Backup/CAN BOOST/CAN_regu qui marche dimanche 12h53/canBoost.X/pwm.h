/* 
 * File:   pwm.h
 * Author: Vincent
 *
 * Created on 29 octobre 2013, 17:40
 */

#ifndef PWM_H
#define	PWM_H


/*** INCLUDES *****************************************************************/


/*** MACROS *******************************************************************/

#define PB_DIV_2                253099
#define PRESCALE                4
#define TOGGLES_PER_SEC         1
#define T3_TICK                 (SYS_FREQ/PB_DIV_2/PRESCALE/TOGGLES_PER_SEC)

/*** VAR GLOBAL *****************************************************************/
// volatile unsigned int flagPwm;
unsigned int flagPwm;

/*** PROTOTYPES ***************************************************************/

/***************************************************************************//**
 * Configuration de l'Output Compare 1
 ******************************************************************************/
void pwmInit(void);

/***************************************************************************//**
 * changement du rapport cyclique PWM
 ******************************************************************************/
void pwmSet(float Pwm);

/***************************************************************************//**
 * Fermeture de l'Output Compare 1
 ******************************************************************************/
void pwmClose(void);

#endif	/* PWM_H */

