/* 
 * File:   regulateur.h
 * Author: Vincent
 *
 * Created on 30 octobre 2013, 11:10
 */

#ifndef REGULATEUR_H
#define	REGULATEUR_H



/*** PROTOTYPES ***************************************************************/
float regulateur(float *commande,float *V_consigne, float *V_mesuree, float *Rn, float* Rd, float* Rp);


float transfert(float * V_mesuree, float *commande, int consigne);


#endif	/* REGULATEUR_H */

