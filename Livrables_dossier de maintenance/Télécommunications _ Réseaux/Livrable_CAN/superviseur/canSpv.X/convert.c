/**
* @file convert.c
* @brief Fonctions de convertion numerique/analogique
* @author VINCENT Simon
* @
* @version 0.1
* @date 02 novembre 2013
*/

/* INCLUDES DEPENDENCIES ***************/
#include "includes.h"

/**
 * @fn float convert(unsigned char)
 * @brief convertit les valeur numerique aquis par le SPI en valeur analogique
 * affichable sur l'interface
 */
float convert(unsigned char value){
    voltagePerBit=0.0195;
    return ((float)((BYTE)value))*voltagePerBit;
}

/**
 * @fn float convert(float**, unsigned short**, int)
 * @brief convertit les valeur numerique aquis par le SPI en valeur analogique
 * affichable sur l'interface
 */
void convertTab(float tabFloat[255][3], unsigned short tabBoost[255][3], int ligne){
    int i;
    for(i=0;i<ligne;i++){
        tabFloat[i][0]=convert((unsigned char)tabBoost[i][1]);
        tabFloat[i][1]=convert((unsigned char)(tabBoost[i][2]>>8));
        tabFloat[i][2]=convert((unsigned char)tabBoost[i][2]);
    }
};

/**
 * @fn float convertTabBoostConnectes(int adresse,char mesureVoulue)
 * @brief convertit les valeur numerique codé sur 8bits en float
 * affichable sur l'interface
 */
float convertTabBoostConnectes(int adresse,char mesureVoulue)
{
    float valConvertie;

    switch(mesureVoulue)
    {
        case VOETOILE:  valConvertie = /*(float)(10*(*/(unsigned char)(tabBoostConnectes[adresse][1]>>8)/*)*FACTEUR_CONVERSION)*/;
            break;
        case VO:        valConvertie = (float)(10*((BYTE)(0x00FF & tabBoostConnectes[adresse][1]))*FACTEUR_CONVERSION);
            break;
        case VI:        valConvertie = (float)(10*((BYTE)(float)(tabBoostConnectes[adresse][2]>>8))*FACTEUR_CONVERSION);
            break;
        case VIL:       valConvertie = (float)(10*((BYTE)(float)(0x00FF & tabBoostConnectes[adresse][2]))*FACTEUR_CONVERSION);
            break;

    }

    return valConvertie;

}
