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
* @brief Configuration liaison SPI cot� MCU
*
* @param chSPI : canal SPI utilis�
* @param freq : d�bit voulu
* @return 1 si la configuration est r�ussi, 0 sinon
*/
SpiChannel ad7885Pic32Open(SpiChannel chn, unsigned int srcClkDiv);


/**
* @fn void ad7634Pic32Read(Handle, chSPI, pData, SlaveS)
* @brief Configuration liaison SPI cot� MCU
*
* @param Handle : Permet de v�rifier si la configuration SPI cot� MCU est bien r�alis�e
* @param chSPI : canal SPI utili�
* @param pData : pointeur qui r�cup�re les donn�es
* @param SlaveS : broche /SS utilis�e
*/
void ad7885Pic32Read(SpiChannel CH, float* data, SlaveS SS);

/**
* @fn ad7634Pic32Close(Handle, chSPI)
* @brief ferme le canal SPI utils�
*
* @param Handle : Permet de v�rifier si la configuration SPI cot� MCU est bien r�alis�e
* @param chSPI : canal SPI � fermer
* @return
*/
void ad7885Pic32Close(SpiChannel Chn);



#endif	/* AD7885_H */

