/*
 * File:   pwm.c
 * Author: Vincent
 *
 * Created on 25 octobre 2013, 19:33
 */

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>

#pragma config FWDTEN=OFF, CP=OFF, POSCMOD=HS, FNOSC=PRIPLL
#pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPLLODIV=DIV_1, FPBDIV=DIV_2

#define SYS_FREQ                (80000000L)
#define PB_DIV                  253099
#define PRESCALE                4
#define TOGGLES_PER_SEC         1
#define T2_TICK                 (SYS_FREQ/PB_DIV/PRESCALE/TOGGLES_PER_SEC)


/*** GLOBALS ******************************************************************/

    //! Vaut 1 si on monte et 0 si on descend
    int Mode = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// !!!!! Ce qu'il faut changer
    #define RapportCyclique     0.8
/////////////////////////////////////////////////////////////////////////////////////////////////


    //! Nombre de cycles à l'état haut
    int Pwm = T2_TICK * RapportCyclique;

/*** INTERRUPTS ***************************************************************/

__ISR(_TIMER_2_VECTOR, IPL2SOFT) Timer2Handler(void) {
    if (Mode) {
        if (Pwm <= T2_TICK) SetDCOC1PWM(Pwm);
        else Mode = 0;
    } else{
        if(Pwm > 0) SetDCOC1PWM(Pwm);
        else Mode = 1;
    }
  //mPORTAToggleBits( BIT_7 );

 // clear the interrupt flag
 mT2ClearIntFlag( );
}



int main(int argc, char** argv) {

    //Optimisation du fonctionnement du CPU
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

     OpenTimer2( T2_ON | T2_SOURCE_INT | T2_PS_1_1, T2_TICK  );

     OpenOC1( OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);

     // Configuration de l'interruption du Timer3
     ConfigIntTimer3( T2_INT_ON | T2_INT_PRIOR_2 );

     //PR2 = 0x001E;
     // Activation des interruptions multi-vecteurs
    INTEnableSystemMultiVectoredInt();

    SetDCOC1PWM(Pwm);
        // Attente
    while(1);

    // Libération des broches
    CloseOC1();

    return (EXIT_SUCCESS);
}

