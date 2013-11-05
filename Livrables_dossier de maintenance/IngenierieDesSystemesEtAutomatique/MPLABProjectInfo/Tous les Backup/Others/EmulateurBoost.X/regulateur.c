
/*
 * File:   pwm.c
 * Author: Vincent
 *
 * Created on 25 octobre 2013, 19:33
 */

/*** INCLUDES *****************************************************************/
#include "includes.h"


/*** FUNCTIONS ****************************************************************/
float regulateur(float *commande,float *V_consigne, float *V_mesuree, float *Rn, float* Rd, float* Rp){

    /* calcul */
    commande[0]=-Rd[1]*commande[1]-Rd[2]*commande[2]-Rd[3]*commande[3]
            -Rd[4]*commande[4]
            -Rn[0]*V_mesuree[0]-Rn[1]*V_mesuree[1]
            -Rn[2]*V_mesuree[2]
            +Rp[0]*V_consigne[0]+Rp[1]*V_consigne[1]+Rp[2]*V_consigne[2]
            +Rp[3]*V_consigne[3]+Rp[4]*V_consigne[4]+Rp[5]*V_consigne[5]
            +Rp[6]*V_consigne[6];

    /*saturation de la commande*/
    if(commande[0]>0.8)
        commande[0]=0.8;
    else if(commande[0]<0.2)
        commande[0]=0.2;

    return commande[0];
}
/******************************************************************************/
float transfert(float * V_mesuree, float *commande,int consigne){
    float num[2];
    float den[3];

    if(consigne==18){
        num[0] = 3.79;
        num[1] = 4.227;

        den[0] = 1;
        den[1] =-1.638;
        den[2] =0.935;
    }
    else if(consigne == 24){
        num[0] = 3.621;
        num[1] = 4.489;

        den[0] = 1;
        den[1] =-1.766;
        den[2] =0.935;
    }
    else if(consigne==30){
        num[0] = 3.365;
        num[1] = 4.788;

        den[0] = 1;
        den[1] =-1.826;
        den[2] =0.935;
    }
    else{
        num[0] = 3.038;
        num[1] = 5.139;

        den[0] = 1;
        den[1] =-1.859;
        den[2] =0.935;
    }


    V_mesuree[0] = -den[1]*V_mesuree[1]-den[2]*V_mesuree[2]+num[0]*commande[1]
            +num[1]*commande[2];

    return V_mesuree[0];
}


void regulateurs_init(float *Rn_18V,float *Rd_18V,float *Rp_18V,float *Rn_24V,
        float *Rd_24V,float *Rp_24V,float *Rn_30V,float *Rd_30V,float *Rp_30V,
        float *Rn_36V,float *Rd_36V,float *Rp_36V){

    /* gain du regulateur 18V , periode échantillonnage Te = 0.0001s */
    Rn_18V[0] =0.0293102602505404;
    Rn_18V[1] =-0.0878509101772626;
    Rn_18V[2] =0.0591720473088610;

    Rd_18V[0] =1.00000000000000;
    Rd_18V[1] =-0.824013588416498;
    Rd_18V[2] =-0.167463757771437;
    Rd_18V[3] =-0.00881639004247820;
    Rd_18V[4] =0.000293736230412986;

    Rp_18V[0] =0.124732432687515;
    Rp_18V[1] =-0.293247941102856;
    Rp_18V[2] =0.238023909270153;
    Rp_18V[3] =-0.0813255145521023;
    Rp_18V[4] =0.0135025185026603;
    Rp_18V[5] =-0.00108826563115985;
    Rp_18V[6] =0.0000342582079289359;
    
    /* gain du regulateur 24V , periode échantillonnage Te = 0.0001s */
    Rn_24V[0] =0.0533033217800201;
    Rn_24V[1] =-0.117758097920058;
    Rn_24V[2] =0.0650789299754368;

    Rd_24V[0] =1.00000000000000;
    Rd_24V[1] =-0.777974596450532;
    Rd_24V[2] =-0.213542950626117;
    Rd_24V[3] =-0.00877618915376453;
    Rd_24V[4] =0.000293736230413011;

    Rp_24V[0] =0.123301471407425;
    Rp_24V[1] =-0.289883728282318;
    Rp_24V[2] =0.235293240184636;
    Rp_24V[3] =-0.0803925281595497;
    Rp_24V[4] =0.0133476142749090;
    Rp_24V[5] =-0.00107578077900801;
    Rp_24V[6] =0.0000338651893048673;


    /* gain du regulateur 30V , periode échantillonnage Te = 0.0001s */
    Rn_30V[0] =0.0647470068325469;
    Rn_30V[1] =-0.131946332754611;
    Rn_30V[2] =0.0678201608248662;

    Rd_30V[0] =1.00000000000000;
    Rd_30V[1] =-0.742597280109346;
    Rd_30V[2] =-0.248939193697005;
    Rd_30V[3] =-0.00875726242406208;
    Rd_30V[4] =0.000293736230412980;

    Rp_30V[0] =0.122645816904418;
    Rp_30V[1] =-0.288342274075589;
    Rp_30V[2] =0.234042070424102;
    Rp_30V[3] =-0.0799650415894844;
    Rp_30V[4] =0.0132766384519617;
    Rp_30V[5] =-0.00107006032406166;
    Rp_30V[6] =0.0000336851114549480;

    /* gain du regulateur 36V , periode échantillonnage Te = 0.0001s */
    Rn_36V[0] =0.0711863465931265;
    Rn_36V[1] =-0.140005846660832;
    Rn_36V[2] =0.0694385409731614;

    Rd_36V[0] =1.00000000000000;
    Rd_36V[1] =-0.707947446550479;
    Rd_36V[2] =-0.283599393849080;
    Rd_36V[3] =-0.00874689583085401;
    Rd_36V[4] =0.000293736230413014;

    Rp_36V[0] =0.122291413070159;
    Rp_36V[1] =-0.287509065001767;
    Rp_36V[2] =0.233365770088472;
    Rp_36V[3] =-0.0797339703792203;
    Rp_36V[4] =0.0132382735758314;
    Rp_36V[5] =-0.00106696822119744;
    Rp_36V[6] =0.0000335877731766572e-05;

}