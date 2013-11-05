/**
* @file regulateur.c
* @brief Configuration des differents perepheriques
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author DEPARIS Nicolas / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

/* INCLUDES DEPENDENCIES ***************/
#include "main.h"


/**
 * @fn float regulateur_PI(float *commande,float *V_consigne,float *V_mesuree)
 * @brief Calcul de la commande
 * @param Tableau de commande
 * @param Tableau de V_consigne
 * @param Tableau de V_mesuree
  */
float regulateur_PI(float *commande,float *V_consigne,float *VO_mesuree){

    /*Te = 0.0003*/
    float den[4] ={0.00430135267617162,0.00430135267617162};
    float num[4] ={1,-1};

    commande[0] = -den[1]*commande[1]
            +num[0]*(V_consigne[0]-VO_mesuree[0])
            +num[1]*(V_consigne[1]-VO_mesuree[1]);

    /*saturation de la commande*/
    if(commande[0]>1)
        commande[0]=1;
    else if(commande[0]<0.3)
        commande[0]=0.33;

    return commande[0];
}
/**
 * @fn float regulateur_trois(float *commande,float *V_consigne,float *V_mesuree)
 * @brief Calcul de la commande
 * @param Tableau de commande
 * @param Tableau de V_consigne
 * @param Tableau de V_mesuree
  */
float regulateur_trois(float *commande,float *V_consigne,float *VO_mesuree){

    /*Te = 0.0004*/
    float num[2] ={0.413049787463201,-0.413049787463201*0.955827782192953} ;
    float den[2] ={1,-1};

    commande[0] = -den[1]*commande[1]
            +num[0]*(V_consigne[0]-VO_mesuree[0])
            +num[1]*(V_consigne[1]-VO_mesuree[1]);

    /*saturation de la commande*/
    if(commande[0]>1)
        commande[0]=1;
    else if(commande[0]<0.2)
        commande[0]=0.2;

    return commande[0];
}
/**
 * @fn float regulateur_final(float *commande,float *V_consigne,float *V_mesuree)
 * @brief Calcul de la commande
 * @param Tableau de commande
 * @param Tableau de V_consigne
 * @param Tableau de V_mesuree
  */
float regulateur_final(float *commande,float *V_consigne,float *VO_mesuree){

    /*Te = 0.0004*/
    float num[4] ={0.014891221699278,-0.0009062757424814134,
    0.00001801787012351308,0} ;
    float den[4] ={1,-1.031465352147425,0.031465352147425,0};

    commande[0] = -den[1]*commande[1]-den[2]*commande[2]-den[3]*commande[3]
            +num[0]*(V_consigne[0]-VO_mesuree[0])
            +num[1]*(V_consigne[1]-VO_mesuree[1])
            +num[2]*(V_consigne[2]-VO_mesuree[2])
            +num[3]*(V_consigne[3]-VO_mesuree[3]);
 
    /*saturation de la commande*/
    if(commande[0]>1)
        commande[0]=1;
    else if(commande[0]<0.3)
        commande[0]=0.33;

    return commande[0];
}
/**
 * @fn float regulateur(float *commande,float *V_consigne,
 * float *V_mesuree, float *Rn, float* Rd, float* Rp)
 * @brief Calcul de la commande
 */
float regulateur(float *commande,float *V_consigne,
        float *V_mesuree, float *Rn, float* Rd, float* Rp){

    /* calcul */
    commande[0]=-Rd[1]*commande[1]-Rd[2]*commande[2]-Rd[3]*commande[3]
            -Rd[4]*commande[4]
            -Rn[0]*V_mesuree[0]-Rn[1]*V_mesuree[1]
            -Rn[2]*V_mesuree[2]
            +Rp[0]*V_consigne[0]+Rp[1]*V_consigne[1]+Rp[2]*V_consigne[2]
            +Rp[3]*V_consigne[3]+Rp[4]*V_consigne[4]+Rp[5]*V_consigne[5]
            +Rp[6]*V_consigne[6];

    /*saturation de la commande*/
    if(commande[0]>0.7)
        commande[0]=0.7;
    else if(commande[0]<0.2)
        commande[0]=0.2;

    return commande[0];
}

/**
 * @fn float transfert(float * V_mesuree, float *commande,int consigne)
 * @brief Emulation du système Boost Converter
 */
