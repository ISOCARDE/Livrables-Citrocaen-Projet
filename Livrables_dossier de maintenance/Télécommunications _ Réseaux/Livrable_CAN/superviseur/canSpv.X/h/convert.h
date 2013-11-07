/**
* @file convert.h
* @brief
* @author VINCENT Simon
* @version 0.1
* @date 02 novembre 2013
*/

#ifndef __CONVERT__
#define __CONVERT__

#define VOETOILE    0
#define VO          1
#define VI          2
#define VIL         3
#define FACTEUR_CONVERSION     0.0195

/* GLOBALS ********************************************************************/
float voltagePerBit;

/* FUNCTION PROTOTYPES ********************************************************/

/**
 * @fn float convert(unsigned char)
 * @brief convertit les valeur numerique aquis par le SPI en valeur analogique
 * affichable sur l'interface
 */
float convert(unsigned char);

/**
 * @fn float convert(float**, unsigned short**, int)
 * @brief convertit les valeur numerique aquis par le SPI en valeur analogique
 * affichable sur l'interface
 */
void convertTab(float[255][3], unsigned short[255][3], int);
float convertTabBoostConnectes(int adresse,char mesureVoulue);

#endif