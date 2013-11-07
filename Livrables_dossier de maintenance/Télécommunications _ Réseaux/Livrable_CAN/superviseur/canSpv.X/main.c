/*******************************************************************************
* @file main.c
* @brief gestion de la communication CAN cote superviseur
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
    CAN1Init(CAN_FILTRE_DEMARRAGE);
    initTimer4();
    UART_Init();
    ShellInit();
    Prompt();

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
* @fn void saveContexte(char requete, char consigne, short filtre)
* @brief sauvegarde des var de la derniere requete
*/
void saveContexte(char requete, char consigne, short filtre)
{
    lastTypeReq = requete;
    lastConsigne = consigne;
    lastAdresse = filtre;
}

/**
* @fn int main(void)
* @brief point d'entrée du programme
*/
int main(void)
{
    /**************************************************************************/
    unsigned short i,j;
    char attenteReqModuleSelectionne = 1;
    char tempNbrBoostConnectes;
    /*** Initialise la board (périph & interrupt) */
    initBoard();
    
    /*** Initialisation des types VOLATILES */
    requeteEnCours = 0;
    timerRequeteEnCours = 0;
    consigneEnCours = 0;
    timerConsigneEnCours = 0;
    renvoi = 0;
    inviteEnCours = 0;
    timerInviteEnCours = 0;
    timerAvantNouvelleInvite = 100;
    //! ATTENTION !
    adresseInvit = CAN_FILTRE_DEMARRAGE;
    for(i=0; i<5; i++) valASCII[i]=0;
    for(i=0; i<255; i++) {
        for(j=0; j<3; j++) {
            tabBoostConnectes[i][j]=0;    
        }
    }
    consigneFromUart = 0;
    consigneToSend = 0;
    valConsigne = 0;
    adrConsigne = 0;
    nbrBoostConnectes = 0;

    LED1 = LED_ON;

    BOOL transmissionReussi;
    BOOL inviteReussi = is100MSecondUp();
    inviteReussi = isDemiSecondUp();
    i = 0, j = 0;
    inviteReussi = TRUE;
    //putUartStr("\r\n");
    while(1){
        //! gestion de l'interface shell
        shell();

        //! consigne prioritaire !
        if(consigneToSend == 1)
        {
             transmissionReussi = CAN1TxSendMsg(CONSIGNE,valConsigne,adrConsigne);
        }


        //! trame d'invite toutes les 0.5 sec
        if( ((isDemiSecondUp() == TRUE)))
        {
            
            //if(nbrBoostConnectes == CAN_NOMBRE_MODULES_POSSIBLES) putUartStr("Nombre MAX de boost connectés /!\\ \r\n");
            // faire clignoter LEDs (500ms allumé, 500ms éteinte si aucun module)
            ledInterface();
            // requete d'invite CAN, toujours a la fin car requêtes & consignes prioritaires
            if( (timerAvantNouvelleInvite >= DIZ_MS_AVANT_NOUVELLE_INVITE + 1) && nbrBoostConnectes < CAN_NOMBRE_MODULES_POSSIBLES )
            {
                inviteReussi = CAN1TxSendMsg(INVITE,0,adresseInvit);
            }
        } else if((inviteReussi == FALSE))
        {
             if( (timerAvantNouvelleInvite >= DIZ_MS_AVANT_NOUVELLE_INVITE + 1) && nbrBoostConnectes < CAN_NOMBRE_MODULES_POSSIBLES )
            {
                inviteReussi = CAN1TxSendMsg(INVITE,0,adresseInvit);
            }
        }

        //! simulation de requetes
        if((is100MSecondUp() == TRUE) && (attenteReqModuleSelectionne == 1))
        {

            //! en simulation de fonctionnement normal du superviseur
            transmissionReussi = CAN1TxSendMsg(REQUETE,0,tabBoostConnectes[j][0]);

            //! la requete a ete lancee
            attenteReqModuleSelectionne = 0;
        }          

        /* CAN1RxMsgProcess() will check if CAN1 has received a message */
        CAN1RxMsgProcess();

        // check des timer
        checkTimer();

        //! mise a jour du pointeur(globale) pour la prochaine requete
        if((requeteEnCours==0 && consigneEnCours==0 && inviteEnCours==0) && attenteReqModuleSelectionne==0)
        {
            do{
                j++;
            } while((tabBoostConnectes[j][0] == 0) && (j<CAN_NOMBRE_MODULES_POSSIBLES));
            attenteReqModuleSelectionne = 1;
        }
        if(j >= CAN_NOMBRE_MODULES_POSSIBLES) j = 0;

        //! maj du compteur de boost
        tempNbrBoostConnectes = nbrBoostConnectes;
        nbrBoostConnectes = 0;
        for(i=0; i<CAN_NOMBRE_MODULES_POSSIBLES; i++)
        {            
            if(tabBoostConnectes[i][0] != 0)
            {
                nbrBoostConnectes++;
            }
        }
        
        //! maj de l'adresse invit si trop de boost connectees
        if(tempNbrBoostConnectes == CAN_NOMBRE_MODULES_POSSIBLES && (nbrBoostConnectes == tempNbrBoostConnectes-1))
        {
            char compteur = 0;
            i = 0;
            while(tabBoostConnectes[i][0]!=0 && compteur<CAN_NOMBRE_MODULES_POSSIBLES)
            {
                i++;
                if(i >= CAN_FILTRE_MAX) i = CAN_FILTRE_DEMARRAGE;
                compteur++;
                
            }
            if(compteur == CAN_NOMBRE_MODULES_POSSIBLES) Nop();//putUartStr("Nombre MAX de boost connectés /!\\");
            else adresseInvit = i + CAN_FILTRE_DEMARRAGE;
        }
    }

    
}

