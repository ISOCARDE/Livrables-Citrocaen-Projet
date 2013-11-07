/*******************************************************************************
* @file main.c
* @brief gestion CAN cote boost
* @author Alain WERCK
* @date 3/11 qui marche
*******************************************************************************/

/*** INCLUDES *****************************************************************/
    #include "includes.h"

/*** CONFIG *******************************************************************/

// POSCMOD = XT (externe 3,5MHz-10MHz) ou HS (externe 10MHz-40MHz)
// PLL si FNOSC = PRIPLL
// CPUfreq = 8MHz   (ext. christal explorer 16) / FPLIDIV .
//                  doit �tre compris entre 4MHz < ? < 5MHz (datasheet)
// CPUfreq = ( (8MHz (ext. explorer 16) / FPLLIDIV) x FPLLMUL ) / FPLLODIV
// FPBDIV = DIV_2 pr�-config de la freq du bus periph. MAJ en soft dans le code
    #pragma config FWDTEN=OFF, CP=OFF, POSCMOD=XT, FNOSC=PRIPLL
    #pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPLLODIV=DIV_1, FPBDIV=DIV_2
    #pragma config FCANIO = OFF     // enable the CAN BUS


/*** PROTOTYPES ***************************************************************/

/**
* @fn void initBoard(void)
* @brief initialisation des diff�rents p�riph�riques de la board
*/
void initBoard(){    

    //Optimisation du fonctionnement du CPU
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    // D�sactivation du JTAG pour lib�rer des broches
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);
    
    /*** Initialisation de tout les modules */
    initGPIO();
    CANxInit(CAN_FILTRE_INVIT);
    initTimer4();
    UART_Init();


}

/**
* @fn int puissance10(char puissance)
* @brief calcul de puissance de 10 avec la puissance passee en argument
*/
int puissance10(char puissance){

    int valeur = 1;
    char i;
    for(i=0; i<puissance; i++) valeur = valeur*10;

    return valeur;
}

