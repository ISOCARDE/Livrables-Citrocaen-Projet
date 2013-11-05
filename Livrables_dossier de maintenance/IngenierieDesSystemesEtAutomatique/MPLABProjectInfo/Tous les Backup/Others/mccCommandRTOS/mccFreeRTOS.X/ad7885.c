/**
* @file ad7885.c
* @brief Configuration liaison SPI et de l'AD7885
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
 * @fn SpiChannel ad7885Pic32Open(SpiChannel chn, unsigned int srcClkDiv)
 * @brief Configuration de la liaison SPI coté MCU
 */
SpiChannel ad7885Pic32Open(SpiChannel chn, unsigned int srcClkDiv){

    unsigned int config;

    if (chn > 4 )
        return -1;

    config=SPI_OPEN_MODE16;  // SPI configuration PIC32
    config|=SPI_OPEN_ON;     // SPI périphérique est activé
    config|=SPI_OPEN_MSTEN;  // agit comme un maître de bus

    SpiChnOpen(chn, config , srcClkDiv);

    //Configure les Port /CS_VI, /CS_VO et /CS_VIL en out
    PORTSetPinsDigitalOut(IOPORT_A,BIT_3);
    PORTSetPinsDigitalOut(IOPORT_B,BIT_9 | BIT_14);

    // mise à niveau haut
    PORTSetBits(IOPORT_A,BIT_3);
    PORTSetBits(IOPORT_B,BIT_14 | BIT_9);

    return chn;
}
/**
 * @fn ad7885Pic32InitPort(void)
 * @brief Configuration des Ports /CS pour le SPI
 */
void ad7885Pic32InitPort(void){

    /*ChipSelec VIL*/
    SS1.Port = IOPORT_A;
    SS1.Bit = BIT_3;

    /*ChipSelect Vo*/
    SS2.Port = IOPORT_B;
    SS2.Bit = BIT_14;

    /*ChipSelect de Vi*/
    SS3.Port = IOPORT_B;
    SS3.Bit = BIT_9;
}

/**
 * @fn void ad7885Pic32Read(SpiChannel CH, int* data, SlaveS SS)
 * @brief Lire la branche MISO du SPI
 */
void ad7885Pic32Read(SpiChannel CH, float* data, SlaveS SS){

    int tempo=0;

    //On envoie un charactère sur le MOSI pour obtenir le signal horloge SCK
    SpiChnPutC(CH,0xF0F0);

    // mise à niveau bas afin de permettre le transfert avec l'ADC selectionné
    PORTClearBits(SS.Port,SS.Bit);

    // Réception des données sur le MISO
    tempo = (SpiChnGetC(CH));
    Nop();
    tempo=tempo>>6;
    Nop();
    // mise à niveau haut afin de permettre le transfert avec l'ADC selectionné
    PORTSetBits(SS.Port,SS.Bit);
    *data = (float)10*tempo*0.0195; //si changement calcul => prevenir developpeur Werck
    SpiChnGetRov(CH, TRUE);
    if(SS.Bit == BIT_3){
        vilCan = (BYTE)(tempo);
    }
    else if(SS.Bit == BIT_14){
        voCan = (BYTE)(tempo);
    }
    else{
        viCan = (BYTE)(tempo);
    }


}

/**
 * @fn void ad7885Pic32Close(SpiChannel Chn)
 * @brief ferme le canal SPI utilsé
 */
void ad7885Pic32Close(SpiChannel Chn){

    // On ferme le canal SPI utilisé
    SpiChnClose(Chn);

    // /CS_VI, /CS_VO et /CS_VIL en entrée pour les liberer
    PORTSetPinsDigitalIn(IOPORT_A,BIT_3);
    PORTSetPinsDigitalIn(IOPORT_B,BIT_9 | BIT_14);
}




