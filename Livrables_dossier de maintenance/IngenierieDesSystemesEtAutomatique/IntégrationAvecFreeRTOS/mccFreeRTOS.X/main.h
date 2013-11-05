/**
* @file main.h
* @brief Header du main.c regroupant tous les fichiers et données éssentielles
* pour le programme principal
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author GOURDEL Vincent / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

#ifndef MAIN_H
#define	MAIN_H

/*** INCLUDES *****************************************************************/

// Application includes
#include <p32xxxx.h>    // PIC32
#include <plib.h>       // Périphériques

// RTOS includes
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Fonctions includes
#include "uart.h"
#include "ad7885.h"
#include "timer1.h"
#include "pwm.h"
#include "regulateur.h"
#include "software.h"
#include "RTOSInit.h"
#include "USERInit.h"
#include "interfaceShell.h"
#include "timerFunctions.h"
#include "gpio.h"
#include "canBoost.h"
#include "canCommon.h"

/* DEFINITIONS ***************/



/** MACROS *********************************************************/
#define GetSystemClock()        (40000000ul)
#define GetPeripheralClock()    (GetSystemClock())

//! Fréquence CPU
#define SYS_FREQ    (80000000L)

//! Fréquence UART
#define UART_FREQ   (40000000L)

//! Baudrate
#define BAUDRATE    115200

//! Diviseur de fréquence des périphériques
#define PB_DIV_CAN         	2

//! Fréquence périphériques
#define PERIPH_FREQ         (SYS_FREQ/PB_DIV_CAN)   // identique a l'uart

//! REQUETES CAN
#define INVITE      0
#define CONSIGNE    1
#define REQUETE     2
#define REPONSE     3
#define ACK         4

// REGLAGES CAN
#define DIZ_MS_AVANT_DECO               300

/*** GLOBALES *****************************************************************/
BYTE CANxMessageFifoArea[1 * 1 * 16];

/** VARIABLES ******************************************************/
#pragma idata

#endif	/* MAIN_H */

