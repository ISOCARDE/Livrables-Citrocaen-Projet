/**
* @file gpio.c
* @brief gestion des GPIO du PIC32
* @author Alain WERCK
* @date 25/10/2013
*/

/*** INCLUDES *****************************************************************/
    #include "includes.h"

/*** PROTOTYPES ***************************************************************/
/**
* @fn void initGPIO(void)
* @brief initialisation des GPIO du PIC32, toute LED eteintes
*/
void initGPIO(void){

	/*** Intialize the board LED and turn all LEDS off */	 
	LED1_TRIS = 0;
	LED2_TRIS = 0;
        LED3_TRIS = 0;
        
	LED1 = LED_OFF;
	LED2 = LED_OFF;
        LED3 = LED_OFF;

        PINA5_TRIS = 0;
}

void isBoostConnected(void){

    if(voBoostToCan>10 || voBoostToCan<50) LED2 = LED_ON;
    else{
        if(LED2 = LED_OFF) LED_ON;
        else LED2 = LED_OFF;
    }

}
