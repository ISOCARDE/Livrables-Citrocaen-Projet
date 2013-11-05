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
* @brief Permet la sélection des différents ChipSelect pour selectionner les
 * ADS7885 lors de l'acquisition des données VO, Vi et VIL délivrer pas le
 * Boost converter
*/
typedef struct{
    IoPortId Port;
    unsigned int Bit;
}SlaveS;

/*** VAR GLOBAL ***************************************************************/
unsigned int sriClk ; // débit voulu : 3Mb/s
unsigned int sroClk ; // Frequence de travail du p?riph?riqe : 40MHz
SlaveS SS1,SS2,SS3;

/**
* @fn handle SpiChannel ad7885Pic32Open(SpiChannel chn, unsigned int srcClkDiv);
* @brief Configuration liaison SPI coté MCU
* @param chn : canal SPI utilisé
* @param srcClkDiv : débit voulu
* @return le canal du SPI si la configuration est réussi, -1 sinon
*/
SpiChannel ad7885Pic32Open(SpiChannel chn, unsigned int srcClkDiv);

/**
 * @fn ad7885Pic32InitPort(void)
 * @brief Configuration des Ports /CS pour le SPI
 */
void ad7885Pic32InitPort(void);

/**
* void ad7885Pic32Read(SpiChannel CH, int* data, SlaveS SS);
* @brief Configuration liaison SPI coté MCU
* @param CH : canal SPI utilié
* @param * data : pointeur qui récupère les données
* @param SS : broche /CS utilisée
*/
void ad7885Pic32Read(SpiChannel CH, float* data, SlaveS SS);

/**
* @fn ad7634Pic32Close(Handle, chSPI)
* @brief ferme le canal SPI utilsé
* @param Chn : canal SPI à fermer
* @return
*/
void ad7885Pic32Close(SpiChannel Chn);

#endif	/* AD7885_H */



