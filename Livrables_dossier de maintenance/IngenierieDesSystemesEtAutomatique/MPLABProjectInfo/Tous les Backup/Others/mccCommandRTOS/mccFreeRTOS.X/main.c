/**
* @file main.c
* @brief Programme principal
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author GOURDEL Vincent / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

/** INCLUDES *******************************************************/

#include "main.h"

/** CONFIGURATION **************************************************/
#pragma config FWDTEN=OFF, CP=OFF, POSCMOD=XT, FNOSC=PRIPLL
#pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPLLODIV=DIV_1, FPBDIV=DIV_2
#pragma config FCANIO = OFF     // enable the CAN BUS

//#pragma config FSRSSEL = PRIORITY_7 // testé sans, pour le can 

/*******************************************************************/
/** DECLARATIONS ***************************************************/
/*******************************************************************/
#pragma code

/********************************************************************
 * Function:        void main(void)
 *
 * Overview:        Point d'entrée du programme principal
 ********************************************************************/
int main(void){

    /*** configuration des differents perepheriques */
    UserInit();

    /*** Initialisations RTOS - Real Time Operating System ***/
    RTOSInit();

    /*** Démarrage de l'ordonnanceur ***/
    vTaskStartScheduler();

    while(1); // ... Nous ne reviendrons jamais ici !
}




