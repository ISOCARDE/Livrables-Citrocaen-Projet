/**
* @file ad7885.h
* @brief Configuration liaison SPI et de l'AD7885
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author GOURDEL Vincent / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

#ifndef AD7885_H
#define	AD7885_H

/* STRUCTURE ******************************************************************/
/**
* @struct SlaveS
* @brief Permet la s�lection des diff�rents ChipSelect pour selectionner les
 * ADS7885 lors de l'acquisition des donn�es VO, Vi et VIL d�livrer pas le
 * Boost converter
*/
typedef struct{
    IoPortId Port;
    unsigned int Bit;
}SlaveS;

/*** VAR GLOBAL ***************************************************************/
unsigned int sriClk ; // d�bit voulu : 3Mb/s
unsigned int sroClk ; // Frequence de travail du p?riph?riqe : 40MHz
SlaveS SS1,SS2,SS3;

/**
* @fn handle SpiChannel ad7885Pic32Open(SpiChannel chn, unsigned int srcClkDiv);
* @brief Configuration liaison SPI cot� MCU
* @param chn : canal SPI utilis�
* @param srcClkDiv : d�bit voulu
* @return le canal du SPI si la configuration est r�ussi, -1 sinon
*/
SpiChannel ad7885Pic32Open(SpiChannel chn, unsigned int srcClkDiv);

/**
 * @fn ad7885Pic32InitPort(void)
 * @brief Configuration des Ports /CS pour le SPI
 */
void ad7885Pic32InitPort(void);

/**
* void ad7885Pic32Read(SpiChannel CH, int* data, SlaveS SS);
* @brief Configuration liaison SPI cot� MCU
* @param CH : canal SPI utili�
* @param * data : pointeur qui r�cup�re les donn�es
* @param SS : broche /CS utilis�e
*/
void ad7885Pic32Read(SpiChannel CH, float* data, SlaveS SS);

/**
* @fn ad7634Pic32Close(Handle, chSPI)
* @brief ferme le canal SPI utils�
* @param Chn : canal SPI � fermer
* @return
*/
void ad7885Pic32Close(SpiChannel Chn);

#endif	/* AD7885_H */



