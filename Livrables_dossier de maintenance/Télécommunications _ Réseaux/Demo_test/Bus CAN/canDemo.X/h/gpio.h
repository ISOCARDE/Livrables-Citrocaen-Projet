/**
* @file gpio.h
* @brief gestion des GPIO du PIC32
* @author Alain WERCK
* @date 25/10/2013
*/

#ifndef _GPIO_H_
#define _GPIO_H_

#include <p32xxxx.h>
#include "GenericTypeDefs.h"

/* The LEDS and their ports	*/
#define LED1_TRIS               _TRISB10
#define LED2_TRIS		_TRISD1
#define LED3_TRIS		_TRISD2

#define LED1            _LATB10
#define LED2		_LATD1
#define LED3		_LATD2

#define LED_ON          1
#define LED_OFF         0

/*** Les pins */
#define	PINA5         	(PORTAbits.RA5)

void initGPIO(void);

#endif
