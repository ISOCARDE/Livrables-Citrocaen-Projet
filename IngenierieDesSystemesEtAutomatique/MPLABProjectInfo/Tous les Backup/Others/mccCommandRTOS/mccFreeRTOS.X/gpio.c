/**
* @file gpio.c
* @brief gestion des GPIO du PIC32
* @author Alain WERCK
* @date 25/10/2013
*/

/*** INCLUDES *****************************************************************/
    #include "main.h"

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

