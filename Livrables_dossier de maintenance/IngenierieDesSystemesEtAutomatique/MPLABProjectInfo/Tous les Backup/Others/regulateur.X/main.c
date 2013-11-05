/*
 * File:   regulateur.c
 * Author: Nicolas
 *
 * Created on 28 octobre 2013, 10:08
 */

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>

#pragma config FWDTEN=OFF, CP=OFF, POSCMOD=HS, FNOSC=PRIPLL
#pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPLLODIV=DIV_1, FPBDIV=DIV_2

#define SYS_FREQ                (80000000L)
#define PB_DIV                  253099
#define PRESCALE                4
#define TOGGLES_PER_SEC         1
#define T2_TICK                 (SYS_FREQ/PB_DIV/PRESCALE/TOGGLES_PER_SEC)


float regulateur(float *commande,float *V_consigne, float *V_mesuree, float *Rn, float* Rd, float* Rp){


    Nop();
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

    Nop();
    
    return commande[0];
}

float transfert(float * V_mesuree, float *commande){
    /* fonctio de transfert pour 24V*/
//    float num[2] = {3.621,4.489};
//    float den[3] = {1,-1.766,0.935};
   /* fonctio de transfert pour 32V*/
//    float num[2] = {3.264,4.899};
//    float den[3] = {1,-1.839,0.935};
   /* fonctio de transfert pour 18V*/
    float num[2] = {3.79,4.227};
    float den[3] = {1,-1.638,0.935};

    V_mesuree[0] = -den[1]*V_mesuree[1]-den[2]*V_mesuree[2]+num[0]*commande[1]
            +num[1]*commande[2];

    return V_mesuree[0];
}

/*
 *
 */
int main(int argc, char** argv) {

    int j;
    /* les tableaux V_consigne et V_mesuree devront être rafraichis avant d'être
     utilisés la fonction regulateur*/
    float V_consigne[7] = {18,18,18,18,18,18,18};
    float V_mesuree[3] = {0,0,0};
    float commande[5]={1,1,1,1,1};
    float nouvelle_Commande=0;
    float nouveau_y=0;

        /* gain du regulateur 24V , periode échantillonnage Te = 0.0001s */
//    float Rn[3] = {0.0533033217800201,-0.117758097920058,0.0650789299754368};
//    float Rd[5] = {1.00000000000000,-0.777974596450532,-0.213542950626117,
//    -0.00877618915376453,0.000293736230413011};
//    float Rp[7] = {0.123301471407425,-0.289883728282318,0.235293240184636,
//    -0.0803925281595497,0.0133476142749090,-0.00107578077900801,
//    0.0000338651893048673};
        /* gain du regulateur 32V , periode échantillonnage Te = 0.0001s */
//    float Rn[3] = {0.0672684340936131,-0.135087924079938,0.0684396131702535};
//    float Rd[5] = {1.00000000000000,-0.731193710270820,-0.260346864675888,
//    -0.00875316128370576,0.000293736230412980};
//    float Rp[7] = {0.122505216976433,-0.288011721399654,0.233773766954179,
//    -0.0798733704720135,0.0132614182474954,-0.00106883361769450,
//    0.0000336464951827892};
        /* gain du regulateur 18V , periode échantillonnage Te = 0.0001s */
    float Rn[3] = {0.0293102602505404,-0.0878509101772626,0.0591720473088610};
    float Rd[5] = {1,-0.824013588416498,-0.167463757771437,
    -0.00881639004247820,0.000293736230412986};
    float Rp[7] = {0.124732432687515,-0.293247941102856,0.238023909270153,
    -0.0813255145521023,0.0135025185026603,-0.00108826563115985,
    0.0000342582079289359};

    for(j=0;j<9000;j++){

        /*rafraichissement du tableau V_mesuree*/
        V_mesuree[2]=V_mesuree[1];
        V_mesuree[1]=V_mesuree[0];

        nouveau_y = transfert(V_mesuree,commande);

        Nop();
        /*rafraichissement du tableau commande*/
        commande[4]=commande[3];
        commande[3]=commande[2];
        commande[2]=commande[1];
        commande[1]=commande[0];

        Nop();
        nouvelle_Commande = regulateur(commande,V_consigne,V_mesuree,Rn,Rd,Rp);
        Nop();
        
    }
    while(1);
     return (EXIT_SUCCESS);
}

