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

#ifndef TIMER_H
#define	TIMER_H

/*** MACROS *******************************************************************/
#define PB_DIV                  10000
#define PRESCALE                4
#define TOGGLES_PER_SEC         1
#define T2_TICK                 (SYS_FREQ/PB_DIV/PRESCALE/TOGGLES_PER_SEC)

/*** VAR GLOBAL ***************************************************************/
unsigned int flagTraitement;

/**
 * @fn void timerInit(void)
 * @brief Initialise le Timer1
 */
void timerInit(void);

/**
 * @fn void timerIntConfig(void)
 * @brief Configuration du Timer1
 */
void timerIntConfig(void);

#endif	/* TIMER_H */

