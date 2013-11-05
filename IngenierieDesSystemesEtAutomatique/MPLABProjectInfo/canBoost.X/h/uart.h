/**
* @file uart.h
* @brief gestion de l'UART 1
* @author Alain WERCK
* @date 25/10/2013
*/

#ifndef UART_H
#define	UART_H

/*** PROTOTYPES ***************************************************************/

unsigned char getUartC(void);
void putUartStr(unsigned char *ptString);
void putUartC(unsigned char keyCode);
void UART_Init(void);

#endif	/* UART_H */

