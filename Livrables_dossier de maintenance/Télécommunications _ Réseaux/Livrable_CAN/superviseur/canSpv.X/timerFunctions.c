/**
* @file timerFunctions.c
* @brief gestion du timer 4 sur pic32
* @author Alain WERCK
* @date 25/10/2013
*/

/*** INCLUDES *****************************************************************/
    #include "includes.h"

/*** MACROS *******************************************************************/

    //! Période du timer
    #define T4_TICK       	25000

/*** GLOBALES ***************************************************************/
static BOOL demiSecondUp;
static UINT32 tenMillisecondsCounter;
static BOOL centMSecondUp;
static UINT32 tenMillisecondsCounterAgain;


/*** INTERRUPTS ***************************************************************/

__ISR(_TIMER_4_VECTOR, ipl2) Timer4Handler(void) {

    // On baisse le flag
    mT4ClearIntFlag();

    // on incremente le compteur
    tenMillisecondsCounter++;
    if(tenMillisecondsCounter == 50)
    {
        demiSecondUp = TRUE;
        tenMillisecondsCounter = 0;
    }

    tenMillisecondsCounterAgain++;
    if(tenMillisecondsCounterAgain == 10)
    {
        centMSecondUp = TRUE;
        tenMillisecondsCounterAgain = 0;
    }

    // timer pour la connection CAN
    timerRequeteEnCours++;
    timerConsigneEnCours++;
    timerInviteEnCours++;
    timerAvantNouvelleInvite++;
    if(timerAvantNouvelleInvite >= 10000) timerAvantNouvelleInvite = DIZ_MS_AVANT_NOUVELLE_INVITE +1;

}


/*** FUNCTIONS ****************************************************************/
/**
* @fn void initTimer4(void)
* @brief initialisation du timer 4 pour une interruption toutes les 10ms exacteement
*/
void initTimer4(void){

    // init du timer
    OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_16, T4_TICK);

    // set up the timer interrupt with a priority of 2
    ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_2);

    // initialisation du compteur
    tenMillisecondsCounter = 0;
    tenMillisecondsCounterAgain = 0;
}


/**
* @fn BOOL isOneSecondUp(void)
* @brief retourne TRUE si 0.5 sec a expiré depuis le dernière fois que la fonction a retourner un TRUE
*/
BOOL isDemiSecondUp(void){
	
	BOOL result;

	if (demiSecondUp == TRUE){
		result = TRUE;	
		demiSecondUp = FALSE;
	}
	else{
		result = FALSE;
	}
	
	return(result);
}

/**
* @fn BOOL is100MSecondUp(void)
* @brief retourne TRUE si 100 msec a expiré depuis le dernière fois que la fonction a retourner un TRUE
*/
BOOL is100MSecondUp(void){

	BOOL result;

	if (centMSecondUp == TRUE){
		result = TRUE;
		centMSecondUp = FALSE;
	}
	else{
		result = FALSE;
	}

	return(result);
}

/**
* @fn void checkTimer(void)
* @brief verification de la valeur des differents timer et prise d'action associee
*/
void checkTimer(void)
{
    // timer de temps de reponse a la requete
    if(timerRequeteEnCours >= DIZ_MS_AVANT_REPONSE && requeteEnCours == 1)
    {
        //! penser a sortir le boost de la table des allocation
        tabBoostConnectes[lastAdresse-CAN_FILTRE_DEMARRAGE][0] = 0;
        /**********************************************************************/
        putUartStr("Deconnecté SPV (ping trop long)"); putUartC('\r'); putUartC('\n');
        LED3 = LED_OFF;
        timerRequeteEnCours = 0;
        requeteEnCours = 0;
    }
    // timer de de temps d'acquittement a la consigne
    if(timerConsigneEnCours >= DIZ_MS_AVANT_ACK_CONSIGNE && consigneEnCours == 1)
    {
        //! penser a sortir le boost de la table des allocation
        tabBoostConnectes[lastAdresse-CAN_FILTRE_DEMARRAGE][0] = 0;
        /**********************************************************************/
        putUartStr("Deconnecté SPV (pas d'acquittement consigne)"); putUartC('\r'); putUartC('\n');
        //LED2 = LED_OFF;
        timerConsigneEnCours = 0;
        consigneEnCours = 0;      
    }
    // Invite en cours
    if((timerInviteEnCours >= DIZ_MS_AVANT_ACK_INVIT) && inviteEnCours == 1)
    {
        inviteEnCours = 0;
        timerInviteEnCours = 0;
    }
}
