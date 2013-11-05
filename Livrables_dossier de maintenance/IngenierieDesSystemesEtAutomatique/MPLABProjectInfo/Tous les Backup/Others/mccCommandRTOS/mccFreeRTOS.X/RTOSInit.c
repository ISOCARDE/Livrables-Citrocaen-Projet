/**
* @file RTOSInit.c
* @brief Initialisations RTOS - Real Time Operating System
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author GOURDEL Vincent / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

/*** INCLUDES *****************************************************************/
#include "main.h"


/**
 * @fn void RTOSInit(void)
 * @brief Cette fonction initialise notre noyau avant de le lancer (créations
 * tâches, créations files d'attente,créations sémaphores ...)
 */
void RTOSInit(void){
    /*** TASKS CREATIONS ***/
    xTaskCreate( TacheRegulation, "TacheRegulation", configMINIMAL_STACK_SIZE, NULL, 2,NULL );
    xTaskCreate( TacheRegulation_bis, "TacheRegulation_bis", configMINIMAL_STACK_SIZE, NULL, 1,NULL );
    //xTaskCreate( TacheUART, "TacheUART", configMINIMAL_STACK_SIZE, NULL, 1,NULL );
    //xTaskCreate( TacheCAN, "TacheCAN", configMINIMAL_STACK_SIZE, NULL, 1,NULL );
    
}

/*******************************************************************
 * Task:        	void Tache1( void *pvParameters )
 *
 * Input:               void *pvParameters -> pointeur sur un paramètre passé à la tâche
 *
 * Overview:            envoi d'une chaine de caractere au PC en forcant le mode critique puis temporisation
 *******************************************************************/
