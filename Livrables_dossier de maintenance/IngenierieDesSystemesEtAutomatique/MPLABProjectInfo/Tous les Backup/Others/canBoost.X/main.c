/*******************************************************************************
* @file main.c
* @brief gestion CAN cote boost
* @author Alain WERCK
* @date 31/10/2013
*******************************************************************************/

/*** INCLUDES *****************************************************************/
    #include "includes.h"

/*** CONFIG *******************************************************************/

// POSCMOD = XT (externe 3,5MHz-10MHz) ou HS (externe 10MHz-40MHz)
// PLL si FNOSC = PRIPLL
// CPUfreq = 8MHz   (ext. christal explorer 16) / FPLIDIV .
//                  doit être compris entre 4MHz < ? < 5MHz (datasheet)
// CPUfreq = ( (8MHz (ext. explorer 16) / FPLLIDIV) x FPLLMUL ) / FPLLODIV
// FPBDIV = DIV_2 pré-config de la freq du bus periph. MAJ en soft dans le code
    #pragma config FWDTEN=OFF, CP=OFF, POSCMOD=XT, FNOSC=PRIPLL
    #pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPLLODIV=DIV_1, FPBDIV=DIV_2
    #pragma config FCANIO = OFF     // enable the CAN BUS


/*** PROTOTYPES ***************************************************************/

/**
* @fn void initBoard(void)
* @brief initialisation des différents périphériques de la board
*/
void initBoard(){    

    //Optimisation du fonctionnement du CPU
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    // Désactivation du JTAG pour libérer des broches
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);
    
    /*** Initialisation de tout les modules */
    initGPIO();
    CAN2Init(CAN_FILTRE_INVIT);
    initTimer4();
    UART_Init();

    /* Configure system for maximum performance and enable multi vector interrupts. */
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
}

/**
* @fn int puissance10(char puissance)
* @brief calcul de puissance de 10 avec la puissance passee en argument
*/
int puissance10(char puissance){

    int valeur = 1;
    char i;
    for(i=0; i<puissance; i++) valeur = valeur*10;

    return valeur;
}

/**
* @fn int main(void)
* @brief point d'entrée du programme
*/
int main(void)
{
    /**************************************************************************/
    short i,j;
    /*** Initialise la board (périph & interrupt) */
    initBoard();
    
    /*** Initialisation des types VOLATILES */
    filtreBoost = 0;
    //consigneBoost = 0;
    alea = 0;
    timerDecoBoost = 0;
    etat = 0;   
    for(i=0; i<5; i++) valASCII[i]=0;

   
    LED1 = LED_ON;

    BOOL raz = is100MSecondUp();
    raz = isDemiSecondUp();
    i = 0;
    putUartStr("\r\n");
    while(1){
        /*** CAN2RxMsgProcess will check if CAN2 has received a message */
        CAN2RxMsgProcess();
      
        // check des timer
        checkTimer();
    }    
}

