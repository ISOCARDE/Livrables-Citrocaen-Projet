/**
* @file regulateur.h
* @brief Configuration des differents perepheriques
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author GOURDEL Vincent / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

#ifndef REGULATEUR_H
#define	REGULATEUR_H

/*** VAR GLOBAL ***************************************************************/


/***FUNCTIONS *****************************************************************/
/**
 * @fn float regulateur_PI(float *commande,float *V_consigne,float *V_mesuree)
 * @brief Calcul de la commande
 * @param Tableau de commande
 * @param Tableau de V_consigne
 * @param Tableau de V_mesuree
  */

float regulateur_PI(float *commande,float *V_consigne,float *VO_mesuree);
/**
 * @fn float regulateur_trois(float *commande,float *V_consigne,float *V_mesuree)
 * @brief Calcul de la commande
 * @param Tableau de commande
 * @param Tableau de V_consigne
 * @param Tableau de V_mesuree
  */

float regulateur_trois(float *commande,float *V_consigne,float *VO_mesuree);
/**
 * @fn float regulateur_final(float *commande,float *V_consigne,float *V_mesuree)
 * @brief Calcul de la commande
 * @param Tableau de commande
 * @param Tableau de V_consigne
 * @param Tableau de V_mesuree
  */
float regulateur_final(float *commande,float *V_consigne,float *VO_mesuree);

/**
 * @fn float regulateur(float *commande,float *V_consigne,
 * float *V_mesuree, float *Rn, float* Rd, float* Rp)
 * @brief Calcul de la commande
 * @param Tableau de commande
 * @param Tableau de V_consigne
 * @param Tableau de V_mesuree
 * @param idem
 * @param idem
 */
    float regulateur(float *commande,float *V_consigne,
        float *V_mesuree, float *Rn, float* Rd, float* Rp);

/**
 * @fn float transfert(float * V_mesuree, float *commande,int consigne)
 * @brief Emulation du système Boost Converter
 * @param Tableau de V_mesuree
 * @param Tableau de commande
 * @param Tableau de consigne
 */
float transfert(float * V_mesuree, float *commande,int consigne);
/**
 * @fn float transfert(float * V_mesuree, float *commande)
 * @brief Emulation du système Boost Converter
 * @param Tableau de V_mesuree
 * @param Tableau de commande
 * @param Tableau de consigne
 */
float transfert2(float * V_mesuree, float *commande);

/**
 * @fn void regulateurs_init(float *Rn_18V,float *Rd_18V,float *Rp_18V,float *Rn_24V,
        float *Rd_24V,float *Rp_24V,float *Rn_30V,float *Rd_30V,float *Rp_30V)
 * @brief Initialisation des gains du rédulateur
 * @param Gain du régulateur au point de fonctionnement 18V
 * @param Gain du régulateur au point de fonctionnement 24V
 * @param Gain du régulateur au point de fonctionnement 30V
 */
void regulateurs_init(float *Rn_18V,float *Rd_18V,float *Rp_18V,float *Rn_24V,
        float *Rd_24V,float *Rp_24V,float *Rn_30V,float *Rd_30V,float *Rp_30V,
        float *Rn_36V,float *Rd_36V,float *Rp_36V);

#endif	/* REGULATEUR_H */

