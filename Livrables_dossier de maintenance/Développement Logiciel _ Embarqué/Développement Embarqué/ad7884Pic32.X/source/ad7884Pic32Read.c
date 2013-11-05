/**
* @file ad7884Pic32Read.c
* @brief librairie SPI pour pilotage ADC externe AD7884
* @author BLIN Valentin
* @date 22/05/2012
*/

#include "../include/ad7884Pic32.h"

/**
* @fn void ad7634Pic32Read(Handle, chSPI, pData, SlaveS)
* @brief Configuration liaison SPI cot� MCU
*
* @param Handle : Permet de v�rifier si la configuration SPI cot� MCU est bien r�alis�e
* @param chSPI : canal SPI utili�
* @param pData : pointeur qui r�cup�re les donn�es
* @param SlaveS : broche /SS utilis�e
*/
void ad7884Pic32Read(Handle H, chSPI CH, pData D, SlaveS SS){
	// Test si la configuration cot� MCU s'est bien d�roul�e :
	if(H==HANDLE_INVALID) return;

        //Configure le Port /SS en out
        PORTSetPinsDigitalOut(SS.Port,SS.Bit);

	// mise � niveau bas (low) afin de permettre le transfert avec l'ADC selectionn�
        PORTClearBits(SS.Port,SS.Bit);

	// permet de synchroniser avec sclk
        SpiChnPutC(CH,0xff);

	int data = SpiChnGetC(CH);

        // mise � niveau haut (high) afin de finir le transfert avec l'ADC selectionn�
        PORTSetBits(SS.Port,SS.Bit);

//	*D=data;
}

