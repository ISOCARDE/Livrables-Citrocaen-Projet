/**
* @file RTOSInit.c
* @brief Initialisations RTOS - Real Time Operating System
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author GOURDEL Vincent / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

#ifndef RTOSINIT_H
#define	RTOSINIT_H

/***GLOBAL*********************************************************************/



/**
 * @fn void RTOSInit(void)
 * @brief Cette fonction initialise notre noyau avant de le lancer (cr�ations
 * t�ches, cr�ations files d'attente,cr�ations s�maphores ...)
 */
void RTOSInit(void);
/**
 * @fn void TacheRegulation( void *pvParameters )
 * @brief Cette fonction initialise notre noyau avant de le lancer (cr�ations
 * t�ches, cr�ations files d'attente,cr�ations s�maphores ...)
 */
void TacheRegulation( void *pvParameters );
void TacheRegulation_bis( void *pvParameters );

/**
 * @fn void TacheUART( void *pvParameters )
 * @brief Lance l'interface
 */
void TacheUART( void *pvParameters );

/**
 * @fn void TacheUART( void *pvParameters )
 * @brief Lance l'interface
 */
void TacheCAN( void *pvParameters );
#endif	/* RTOSINIT_H */

