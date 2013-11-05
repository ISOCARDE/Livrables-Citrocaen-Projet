/**
* @file fucntionTest.c
* @brief Fonction pour la configuration du codec Audio TLV320AIC23.
* Configuration via liaison SPI
* IDE MPLAB X vs Beta 7.02
* Compilateur C32 vs 2.0
* @author nom1 nom2 groupe promo
* @version 0.1
* @date 21 février 2012
*/

/* INCLUDES DEPENDENCIES ***************/
#include "headerTest.h"

/* MACROS ***************/
#define SIZE	300	


/**
 * @fn HandleAic23 aic23Pic32_open( char* returnData, 
 * ConfigAic23 configCodec );
 * @brief Configuration codec audio TLV320AIC23 via liaison SPI
 */
 HandleAic23 aic23Pic32_open( char* returnData, ConfigAic23 configCodec ) {

	int i;
	
    if ( configCodec == CONFIG_INVALID )
        return HANDLE_INVALID;
	
	// Algorithme de filtrage récursif
	for(i = 0; i < SIZE; i++) {
		// Corps de la boucle
	}
	
    return HANDLE_VALID;
 }
