/**
* @file ad7884Pic32Read.c
* @brief librairie SPI pour pilotage ADC externe AD7884
* @author BLIN Valentin
* @date 22/05/2012
*/

#include "../include/ad7884Pic32.h"

/**
* @fn void ad7634Pic32Read(Handle, chSPI, pData, SlaveS)
* @brief Configuration liaison SPI coté MCU
*
* @param Handle : Permet de vérifier si la configuration SPI coté MCU est bien réalisée
* @param chSPI : canal SPI utilié
* @param pData : pointeur qui récupère les données
* @param SlaveS : broche /SS utilisée
*/
void ad7884Pic32Read(Handle H, chSPI CH, pData D, SlaveS SS){
	// Test si la configuration coté MCU s'est bien déroulée :
	if(H==HANDLE_INVALID) return;

        //Configure le Port /SS en out
        PORTSetPinsDigitalOut(SS.Port,SS.Bit);

	// mise à niveau bas (low) afin de permettre le transfert avec l'ADC selectionné
        PORTClearBits(SS.Port,SS.Bit);

	// permet de synchroniser avec sclk
        SpiChnPutC(CH,0xff);

	int data = SpiChnGetC(CH);

        // mise à niveau haut (high) afin de finir le transfert avec l'ADC selectionné
        PORTSetBits(SS.Port,SS.Bit);

//	*D=data;
}

