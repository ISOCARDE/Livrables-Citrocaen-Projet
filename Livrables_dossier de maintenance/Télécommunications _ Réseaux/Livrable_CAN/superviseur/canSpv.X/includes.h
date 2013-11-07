/*******************************************************************************
* @file includes.h
* @brief gestion de tout les .h necessaire au fonctionnement
* @author Alain WERCK
* @date 27/10/2013
*******************************************************************************/

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
    #include ".\h\canSpv.h"
    #include ".\h\shellSupervision.h"
    #include ".\h\convert.h"

/*** MACROS *******************************************************************/

    //! Fréquence CPU
    #define SYS_FREQ    (80000000L)

    //! Fréquence UART
    #define UART_FREQ   (40000000L)

    //! Baudrate
    #define BAUDRATE    115200

    //!
    #define CONFIG_INVALID	0
    #define	HANDLE_INVALID	0
    #define	HANDLE_VALID	1

    //! Diviseur de fréquence des préiphériques
    #define PB_DIV         	2

    //! Fréquence périphériques
    #define PERIPH_FREQ         (SYS_FREQ/PB_DIV)   // identique a l'uart

    //! REQUETES CAN
    #define INVITE      0
    #define CONSIGNE    1
    #define REQUETE     2

    // REGLAGES CAN
    #define DIZ_MS_AVANT_REPONSE            100
    #define DIZ_MS_AVANT_ACK_CONSIGNE       5
    #define DIZ_MS_AVANT_ACK_INVIT          4
    #define DIZ_MS_AVANT_NOUVELLE_INVITE    100  // pas convaincu du 10

/*** GLOBALES *****************************************************************/
BYTE CAN1MessageFifoArea[2 * 8 * 16];

//!\ risque de mauvaise lecture de ces variables (le cas sur le boost en reception de consigne)
// a definir ailleurs si oui...
static char tabValSortie[10] = {    '0','0',
                                    '1','8',
                                    '2','4',
                                    '3','0',
                                    '3','6'};
char lastTypeReq;
char lastConsigne;
short lastAdresse;
volatile char consigneToSend;
volatile char nbrBoostConnectes;

#endif	/* INCLUDES_H */