void TacheRegulation( void *pvParameters ){

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
    regulateurs_init(Rn_18V,Rd_18V,Rp_18V,Rn_24V,Rd_24V,Rp_24V,Rn_30V,
            Rd_30V,Rp_30V,Rn_36V,Rd_36V,Rp_36V);

    portTickType xLastWakeTime;
    const portTickType xFrequency = 3;  //appel de la fonction toutes les 300us

    /*** Initialise the xLastWakeTime variable with the current time. */
    xLastWakeTime = xTaskGetTickCount();
    
    /*** Faire toujours ... ***/
    for(;;){
        Nop();
            taskENTER_CRITICAL();
            if(algo==1){
                V_consigne[0]= ref;
                V_consigne[6]=V_consigne[0];
                V_consigne[5]=V_consigne[0];
                V_consigne[4]=V_consigne[0];
                V_consigne[3]=V_consigne[0];
                V_consigne[2]=V_consigne[0];
                V_consigne[1]=V_consigne[0];
            }
            Nop();
            
            // Acquisition
//            if (channel != -1) {
//                // Read ADC VIL
//                ad7885Pic32Read(channel, &pDataVIL,SS1);
//                VIL_mesuree[6] = VIL_mesuree[5];
//                VIL_mesuree[5] = VIL_mesuree[4];
//                VIL_mesuree[4] = VIL_mesuree[3];
//                VIL_mesuree[3] = VIL_mesuree[2];
//                VIL_mesuree[2] = VIL_mesuree[1];
//                VIL_mesuree[1] = VIL_mesuree[0];
//                VIL_mesuree[0] = pDataVIL;
//                Vil = pDataVIL;
//                Nop();
//
//                // Read ADC VO
//                ad7885Pic32Read(channel, &pDataVO,SS2);
//                VO_mesuree[6] = VO_mesuree[5];
//                VO_mesuree[5] = VO_mesuree[4];
//                VO_mesuree[4] = VO_mesuree[3];
//                VO_mesuree[3] = VO_mesuree[2];
//                VO_mesuree[2] = VO_mesuree[1];
//                VO_mesuree[1] = VO_mesuree[0];
//                VO_mesuree[0] = pDataVO;
//                Vo = pDataVO;
//                Nop();
//
//                // Read ADC VI
//                ad7885Pic32Read(channel, &pDataVI,SS3);
//                VI_mesuree[6] = VI_mesuree[5];
//                VI_mesuree[5] = VI_mesuree[4];
//                VI_mesuree[4] = VI_mesuree[3];
//                VI_mesuree[3] = VI_mesuree[2];
//                VI_mesuree[2] = VI_mesuree[1];
//                VI_mesuree[1] = VI_mesuree[0];
//                VI_mesuree[0] = pDataVI;
//                Vi = pDataVI;
//                Nop();
//            }

            /*fonction test qui simule le systeme. Ne sera pas presente
             lors de l'integration finale*/
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
            VO_mesuree[6] = VO_mesuree[5];
            VO_mesuree[5] = VO_mesuree[4];
            VO_mesuree[4] = VO_mesuree[3];
            VO_mesuree[3] = VO_mesuree[2];
            VO_mesuree[2] = VO_mesuree[1];
            VO_mesuree[1] = VO_mesuree[0];
            transfert(VO_mesuree,commande,consigne);

            /*rafraichissement du tableau commande*/
            commande[6]=commande[5];
            commande[5]=commande[4];
            commande[4]=commande[3];
            commande[3]=commande[2];
            commande[2]=commande[1];
            commande[1]=commande[0];

//            /*Premier regulateur : Calcul de la nouvelle commande */
//            if(V_consigne[0]==18){
//                nouvelle_Commande  = regulateur(commande,V_consigne,
//                        VO_mesuree,Rn_18V,Rd_18V,Rp_18V);
//            }
//            else if(V_consigne[0]==24){
//                nouvelle_Commande  = regulateur(commande,V_consigne,
//                        VO_mesuree,Rn_24V,Rd_24V,Rp_24V);
//            }
//            else if(V_consigne[0]==30){
//                nouvelle_Commande  = regulateur(commande,V_consigne,
//                        VO_mesuree,Rn_30V,Rd_30V,Rp_30V);
//            }
//            else
//                nouvelle_Commande  = regulateur(commande,V_consigne,
//                        VO_mesuree,Rn_36V,Rd_36V,Rp_36V);

            /* Deuxième régulateur  : calcul de la commande*/
            nouvelle_Commande = regulateur_final(commande,V_consigne,VO_mesuree);

            /*Changement du rapport cyclique du PWM*/

            if(algo == 1){
                pwmSet( (1-1) * T3_TICK); //a changer !
            }
            else{
                pwmSet( ((float)(Pwm)/100) * T3_TICK);
            }

            /*** envoie d'une chaîne de caractères au port COM du PC ***/
            /* taskENTER_CRITICAL();
            putUartStr(pvParameters);
            taskEXIT_CRITICAL();*/
            vTaskDelayUntil(&xLastWakeTime, xFrequency);
            taskEXIT_CRITICAL();

    }
}

/*******************************************************************
 * Task:        	void Tache2( void *pvParameters )
 *
 * Input:               void *pvParameters -> pointeur sur un paramètre passé à la tâche
 *
 * Overview:            envoi d'une chaine de caractere au PC en forcant le mode critique puis temporisation
 *******************************************************************/
