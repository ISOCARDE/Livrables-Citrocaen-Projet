/**
* @file pwm.h
* @brief Configuration du signal Pwm
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author GOURDEL Vincent / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

#ifndef PWM_H
#define	PWM_H


/*** MACROS *******************************************************************/
#define SYS_FREQ                (80000000L) /*Vitesse travail bus matrix et CPU*/
#define PB_DIV_2                253099
#define PRESCALE                4
#define TOGGLES_PER_SEC         1
#define T3_TICK                 (SYS_FREQ/PB_DIV_2/PRESCALE/TOGGLES_PER_SEC)

/*** VAR GLOBAL ***************************************************************/
unsigned int flagPwm;

/**
 * @fn void pwmInit(void)
 * @brief Configuration de l'Output Compare 1 et du Timer1
 */
void pwmInit(void);

/**
 * @fn void pwmInit(void)
 * @brief changement du rapport cyclique PWM
 */
void pwmSet(float Pwm);

/**
 * @fn void pwmInit(void)
 * @brief Fermeture de l'Output Compare 1
 */
void pwmClose(void);

#endif	/* PWM_H */


