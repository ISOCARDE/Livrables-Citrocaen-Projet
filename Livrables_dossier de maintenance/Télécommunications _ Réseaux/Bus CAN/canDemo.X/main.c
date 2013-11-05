/**
* @file main.c
* @brief gestion de la demo de communication CAN
* @author Alain WERCK
* @date 25/10/2013
*/

#include <p32xxxx.h>
#include <peripheral\system.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "GenericTypeDefs.h"
#include ".\h\CANFunctions.h"
#include ".\h\gpio.h"

/* The code example shows how to transmit and receive
 * standard ID messages using the PIC32 CAN modules and
 * the PIC32 Peripheral Library. In this case, CAN1 
 * sends a Standard ID message to CAN1 and CAN2 replies
 * back with a Standard ID message.
 *
 * A timer is setup for 0.1 millisecond. This is used
 * to obtain a 1 second tick. Every 1 second, CAN1 will
 * send a message to CAN2 to toggle LEDx. CAN2 will
 * then send a message to CAN1 to toggle LEDx. Hence
 * both LEDs will toggle every second.*/

/* Configuration Bit settings
 * SYSCLK = 80 MHz (((8MHz Crystal/ FPLLIDIV) * FPLLMUL) / FPLLODIV)
 * PBCLK = 80 MHz
 * Primary Osc w/PLL (XT+,HS+,EC+PLL)
 * WDT OFF
 * Other options are don't care */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
#pragma config FCANIO = OFF
#define SYS_FREQ 				(80000000L)

/* Each CAN modulec uses 2 Channels (Channel 0
 * and Channel 1). Each channel is configured
 * to be 8 messages deep. Channel 0 is configured
 * for Transmit and Channel 1 is configured for
 * receive. CAN module configuration code
 * is in CANFunctions.c */ 

/* Note the size of each Channel area.
 * It is 2 (Channels) * 8 (Messages Buffers) 
 * 16 (bytes/per message buffer) bytes. Each 
 * CAN module should have its own message 
 * area. */

BYTE CAN1MessageFifoArea[2 * 8 * 16];
BYTE CAN2MessageFifoArea[2 * 8 * 16];

/**
* @fn void initBoard(void)
* @brief initialisation des différents périphériques de la board
*/
void initBoard(){
    

    /*** Rends tout les ports analogique en numérique */
    //AD1PCFGSET = 0xFFFFFFFF;

    /*** Initialisation de tout les modules */
    initGPIO();
    CAN1Init();
    CAN2Init();
    initTimer1();
    //UART_Init();

    /* Configure system for maximum performance
     * and enable multi vector interrupts. */
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
}

/**
* @fn int main(void)
* @brief point d'entrée du programme
*/
int main(void)
{
    /*** Initialise la board */
    initBoard();

    /*** test UART */
    unsigned char keyCode = 'a';
    //putUartC(keyCode);

    while(1){

        if(isOneSecondUp() == TRUE){
            /*** If one second is up then CAN1 sends a message to CAN2 to toggle LEDx */
            CAN1TxSendLEDMsg();
            //putUartC('a');
        }

        /*** CAN2RxMsgProcess will check if CAN2 has received a message from CAN1 and
         * will toggle LEDx. It will send a message to CAN1 to toggle LEDx. */
        CAN2RxMsgProcess();

        /* CAN1RxMsgProcess() will check if CAN1 has received a message from CAN2 and will toggle LEDx. */
        CAN1RxMsgProcess();
    }

    
}

