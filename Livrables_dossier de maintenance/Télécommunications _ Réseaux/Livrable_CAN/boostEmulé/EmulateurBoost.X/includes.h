/**
* @file includes.h
* @brief gestion de tout les .h necessaire au fonctionnement
* @author Alain WERCK
* @date 27/10/2013
*/

#ifndef INCLUDES_H
#define	INCLUDES_H

/*** INCLUDES *****************************************************************/
    #include <plib.h>
    #include <p32xxxx.h>
    #include <peripheral\system.h>
    #include <sys/kmem.h>
    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>
    #include <stdlib.h>
    #include "GenericTypeDefs.h"
    #include ".\h\canCommon.h"
    #include ".\h\gpio.h"
    #include ".\h\timerFunctions.h"
    #include ".\h\uart.h"
    #include ".\h\canBoost.h"

    #include "pwm.h"
    #include "software.h"
    #include "regulateur.h"
    #include "timer1.h"
    #include "ad7885.h"

/*** MACROS *******************************************************************/

    //! Fréquence CPU
    #define SYS_FREQ    (80000000L)

    //! Fréquence UART
    #define UART_FREQ   (40000000L)

    //! Baudrate
    #define BAUDRATE    115200

    //! Diviseur de fréquence des préiphériques
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
float consigneDuCan;
BYTE voBoostToCan;
BYTE viBoostToCan;
BYTE vilBoostToCan;

#endif	/* INCLUDES_H */

