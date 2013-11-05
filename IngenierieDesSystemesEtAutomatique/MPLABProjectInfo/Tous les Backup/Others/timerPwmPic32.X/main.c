/**
* @file Timer.c
* @brief à compléter !
* @author NUNES e SILVA Leonardo / VINCENT Simon
* @version 1.3
* @date 19/02/2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>

/* CONFIGURATION BITS ***************/
// POSCMOD = XT (chrital externe 3,5MHz-10MHz) ou HS (chrital externe 10MHz-40MHz)
// PLL si FNOSC = PRIPLL
// CPUfreq = 8MHz   (ext. christal explorer 16) / FPLLIDIV .
//                  doit être compris entre 4MHz < ? < 5MHz (datasheet)
// CPUfreq = ( (8MHz (ext. christal explorer 16) / FPLLIDIV) x FPLLMUL ) / FPLLODIV
// FPBDIV = DIV_2 pré-config de la freq du bus periph. MAJ en soft dans le code
#pragma config FWDTEN = OFF, CP = OFF, POSCMOD = XT, FNOSC = PRIPLL
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20, FPLLODIV = DIV_1, FPBDIV = DIV_2

#define SYS_FREQ             (80000000L)
#define PB_DIV                 2
#define PRESCALE               4
#define TOGGLES_PER_SEC        1
#define T3_TICK               (SYS_FREQ/PB_DIV/PRESCALE/TOGGLES_PER_SEC)

#pragma code
/**
* @fn void main (void)
* @brief point d'entrée du programme
*/


int main(void){

   SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

   // Timer 3 config
   OpenTimer3(T3_ON | T3_SOURCE_INT | T3_IDLE_CON | T3_GATE_ON | T3_PS_1_4 , T3_TICK);
   // T3_TICK = PR3 = 1000
   ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_2);


   // PWM config

   /* Enable OC 2 | 16 bit Mode  | Timer3 is selected | OC Pin High , S Compare value, Compare value*/
    OpenOC2( OC_ON | OC_TIMER_MODE16 | OC_TIMER3_SRC | OC_LOW_HIGH | OC_CONTINUE_PULSE , 0x00, 0x00 );

     // Si on utilise le while(1) les 2 fonction au-dessous ne sont pas besoin
    CloseTimer3();
    CloseOC2();
   }

void __ISR(_TIMER_3_VECTOR, ipl5) Timer3Handler(void){
    int duty_cycle;
    // clear the interrupt flag
    INTClearFlag(INT_T3)

    // Pour allumer un del et tester 
    mPORTAToggleBits(BIT_7);
    mPORTAToggleBits(BIT_6);
    // Si c'est moins que le rapport
    // On configure le rapport à travers la divisiondu TICK pour un chiffre.
    if(duty_cycle < T3_TICK){
        duty_cycle = duty_cycle + T3_TICK/100;
    }
    else {
        duty_cycle = 0;
    }
    //Writes passed data to the dutycycle register
    SetDCOC2PWM(duty_cycle);
}



// Code défini par registres
    /*
    // Initialisation
    T3CONbits.ON = 0; // Timer 3 desactivé
    TMR3 = 0x0; //Début de la comptage
    // Chargement des valeurs
    T3CONbits.SIDL = 0; // Mode IDLE desactivé. Il continue n'importe l'état du
                        // système
    T3CONbits.TCS = 1; // Clock externe
                       // T32 est le Timer avec 32 bits. Il n'est disponible que
                       // en Timer's pairs.
    T3CONbits.TCKPS = 0b010; // Prescale. On doit choisir par rapport au PWM *****
    TMR3 = 0xFF;     // Configurer le Timer **********
    PR3 = 1000; // Configurer le periode. *************
    //Gestion des Interruptions

    IEC0bits.T3IE = 1; // Interrupteur Timer 3. Niveau haut.
    IFS0bits.T3IF = 0; // Desactivation du flag de l'interruption du Timer3
    IPC3bits.T3IP = 0b111; // Priorité 7 avant le Timer1(MCU), Timer2(RTOS)
    
}*/
/*
void PWM_cfg(void){
    //Initialisation du OC2
    OC2CONbits.ON = 0; // Desactivé
    // Controle de Registre du Output Compare 2
    OC2CONbits.SIDL = 0; //Continuation même étant IDLE
    OC2CONbits.OC32 = 0; // Mode 16 bits en utilisant OC2R et OC2RS
    OC2CONbits.OCTSEL = 1; // Utilisation du Timer3
    OC2CONbits.OCFLT = 1; //On utilise le Flag d'erreur
    OC2CONbits.OCM = 0b111; // PWM avec le flag

    OC2R = 0x0000; // Lorsque la valeur OC32 est 0 il compare avec OC2R
    OC2RS = 0x0000; // Lorsque la valeur OC32 est 0 il compare avec OC2R

    //Gestion des Interruptions
    IEC0bits.OC2IE = 1; // Interruption activé
    IFS0bits.OC2IF = 0; // Flag desactivé
    IPC2bits.OC2IP = 0B110; // Priorité 6 après le Timer
}
*/