void TacheRegulation_bis( void *pvParameters ){

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
    regulateurs_init(Rn_18V,Rd_18V,Rp_18V,Rn_24V,Rd_24V,Rp_24V,Rn_30V,
            Rd_30V,Rp_30V,Rn_36V,Rd_36V,Rp_36V);
    /*** Faire toujours ... ***/

    for(;;){
        Nop();
//           taskENTER_CRITICAL();

//        V_consigne[6]=V_consigne[5];
//        V_consigne[5]=V_consigne[4];
//        V_consigne[4]=V_consigne[3];
//        V_consigne[3]=V_consigne[2];
//        V_consigne[2]=V_consigne[1];
//        V_consigne[1]=V_consigne[0];


            // Acquisition
            if (channel != -1) {
                // Read ADC VIL
                 ad7885Pic32Read(channel, &pDataVIL,SS1);
                VIL_mesuree[2] = VIL_mesuree[1];
                VIL_mesuree[1] = VIL_mesuree[0];
                VIL_mesuree[0] = pDataVIL;
                Nop();

                // Read ADC VO
                ad7885Pic32Read(channel, &pDataVO,SS2);
                VO_mesuree[2] = VO_mesuree[1];
                VO_mesuree[1] = VO_mesuree[0];
                VO_mesuree[0] = pDataVO;
                Nop();

                // Read ADC VI
                ad7885Pic32Read(channel, &pDataVI,SS3);
                VI_mesuree[2] = VI_mesuree[1];
                VI_mesuree[1] = VI_mesuree[0];
                VI_mesuree[0] = pDataVI;
                Nop();
            }

        

            /*fonction test qui simule le systeme. Ne sera pas presente
             lors de l'integration finale*/
            int consigne = 0;
            if(V_consigne[0] <= 22 )
                consigne=18;
            else if(V_consigne[0] > 22 && V_consigne[0] < 28)
                consigne=24;
            else
                consigne=30;

            /* partie emulation, a enlever si Boost Converter Branche*/
            VO_mesuree[2] = VO_mesuree[1];
            VO_mesuree[1] = VO_mesuree[0];
            transfert(VO_mesuree,commande,consigne);

            /*rafraichissement du tableau commande*/
            commande[4]=commande[3];
            commande[3]=commande[2];
            commande[2]=commande[1];
            commande[1]=commande[0];

            /*Calcul de la nouvelle commande */
            if(V_consigne[0]==18){
                nouvelle_Commande  = regulateur(commande,V_consigne,
                        VO_mesuree,Rn_18V,Rd_18V,Rp_18V);
            }
            else if(V_consigne[0]==24){
                nouvelle_Commande  = regulateur(commande,V_consigne,
                        VO_mesuree,Rn_24V,Rd_24V,Rp_24V);
            }
            else
                nouvelle_Commande  = regulateur(commande,V_consigne,
                        VO_mesuree,Rn_30V,Rd_30V,Rp_30V);


            /*Changement du rapport cyclique du PWM*/

            pwmSet( (1-0) * T3_TICK);

        /*** envoie d'une chaîne de caractères au port COM du PC ***/
       /* taskENTER_CRITICAL();
        putUartStr(pvParameters);*/
 //       taskEXIT_CRITICAL();

    }
}

/**
 * @fn void TacheUART( void *pvParameters )
 * @brief Lance l'interface
 */
void TacheUART( void *pvParameters ){

    filtreBoost = 0x000A; //attention, variable également initialisee dans TacheCan
    /*** Faire toujours ... ***/
    for(;;){

        shell();

    }
}

/**
 * @fn void TacheCAN( void *pvParameters )
 * @brief Gere la liaison avec le PIC superviseur
 */
void TacheCAN( void *pvParameters ){
    /**************************************************************************/
    short i,j;
    /*** Initialise la board (périph & interrupt) */

    /*** Initialisation des types VOLATILES */
    filtreBoost = 0;
    consigneBoost = 3;
//    alea = 0;
    timerDecoBoost = 0;
    etat = 0;
    //for(i=0; i<5; i++) valASCII[i]=0;


    LED1 = LED_ON;

    BOOL raz = is100MSecondUp();
    raz = isDemiSecondUp();
    i = 0;
    putUartStr("\r\n");

    /*** periodicite ... ***/
    portTickType xLastWakeTime;
    const portTickType xFrequency = 10000;
    for(;;){


        /*** Initialise the xLastWakeTime variable with the current time. */
        xLastWakeTime = xTaskGetTickCount();

        /*** CAN2RxMsgProcess will check if CAN2 has received a message */
        CANxRxMsgProcess();

        // check des timer
        checkTimer();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

    }
}