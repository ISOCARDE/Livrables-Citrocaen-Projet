/*
 * File:   ad7884.c
 * Author: Vincent
 *
 * Created on 25 octobre 2013, 19:33
 */

/*** INCLUDES *****************************************************************/
#include "ad7885.h"

/*** FUNCTIONS ****************************************************************/
/**
* @fn handle ad7634Pic32Open(chSPI, freq)
* @brief Configuration liaison SPI coté MCU
*
* @param chSPI : canal SPI utilisé
* @param freq : débit voulu
* @return 1 si la configuration est réussi, 0 sinon
*/
//SpiChannel ad7885Pic32Open(SpiChannel chn, unsigned int srcClkDiv){
SpiChannel ad7885Pic32Open(SpiChannel chn, unsigned int srcClkDiv){

    unsigned int config;

        if (chn > 4 )
            return -1;


        config=SPI_OPEN_MODE16;  // SPI configuration PIC32
        config|=SPI_OPEN_ON;     // SPI périphérique est activé
        config|=SPI_OPEN_MSTEN;  // agit comme un maître de bus
        //config|=SPI_OPEN_SMP_END;// Données d'entrée échantillonnées à la fin du temps de sortie de données
        //config|=SPI_CON_FRMEN;   // le mode de tram est permis
        //config|=SPI_CON_FRMSYNC; //trame d'impulsion de synchronisation de sortie (mode Master
        //config|=SPI_CON_CKP;

        SpiChnOpen(chn, config , srcClkDiv);

        //Configure le Port /SS en out
        PORTSetPinsDigitalOut(IOPORT_A,BIT_3);
        PORTSetPinsDigitalOut(IOPORT_B,BIT_9 | BIT_14);


        // mise à niveau haut (high)
        PORTSetBits(IOPORT_A,BIT_3);
        PORTSetBits(IOPORT_B,BIT_14 | BIT_9);


        return chn;
}


/**
* @fn void ad7634Pic32Read(Handle, chSPI, pData, SlaveS)
* @brief Configuration liaison SPI coté MCU
*
* @param Handle : Permet de vérifier si la configuration SPI coté MCU est bien réalisée
* @param chSPI : canal SPI utilié
* @param pData : pointeur qui récupère les données
* @param SlaveS : broche /SS utilisée
*/
void ad7885Pic32Read(SpiChannel CH, float* data, SlaveS SS){

    int tempo=0;
    SpiChnPutC(CH,0xF0F0);

    // mise à niveau bas (low) afin de permettre le transfert avec l'ADC selectionné
    PORTClearBits(SS.Port,SS.Bit);

    tempo = (SpiChnGetC(CH));
    Nop();
    tempo=tempo>>6;
    Nop();

    PORTSetBits(SS.Port,SS.Bit);
    *data = (float)10*tempo*0.0195;
    SpiChnGetRov(CH, TRUE);

}

/**
* @fn ad7634Pic32Close(Handle, chSPI)
* @brief ferme le canal SPI utilsé
*
* @param Handle : Permet de vérifier si la configuration SPI coté MCU est bien réalisée
* @param chSPI : canal SPI à fermer
* @return
*/
void ad7885Pic32Close(SpiChannel Chn){

    // On ferme le canal SPI utilisé
    SpiChnClose(Chn);

    // /Cs en entrée pour le liberer
    PORTSetPinsDigitalIn(IOPORT_A,BIT_3);
    PORTSetPinsDigitalIn(IOPORT_B,BIT_9 | BIT_14);
}


