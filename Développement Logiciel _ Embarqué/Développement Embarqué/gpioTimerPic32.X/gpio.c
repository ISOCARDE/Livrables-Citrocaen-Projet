/***************************************************************************//**
 * @file        main.c
 * @author      VINCENT Simon
 * @author      GOURDEL Vincent
 * @date        23/10/13
 *
 * Validation de l'utilisation des GPIO sur PIC32
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>

/*** CONFIG *******************************************************************/

// POSCMOD = XT (externe 3,5MHz-10MHz) ou HS (externe 10MHz-40MHz)
// PLL si FNOSC = PRIPLL
// CPUfreq = 8MHz   (ext. christal explorer 16) / FPLIDIV .
//                  doit être compris entre 4MHz < ? < 5MHz (datasheet)
// CPUfreq = ( (8MHz (ext. explorer 16) / FPLLIDIV) x FPLLMUL ) / FPLLODIV
// FPBDIV = DIV_2 pré-config de la freq du bus periph. MAJ en soft dans le code
    #pragma config FWDTEN=OFF, CP=OFF, POSCMOD=XT, FNOSC=PRIPLL
    #pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPLLODIV=DIV_1, FPBDIV=DIV_2


/*** MACROS *******************************************************************/

#define SYS_FREQ             (80000000L)



/*** INTERRUPTS ***************************************************************/

__ISR(_TIMER_2_VECTOR, IPL2SOFT) Timer2Handler(void) {

//mPORTAToggleBits( BIT_5 );
    mPORTBToggleBits( BIT_10 );

 // clear the interrupt flag
 mT2ClearIntFlag( );
}

/*** FUNCTIONS ****************************************************************/

int main(int argc, char** argv) {

   // Optimisation des performances
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    //PORTSetPinsDigitalOut(IOPORT_A, BIT_5 ); // Definition des sorties

    //PORTClearBits(IOPORT_A, BIT_5); // Initialisation ? 0 les portes

    PORTSetPinsDigitalOut(IOPORT_B, BIT_10 ); // Definition des sorties

    PORTClearBits(IOPORT_B, BIT_10); // Initialisation ? 0 les portes

    OpenTimer2( T2_ON | T2_SOURCE_INT | T2_PS_1_256, 0x9880 );

         // Configuration de l'interruption du Timer3
     ConfigIntTimer2( T2_INT_ON | T2_INT_PRIOR_2 );

     // Activation des interruptions multi-vecteurs
    INTEnableSystemMultiVectoredInt();

        // Attente
    while(1);

    return (EXIT_SUCCESS);

}

