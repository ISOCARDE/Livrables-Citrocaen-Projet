/**
* @file ad7884Pic32Close.c
* @brief librairie SPI pour pilotage ADC externe AD7634
* @date 22/05/2012
* Librairie SPI pour pilotage ADC externe AD7634
*/

#include "../include/ad7884Pic32.h"

/**
* @fn ad7634Pic32Close(Handle, chSPI)
* @brief ferme le canal SPI utilsé
*
* @param Handle : Permet de vérifier si la configuration SPI coté MCU est bien réalisée
* @param chSPI : canal SPI à fermer
* @return
*/
void ad7884Pic32Close(Handle H, chSPI CH){

    if (H == 0)return;
    else
    // On ferme le canal SPI utilisé
     SpiChnClose(CH);

}