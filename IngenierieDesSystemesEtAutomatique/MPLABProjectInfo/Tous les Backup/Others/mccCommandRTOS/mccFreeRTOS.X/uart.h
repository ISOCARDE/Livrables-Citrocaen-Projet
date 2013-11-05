/**
* @file uart.c
* @brief Configuration de l'uart pour la communication RS-232
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author GOURDEL Vincent / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

#ifndef UART_H
#define	UART_H


/*** MACROS *******************************************************************/
#define UART_FREQ   (40000000L) /*Vitesse travail bus de l'UART*/
#define BAUDRATE    115200      /*BAUDRATE de l'UART*/

#define MAX_STRING  100

/*** VAR GLOBAL ****************************************************************/
//unsigned char Cmd[MAX_STRING];
//unsigned int k;
unsigned int flagReception;

/**
 * @fn void UART_Init (void)
 * @brief initialisation du module UART1
 */
void UART_Init(void);

/**
 * @fn unsigned char getUartC()
 * @brief reception d'un caractere envoyé sur le port serie
 */
unsigned char getUartC(void);

/**
 * @fn void putUartC ( unsigned char keyCode )
 * @brief envoie d'un caractere au terminal du PC relie par liaison serie
 * @param Le caractère que l'on veut envoyer
 */
void putUartC(unsigned char keyCode);

/**
 * @fn void putUartStr ( string keyCode )
 * @brief envoie d'une chaine de caractere au terminal du PC relie par liaison serie
 * @param La chainde de caractère que l'on veut envoyer
 */
void putUartStr(unsigned char *ptString);

#endif	/* UART_H */

