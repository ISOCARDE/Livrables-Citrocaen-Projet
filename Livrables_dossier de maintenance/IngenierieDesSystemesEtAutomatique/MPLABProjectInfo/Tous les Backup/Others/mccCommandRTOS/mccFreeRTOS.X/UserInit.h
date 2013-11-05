/**
* @file UserInit.h
* @brief Configuration des differents perepheriques
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author GOURDEL Vincent / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

#ifndef USERINIT_H
#define	USERINIT_H


/*** VAR GLOBAL pour partie automatique ***************************************/
SpiChannel channel;
unsigned int sriClk;   // debit voulu : 3Mb/s
unsigned int sroClk;  // Frequence de travail du peripheriqe : 40MHz
float V_consigne[7];
float VO_mesuree[7];
float VI_mesuree[7];
float VIL_mesuree[7];
float commande[7];
float nouvelle_Commande;
float pDataVI;
float pDataVO;
float pDataVIL;


/**
 * @fn void UserIntit(void)
 * @brief Configuration de tous les périphériques
 */
void UserInit(void);

#endif	/* USERINIT_H */

