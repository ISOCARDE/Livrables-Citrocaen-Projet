/*
 * File:   main.c
 * Author: Vincent
 *
 * Created on 28 octobre 2013, 18:33
 */

/*** INCLUDES *****************************************************************/

    #include "main_identification.h"

/*** VAR GLOBAL *****************************************************************/

    #define TAILLE_TABLEAU  64
    #define TAILLE_MESURE   TAILLE_TABLEAU
    #define TAILLE_COMMANDE TAILLE_TABLEAU


/***  GLOBAL VARIABLE *********************************************************/

/*** GLOBALS ******************************************************************/

    // Valeurs




/*** INTERRUPTS ***************************************************************/




/**
* @fn void main (void)
* @brief point d'entrée du programme
*/
int main(void){

    /*Optimisation du fonctionnement du CPU*/
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    /*Desactivation du JTAG pour liberer des broches*/
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);

    /*Initialisation des perihperiques*/
    UART_Init();
    timerInit();
    pwmInit();

    SpiChannel channel;
    unsigned int sriClk = 2500000;  // debit voulu : 3Mb/s
    unsigned int sroClk = 80000000; // Frequence de travail du peripheriqe : 40MHz
    channel = ad7885Pic32Open(SPI_CHANNEL4,sroClk/sriClk);

    /*Configuration du Timer*/
    timerIntConfig();

    // Activation des interruptions
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();


    /****** partie identification*/
    float rapportCyclique;
    rapportCyclique =0;
    float acqui[100] ={0};
    int increm = 0;
    int compt = 0;

    /*Definition des broches pour les 3 ADCs*/
    SlaveS SS1,SS2,SS3;

    /*ChipSelec VIL*/
    SS1.Port = IOPORT_A;
    SS1.Bit = BIT_3;

    /*ChipSelect Vo*/
    SS2.Port = IOPORT_B;
    SS2.Bit = BIT_14;

    /*ChipSelect de Vi*/
    SS3.Port = IOPORT_B;
    SS3.Bit = BIT_9;

    /*creation des tableaux des gains pour les regulateurs*/
    float Rn_18V[3];
    float Rd_18V[5];
    float Rp_18V[7];

    float Rn_24V[3];
    float Rd_24V[5];
    float Rp_24V[7];

    float Rn_30V[3];
    float Rd_30V[5];
    float Rp_30V[7];

    /*initialisation des gains des regulateurs */
    regulateurs_init(Rn_18V,Rd_18V,Rp_18V,Rn_24V,Rd_24V,Rp_24V,Rn_30V,Rd_30V,Rp_30V);


    /*les tableaux V_consigne et V_mesuree doivent etre rafraichis depuis les
     acquisition des ADC*/
    float V_consigne[7] = {24,24,24,24,24,24,24};
    float V_mesuree[3] = {0,0,0};
    float commande[5]={1,1,1,1,1};
    float nouvelle_Commande=0;
    float nouveau_y=0;


    /* Pointeurs*/
    unsigned int pMesure = 0;
    unsigned int pEchantillon = 0;
    float pData;
    int mesure [TAILLE_TABLEAU]={0};
    char pDataC[10000];
    char pEchantillonC[MAX_STRING];

    /*Variables de flag pour les interruptions ADC,SPI,PWM,UART*/
    flagReception=0;
    flagPwm = 0;
    flagTraitement = 0;

    putUartStr("====== ADC ====== ");

    while(1){

        if(flagTraitement){
            flagTraitement = 0;

            // Acquisition
            if (channel != -1) {
                // Read ADC VIL
                // ad7885Pic32Read(channel, &pData,SS1);

                // Read ADC VO
                ad7885Pic32Read(channel, &pData,SS2);
                V_mesuree[2]=V_mesuree[1];
                V_mesuree[1]=V_mesuree[0];

                V_mesuree[0] = pData;

                /* partie identification*/
                if(increm == 7)
                    rapportCyclique = 0.6; //valeur a changer pour la taille de l'echelon
                
                if(increm<100){
                    acqui[increm]=pData;
                    increm ++;
                }
                if(increm == 200){
                   rapportCyclique =0;
                    Nop();
                }

                Nop();
                // Read ADC VI
                //ad7885Pic32Read(channel, &pData,SS3);
            }

            Nop();

            pMesure++;
            pEchantillon ++;

            if (pMesure >= TAILLE_MESURE)
                pMesure = 0;

            /*rafraichissement du tableau V_mesuree*/

            /*fonction test qui simule le systeme. Ne sera pas presente lors de
             l'integration finale*/
            int consigne = 0;
            if(V_consigne[0] <= 22 )
                consigne=18;
            else if(V_consigne[0] > 22 && V_consigne[0] < 28)
                consigne=24;
            else
                consigne=30;

            //nouveau_y = transfert(V_mesuree,commande,consigne);

            /*rafraichissement du tableau commande*/
            commande[4]=commande[3];
            commande[3]=commande[2];
            commande[2]=commande[1];
            commande[1]=commande[0];

            /*Calcul de la nouvelle commande */
            if(V_consigne[0]==18){
                nouvelle_Commande  = regulateur(commande,V_consigne,V_mesuree,
                        Rn_18V,Rd_18V,Rp_18V);
            }
            else if(V_consigne[0]==24){
                nouvelle_Commande  = regulateur(commande,V_consigne,V_mesuree,
                        Rn_24V,Rd_24V,Rp_24V);
            }
            else
                nouvelle_Commande  = regulateur(commande,V_consigne,V_mesuree,
                        Rn_30V,Rd_30V,Rp_30V);


            /*Changement du rapport cyclique du PWM*/
            if (flagPwm){
                flagPwm = 0;
                pwmSet( (rapportCyclique) * T3_TICK);
            }

             /*   pCommande++;

                if (pCommande >= TAILLE_COMMANDE)
                    pCommande = 0;
            }*/
        }

        /* Attente interruption de l'UART*/
        if (flagReception){

            /*remise du flag a 0 */
            flagReception=0;

            // permet de revenir à la ligne
            putUartStr("");
            putUartStr("Echantillon");
            sprintf(pEchantillonC,"%d",pEchantillon);
            putUartStr( pEchantillonC);

            putUartStr("Vil = ");


            putUartStr("Vo = ");
            sprintf(pDataC,"%d",pData);
            putUartStr( pDataC);

            putUartStr("Vi = ");
        }
   }

    /*fermeture du channel SPI */
    ad7885Pic32Close(channel);
}

