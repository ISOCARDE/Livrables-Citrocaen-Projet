/***************************************************************************//**
 * @file    main.c
 * @author  PERROCHAUD Clément
 * @version 0.1
 * @date    18/02/13
 *
 * Programme de test Timer et PWM
 ******************************************************************************/

/*** INCLUDES *****************************************************************/

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

    //! Fréquence CPU
    #define SYS_FREQ            (80000000L)

    //! Diviseur de fréquence des préiphériques
    #define PB_DIV         	2

    //! Fréquence périphériques
    #define PERIPH_FREQ         (SYS_FREQ/PB_DIV)

    //! Diviseur de fréquence du timer
    #define PRESCALE       	8

    //! Fréquence du timer (en Hz)
    #define FREQ_TIMER          2000

    //! Période du timer
    #define T3_TICK       	(PERIPH_FREQ/PRESCALE/FREQ_TIMER)


/*** GLOBALS ******************************************************************/

    //! Vaut 1 si on monte et 0 si on descend
    int Mode = 0;

    //! Nombre de cycles à l'état haut
    int Pwm = 0;


/*** INTERRUPTS ***************************************************************/

__ISR(_TIMER_3_VECTOR, IPL2SOFT) Timer3Handler(void) {

    // On baisse le flag
    mT3ClearIntFlag();

    // On fait évoluer le rapport cyclique
    if (Mode) {
        if (Pwm <= T3_TICK) {
            Pwm++;
            SetDCOC2PWM(Pwm);
        } else {
            Mode = 0;
        }
    } else {
        if (Pwm > 0) {
            Pwm--;
            SetDCOC2PWM(Pwm);
        } else {
            Mode = 1;
        }
    }
}


/*** FUNCTIONS ****************************************************************/

/***************************************************************************//**
 * Configuration du Timer
 ******************************************************************************/
void Timer_Init(void) {
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_8, T3_TICK);
}

/***************************************************************************//**
 * Configuration de OC2
 ******************************************************************************/
void OCmp_Init(void) {
    OpenOC2( OC_ON | OC_TIMER3_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
}

/***************************************************************************//**
 * Configuration des interruptions
 ******************************************************************************/
void INT_Config() {

    // Configuration de l'interruption du Timer3
    ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_2);

    // Activation des interruptions multi-vecteurs
    INTEnableSystemMultiVectoredInt();
}

/***************************************************************************//**
 * Point d'entrée du programme
 ******************************************************************************/
void main(void) {

    //Optimisation du fonctionnement du CPU
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    // Désactivation du JTAG pour libérer des broches
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);

    // Configuration du Timer
    Timer_Init();

    // Configuration de l'Output Compare
    OCmp_Init();

    // Configuration des interruptions
    INT_Config();

    // Attente
    while(1);

    // Libération des broches
    CloseOC2();
}
