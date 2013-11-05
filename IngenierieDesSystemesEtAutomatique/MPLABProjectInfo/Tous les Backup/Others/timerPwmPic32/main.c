/***************************************************************************//**
 * @file    main.c
 * @author  PERROCHAUD Cl�ment
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
//                  doit �tre compris entre 4MHz < ? < 5MHz (datasheet)
// CPUfreq = ( (8MHz (ext. explorer 16) / FPLLIDIV) x FPLLMUL ) / FPLLODIV
// FPBDIV = DIV_2 pr�-config de la freq du bus periph. MAJ en soft dans le code
    #pragma config FWDTEN=OFF, CP=OFF, POSCMOD=XT, FNOSC=PRIPLL
    #pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPLLODIV=DIV_1, FPBDIV=DIV_2


/*** MACROS *******************************************************************/

    //! Fr�quence CPU
    #define SYS_FREQ            (80000000L)

    //! Diviseur de fr�quence des pr�iph�riques
    #define PB_DIV         	2

    //! Fr�quence p�riph�riques
    #define PERIPH_FREQ         (SYS_FREQ/PB_DIV)

    //! Diviseur de fr�quence du timer
    #define PRESCALE       	8

    //! Fr�quence du timer (en Hz)
    #define FREQ_TIMER          2000

    //! P�riode du timer
    #define T3_TICK       	(PERIPH_FREQ/PRESCALE/FREQ_TIMER)


/*** GLOBALS ******************************************************************/

    //! Vaut 1 si on monte et 0 si on descend
    int Mode = 0;

    //! Nombre de cycles � l'�tat haut
    int Pwm = 0;


/*** INTERRUPTS ***************************************************************/

__ISR(_TIMER_3_VECTOR, IPL2SOFT) Timer3Handler(void) {

    // On baisse le flag
    mT3ClearIntFlag();

    // On fait �voluer le rapport cyclique
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
 * Point d'entr�e du programme
 ******************************************************************************/
void main(void) {

    //Optimisation du fonctionnement du CPU
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    // D�sactivation du JTAG pour lib�rer des broches
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);

    // Configuration du Timer
    Timer_Init();

    // Configuration de l'Output Compare
    OCmp_Init();

    // Configuration des interruptions
    INT_Config();

    // Attente
    while(1);

    // Lib�ration des broches
    CloseOC2();
}
