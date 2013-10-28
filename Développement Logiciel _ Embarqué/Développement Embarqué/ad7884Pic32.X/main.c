/* 
 * File:   main.c
 * Author: Simon
 *
 * Created on 27 octobre 2013, 13:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <p32xxxx.h>
#include <plib.h>
#include "./include/ad7884Pic32.h"

#pragma config FWDTEN = OFF/*, CP = OFF, POSCMOD = XT, FNOSC = PRIPLL
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20, FPLLODIV = DIV_1, FPBDIV = DIV_2*/


#define T3_TICK               0x0001

/*GLOBALS*******************/

int i=0;
Handle H;
int* Val;
SlaveS SS1,SS2,SS3;


/*INTERRUPT***************/

__ISR(_TIMER_3_VECTOR, IPL2SOFT) Timer3Handler(void) {

  //  int j;
    if (i==0){
        PORTSetBits(IOPORT_A,BIT_0 | BIT_4 |BIT_5);
        //ad7884Pic32Read(H,SPI_CHANNEL4,Val,SS1);
        i++;
    }
    else if (i==1){
        PORTClearBits(IOPORT_A,BIT_0 | BIT_4 |BIT_5);
        //ad7884Pic32Read(H,SPI_CHANNEL4,Val,SS2);
        i=0;
    }
    else {
        //ad7884Pic32Read(H,SPI_CHANNEL4,Val,SS3);
        i=0;
    }
    //for(j=0;j<100;j++);
    // clear the interrupt flag
    mT3ClearIntFlag( );
}


/*
 * 
 */
int main(int argc, char** argv) {

    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    OpenTimer3( T3_ON | T3_SOURCE_INT | T3_PS_1_1, T3_TICK  );

    ConfigIntTimer3( T3_INT_ON | T3_INT_PRIOR_2 );

    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);
  /*
    SS1.Port = IOPORT_A;
    SS1.Bit = BIT_5;

    SS2.Port = IOPORT_A;
    SS2.Bit = BIT_4;

    SS3.Port = IOPORT_A;
    SS3.Bit = BIT_0;
   
    
    H = ad7884Pic32Open(SPI_CHANNEL4,3000000);

    */

    PORTSetPinsDigitalOut(IOPORT_A,BIT_0 | BIT_4 |BIT_5);

    INTEnableSystemMultiVectoredInt();

    while(1);

    ad7884Pic32Close(H,SPI_CHANNEL4);
    
    return (EXIT_SUCCESS);
}