/**
* @fn int main(void)
* @brief point d'entr�e du programme
*/
int main(void)
{
    /**************************************************************************/
    short i,j;
    /*** Initialise la board (p�riph & interrupt) */
    initBoard();

    pwmInit();
    SpiChannel channel;
    unsigned int sriClk = 2500000;  // debit voulu : 3Mb/s
    unsigned int sroClk = 80000000; // Frequence de travail du peripheriqe : 40MHz
    channel = ad7885Pic32Open(SPI_CHANNEL4,sroClk/sriClk);

    /*Configuration du Timer*/
    //timerIntConfig();

    /* Configure system for maximum performance and enable multi vector interrupts. */
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();

    /*** Initialisation des types VOLATILES */
    filtreBoost = 0;
    consigneBoost = 0;
    alea = 0;
    timerDecoBoost = 0;
    etat = 0;   
    for(i=0; i<5; i++) valASCII[i]=0;

    LED1 = LED_ON;

    BOOL raz = is100MSecondUp();
    raz = isDemiSecondUp();
    i = 0;
    putUartStr("\r\n");


    /*Definition des broches pour les 3 ADCs*/
    SlaveS SS1;
    SlaveS SS2;
    SlaveS SS3;

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

    float Rn_36V[3];
    float Rd_36V[5];
    float Rp_36V[7];

    /*initialisation des gains des regulateurs */
    regulateurs_init(Rn_18V,Rd_18V,Rp_18V,Rn_24V,Rd_24V,Rp_24V,Rn_30V,Rd_30V,
            Rp_30V,Rn_36V,Rd_36V,Rp_36V);


    /*les tableaux V_consigne et V_mesuree doivent etre rafraichis depuis les
     acquisition des ADC*/
    float V_consigne[7] = {24,24,24,24,24,24,24};
    float VO_mesuree[3] = {0,0,0};
    float Vil_mesuree[3] = {0,0,0};
    float Vi_mesuree[3] = {0,0,0};
    float commande[5]={1,1,1,1,1};
    float nouvelle_Commande=0;
    float nouveau_y=0;

    /* Pointeurs*/
    unsigned int pMesure = 0;
    unsigned int pEchantillon = 0;
    pDataVO = 0;
    pDataVI = 0;
    pDataVIL = 0;

    /*Variables de flag pour les interruptions ADC,SPI,PWM,UART*/
    flagPwm = 0;
    flagTraitement = 0;
    consigneDuCan = 24;

    voBoostToCan = 0;
    viBoostToCan = (BYTE)(11.9/(10*0.0195));
    vilBoostToCan = (BYTE)(12.12/(10*0.0195));

    while(1)
    {

        // LED2
        if(demiSecondUpForLed == TRUE){
            isBoostConnected();
            demiSecondUpForLed = FALSE;
        }

        /*** CAN2RxMsgProcess will check if CAN2 has received a message */
        CANxRxMsgProcess();
        //Nop();
        // check des timer
        checkTimer();

        flagTraitement = 1;
        if(flagTraitement){
            V_consigne[6] = consigneDuCan;
            V_consigne[5] = consigneDuCan;
            V_consigne[4] = consigneDuCan;
            V_consigne[3] = consigneDuCan;
            V_consigne[2] = consigneDuCan;
            V_consigne[1] = consigneDuCan;
            V_consigne[0] = consigneDuCan;
            

            flagTraitement = 0;

            // Acquisition
//            if (channel != -1) {
//                // Read ADC VIL
//                ad7885Pic32Read(channel, &pDataVO,SS1);
//                Vil_mesuree[2] = Vil_mesuree[1];
//                Vil_mesuree[1] = Vil_mesuree[0];
//                Vil_mesuree[0] = pDataVIL;
//
//                // Read ADC VO
                ad7885Pic32Read(channel, &pDataVO,SS2);
//                VO_mesuree[2] = VO_mesuree[1];
//                VO_mesuree[1] = VO_mesuree[0];
//                VO_mesuree[0] = pDataVO;;

                // Read ADC VI
//                ad7885Pic32Read(channel, &pDataVI,SS3);
//                Vi_mesuree[2] = Vi_mesuree[1];
//                Vi_mesuree[1] = Vi_mesuree[0];
//                Vi_mesuree[0] = pDataVI;
//            }

            Nop();

            pMesure++;
            pEchantillon ++;


            /*rafraichissement du tableau V_mesuree*/

            /*fonction test qui simule le systeme. Ne sera pas presente lors de
             l'integration finale*/
            int consigne = 0;
            if(V_consigne[0] <= 22 )
                consigne=18;
            else if(V_consigne[0] > 22 && V_consigne[0] <= 28)
                consigne=24;
            else if(V_consigne[0]> 28 && V_consigne[0]<=32)
                consigne=30;
            else
                consigne=36;

            /* partie emulation, a enlever si Boost Converter Branche*/
            VO_mesuree[2] = VO_mesuree[1];
            VO_mesuree[1] = VO_mesuree[0];
            nouveau_y = transfert(VO_mesuree,commande,consigne);
            voBoostToCan = (BYTE)((VO_mesuree[0])/(100*0.0195));
            
            /*rafraichissement du tableau commande*/
            commande[4]=commande[3];
            commande[3]=commande[2];
            commande[2]=commande[1];
            commande[1]=commande[0];

            /*Calcul de la nouvelle commande */
            if(V_consigne[0]==18){
                nouvelle_Commande  = regulateur(commande,V_consigne,VO_mesuree,
                        Rn_18V,Rd_18V,Rp_18V);
            }
            else if(V_consigne[0]==24){
                nouvelle_Commande  = regulateur(commande,V_consigne,VO_mesuree,
                        Rn_24V,Rd_24V,Rp_24V);
            }
            else if(V_consigne[0]==30){
                nouvelle_Commande  = regulateur(commande,V_consigne,VO_mesuree,
                        Rn_30V,Rd_30V,Rp_30V);
            }
            else{
                nouvelle_Commande  = regulateur(commande,V_consigne,VO_mesuree,
                        Rn_36V,Rd_36V,Rp_36V);

            }

            /*Changement du rapport cyclique du PWM*/
            if (flagPwm){
                flagPwm = 0;
                pwmSet( (1-nouvelle_Commande) * T3_TICK);
            }

             /*   pCommande++;

                if (pCommande >= TAILLE_COMMANDE)
                    pCommande = 0;
            }*/
       }
    }
}

