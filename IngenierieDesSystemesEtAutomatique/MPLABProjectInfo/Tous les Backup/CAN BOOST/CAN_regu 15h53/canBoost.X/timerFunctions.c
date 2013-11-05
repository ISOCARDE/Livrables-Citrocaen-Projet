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

    // valeur aleatoire (ou presque)
    alea++;
    if(alea == 255)
    {
        alea = 0;
    }

    // timer pour la connection CAN
    timerDecoBoost++;

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

    // init val aleatoire
    alea = 0;
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
    // timer deconnection de boost
    if(timerDecoBoost >= DIZ_MS_AVANT_DECO && etat)
    {
        CANxInitFiltre(CAN_FILTRE_INVIT);
        putUartStr("Deconnecté BOOST (plus de données reçues)"); putUartC('\r'); putUartC('\n');
        timerDecoBoost = 0;
        etat = 0;
    }
}
