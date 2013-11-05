/*
 * File:   ad7885.h
 * Author: Vincent
 *
 * Created on 28 octobre 2013, 19:02
 */

#ifndef AD7885_H
#define	AD7885_H

    #include <plib.h>
    #include "software.h"

/* STRUCTURE ***************/

typedef struct{
    IoPortId Port;
    unsigned int Bit;
}SlaveS;

/*** MACROS *******************************************************************/
   unsigned int sriClk ; // d?bit voulu : 3Mb/s
   unsigned int sroClk ; // Frequence de travail du p?riph?riqe : 40MHz

/* FUNCTION PROTOTYPES ***************/

/*** FUNCTIONS ****************************************************************/
/**
* @fn handle ad7634Pic32Open(chSPI, freq)
* @brief Configuration liaison SPI coté MCU
*
* @param chSPI : canal SPI utilisé
* @param freq : débit voulu
* @return 1 si la configuration est réussi, 0 sinon
*/
SpiChannel ad7885Pic32Open(SpiChannel chn, unsigned int srcClkDiv);


/**
* @fn void ad7634Pic32Read(Handle, chSPI, pData, SlaveS)
* @brief Configuration liaison SPI coté MCU
*
* @param Handle : Permet de vérifier si la configuration SPI coté MCU est bien réalisée
* @param chSPI : canal SPI utilié
* @param pData : pointeur qui récupère les données
* @param SlaveS : broche /SS utilisée
*/
void ad7885Pic32Read(SpiChannel CH, float* data, SlaveS SS);

/**
* @fn ad7634Pic32Close(Handle, chSPI)
* @brief ferme le canal SPI utilsé
*
* @param Handle : Permet de vérifier si la configuration SPI coté MCU est bien réalisée
* @param chSPI : canal SPI à fermer
* @return
*/
void ad7885Pic32Close(SpiChannel Chn);



#endif	/* AD7885_H */

