/**
* @file UserInit.c
* @brief Configuration des differents perepheriques
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author GOURDEL Vincent / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

/*** INCLUDES *****************************************************************/
#include "main.h"


/**
* @fn void initBoard(void)
* @brief initialisation des différents périphériques de la board
*/
void initBoard(void);

/**
 * @fn void UserIntit(void)
 * @brief Configuration de tous les périphériques
 */
void UserInit(void){

    unsigned int    periphBusClk;
    int i;
    sriClk = 2500000;  // debit voulu : 3Mb/s
    sroClk = 80000000; // Frequence de travail du peripheriqe : 40MHz

     //Optimisation du fonctionnement du CPU
    periphBusClk = SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    // Désactivation du JTAG pour libérer des broches
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);

    // Initialisation de la partie Automatique
//    timerInit();
    pwmInit();
    channel = ad7885Pic32Open(SPI_CHANNEL4,sroClk/sriClk);
    ad7885Pic32InitPort();

    
    
    // Initialisation de l'UART
    UART_Init();
    ShellInit();
    Prompt();

    // Initialisation du CAN
    initBoard();
    
    // Configuration
//    timerIntConfig();

    /*** INTERRUPT CONFIGURATION ***/

    /*** Configuartion du mode "multi-vectored". Vecteurs d'interruption multiples ***/
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    /*** Validation globale des interruptions ***/
    INTEnableInterrupts();
    //INTEnableSystemMultiVectoredInt();


    /*les tableaux V_consigne et V_mesuree doivent etre rafraichis depuis les
    acquisition des ADC*/
    for(i=0;i<7;i++)
        V_consigne[i] = 24;

    for(i=0;i<7;i++)
        VI_mesuree[i] = 0;

    for(i=0;i<7;i++)
        VO_mesuree[i] = 0;

    for(i=0;i<7;i++)
        VIL_mesuree[i] = 0;

    for(i=0;i<7;i++)
        commande[i]=1;

    nouvelle_Commande=0;
    pDataVI = 0;
    pDataVO = 0;
    pDataVIL = 0;
}


/**
* @fn void initBoard(void)
* @brief initialisation des différents périphériques de la board
*/
void initBoard(void){

    /*** Initialisation de tout les modules */
    initGPIO();
    CANxInit(CAN_FILTRE_INVIT);
    initTimer4();

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