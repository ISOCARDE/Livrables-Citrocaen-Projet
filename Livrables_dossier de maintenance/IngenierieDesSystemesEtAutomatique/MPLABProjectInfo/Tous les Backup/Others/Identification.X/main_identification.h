/***************************************************************************//**
 * @file    main.h
 * @author  gourdel
 * @version 1.0
 * @date    11/03/13
 *
 * Header principal
 ******************************************************************************/

#ifndef MAIN_IDENTIFICATION_H
#define	MAIN_IDENTIFICATION_H

/*** INCLUDES *****************************************************************/

    #include <plib.h>
    #include "software.h"
    #include "uart.h"
    #include "ad7885.h"
    #include "timer3.h"
    #include "timer1.h"
    #include "pwm.h"
    #include "regulateur.h"

/*** CONFIG *******************************************************************/

    #pragma config FWDTEN=OFF, CP=OFF, POSCMOD=XT, FNOSC=PRIPLL
    #pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPLLODIV=DIV_1, FPBDIV=DIV_2

#endif	/* MAIN_H */