float transfert(float * V_mesuree, float *commande,int consigne){
    float num[2];
    float den[3];

    if(consigne==18){
        num[0] = 32.12;
        num[1] = 7.332;

        den[0] = 1;
        den[1] =0.328;
        den[2] =0.1333;
    }
    else if(consigne == 24){
        num[0] = 30.43;
        num[1] = - 11.07;

        den[0] = 1;
        den[1] = - 0.73;
        den[2] = 0.1333;
    }
    else if(consigne==30){
        num[0] = 99.25;
        num[1] = 29.98;

        den[0] = 1;
        den[1] =0.5897;
        den[2] =0.1333;
    }
    else{
        num[0] = 121.7;
        num[1] = 39.01;

        den[0] = 1;
        den[1] = 0.3546;
        den[2] = 0.1333;
    }


    V_mesuree[0] = -den[1]*V_mesuree[1]-den[2]*V_mesuree[2]+num[0]*commande[1]
            +num[1]*commande[2];

    return V_mesuree[0];
}

/**
 * @fn float transfert2(float * V_mesuree, float *commande,int consigne)
 * @brief Emulation du système Boost Converter
 */
float transfert2(float * V_mesuree, float *commande){
    float num[1]={2.366};
    float den[3]={1,-0.7954,-0.188};

    V_mesuree[0] = -den[1]*V_mesuree[1]-den[2]*V_mesuree[2]+num[0]*commande[1];

    return V_mesuree[0];
}

/**
 * @fn void regulateurs_init(float *Rn_18V,float *Rd_18V,float *Rp_18V,float *Rn_24V,
        float *Rd_24V,float *Rp_24V,float *Rn_30V,float *Rd_30V,float *Rp_30V)
 * @brief Initialisation des gains du rédulateur
 */
void regulateurs_init(float *Rn_18V,float *Rd_18V,float *Rp_18V,float *Rn_24V,
        float *Rd_24V,float *Rp_24V,float *Rn_30V,float *Rd_30V,float *Rp_30V,
        float *Rn_36V,float *Rd_36V,float *Rp_36V){

    /* gain du regulateur 18V , periode échantillonnage Te = 0.0003s */
    Rn_18V[0] =0.0116370085299339;
    Rn_18V[1] =0.00763676837247052;
    Rn_18V[2] =0.00361027089422409;

    Rd_18V[0] =1.00000000000000;
    Rd_18V[1] =-0.801411847229262;
    Rd_18V[2] =-0.198588152770738;
    Rd_18V[3] =0;
    Rd_18V[4] =0;

    Rp_18V[0] =0.0253449228249353;
    Rp_18V[1] =-0.00252369881092658;
    Rp_18V[2] =0.0000628237826197493;
    Rp_18V[3] =0;
    Rp_18V[4] =0;
    Rp_18V[5] =0;
    Rp_18V[6] =0;

    /* gain du regulateur 24V , periode échantillonnage Te = 0.0003s */
    Rn_24V[0] =0.00763441307050389;
    Rn_24V[1] =0.00477915327633832;
    Rn_24V[2] =0.00138703033656370;

    Rd_24V[0] =1.00000000000000;
    Rd_24V[1] =-0.800698913194399;
    Rd_24V[2] =-0.199301086805601;
    Rd_24V[3] =0;
    Rd_24V[4] =0;

    Rp_24V[0] =0.0146734136588590;
    Rp_24V[1] =-0.000886197396741699;
    Rp_24V[2] =0.0000133804212886348;
    Rp_24V[3] =0;
    Rp_24V[4] =0;
    Rp_24V[5] =0;
    Rp_24V[6] =0;

    /* gain du regulateur 30V , periode échantillonnage Te = 0.0003s */
    Rn_30V[0] =0.00197095894878839;
    Rn_30V[1] =0.00450430886281578;
    Rn_30V[2] =0.000511682314872090;

    Rd_30V[0] =1.00000000000000;
    Rd_30V[1] =-0.884912717619135;
    Rd_30V[2] =-0.115087282380865;
    Rd_30V[3] =0;
    Rd_30V[4] =0;

    Rp_30V[0] =0.00773830370006930;
    Rp_30V[1] =-0.000770534910733290;
    Rp_30V[2] =0.0000191813371402521;
    Rp_30V[3] =0;
    Rp_30V[4] =0;
    Rp_30V[5] =0;
    Rp_30V[6] =0;

    /* gain du regulateur 36V , periode échantillonnage Te = 0.0003s */
    Rn_36V[0] =0.00256794545956769;
    Rn_36V[1] =0.00225352229087562;
    Rn_36V[2] =0.000797392667936648;

    Rd_36V[0] =1.00000000000000;
    Rd_36V[1] =-0,766622704657907;
    Rd_36V[2] =-0,233377295342093;
    Rd_36V[3] =0;
    Rd_36V[4] =0;

    Rp_36V[0] =0.00622309413673331;
    Rp_36V[1] =-0.000619659226490389;
    Rp_36V[2] =0.0000154255081370274;
    Rp_36V[3] =0;
    Rp_36V[4] =0;
    Rp_36V[5] =0;
    Rp_36V[6] =0;
}