/*
 * File:   uart.h
 * Author: Vincent
 *
 * Created on 28 octobre 2013, 00:48
 */

#ifndef UART_H
#define	UART_H

/*** INCLUDES *****************************************************************/

    #include <plib.h>
    #include "software.h"


/*** MACROS *******************************************************************/
    #define MAX_STRING  100

/*** VAR GLOBAL *****************************************************************/
    unsigned char Cmd[MAX_STRING];
    unsigned int k;
    unsigned int flagReception;

/*** PROTOTYPES ***************************************************************/

/***************************************************************************//**
 * Configuration des interruptions
 * @return  Caractère reçu, ou '\0' si aucun caractère n'a été reçu
 ******************************************************************************/
unsigned char getUartC(void);

/***************************************************************************//**
 * @fn void putUartC ( unsigned char keyCode )
 * @brief envoie d'un caractere au terminal du PC relie par liaison serie
 ******************************************************************************/

void putUartC(unsigned char keyCode);

/***************************************************************************//**
 * @fn void putUartStr ( string keyCode )
 * @brief envoie d'une chaine de caractere au terminal du PC relie par liaison serie
******************************************************************************/
void putUartStr(unsigned char *ptString);

/***************************************************************************//**
  * @fn void UART_Init (void)
 * @brief initialisation du module UART1
 ******************************************************************************/
void UART_Init(void);

#endif	/* UART_H */

