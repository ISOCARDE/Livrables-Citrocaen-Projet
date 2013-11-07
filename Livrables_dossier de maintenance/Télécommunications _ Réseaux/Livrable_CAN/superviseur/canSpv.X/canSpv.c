/**
* @file canSpv.c
* @brief gestion de la com CAN cote superviseur
* @author Alain WERCK
* @date 27/10/2013
*/

/*** INCLUDES *****************************************************************/
    #include "includes.h"

/*** PROTOTYPES ***************************************************************/

/* isCAN1MsgReceived is true if CANx channel 1 received
 * a message. This flag is updated in the CANx ISR. */
static volatile BOOL isCAN1MsgReceivedCH1 = FALSE;


/**
* @fn void CAN1Init(void)
* @brief intialisation du CAN de supervision
*/
void CAN1Init(short filtre)
{
    CAN_BIT_CONFIG canBitConfig;

    /*** Step 1: Switch the CAN module ON and switch it to Configuration mode. Wait till the switch is complete */
    CANEnableModule(CAN1,TRUE);
    CANSetOperatingMode(CAN1, CAN_CONFIGURATION);
    while(CANGetOperatingMode(CAN1) != CAN_CONFIGURATION);

    /*** Step 2: Configure the CAN Module Clock. The
     * CAN_BIT_CONFIG data structure is used
     * for this purpose. The propagation segment,
     * phase segment 1 and phase segment 2
     * are configured to have 3TQ. The
     * CANSetSpeed function sets the baud.*/
    canBitConfig.phaseSeg2Tq            = CAN_BIT_3TQ;
    canBitConfig.phaseSeg1Tq            = CAN_BIT_3TQ;
    canBitConfig.propagationSegTq       = CAN_BIT_3TQ;
    canBitConfig.phaseSeg2TimeSelect    = TRUE;
    canBitConfig.sample3Time            = TRUE;
    canBitConfig.syncJumpWidth          = CAN_BIT_2TQ;

    CANSetSpeed(CAN1,&canBitConfig,SYS_FREQ,CAN_BUS_SPEED);

    /*** Step 3: Assign the buffer area to the
    * CAN module. */
    CANAssignMemoryBuffer(CAN1,CAN1MessageFifoArea,(2 * 8 * 16));   // 2 channels
                                                                    // de 8 messages en buffer chacun
                                                                    // 1 message fait 16 octets = 128 bits

    /* Step 4: Configure channel 0 for TX and size of
     * 8 message buffers with RTR disabled and low medium
     * priority. Configure channel 1 for RX and size
     * of 8 message buffers and receive the full message.
     */
    CANConfigureChannelForTx(CAN1, CAN_CHANNEL0, 8, CAN_TX_RTR_DISABLED, CAN_LOW_MEDIUM_PRIORITY);
    CANConfigureChannelForRx(CAN1, CAN_CHANNEL1, 8, CAN_RX_FULL_RECEIVE);

    /* Step 5: Configure filters and mask. Configure
     * filter 0 to accept SID messages with ID 0x201.
     * Configure filter mask 0 to compare all the ID
     * bits and to filter by the ID type specified in
     * the filter configuration. Messages accepted by
     * filter 0 should be stored in channel 1. */
    CANConfigureFilter  (CAN1,
                        CAN_FILTER0,
                        filtre,
                        CAN_SID);   // CAN_SID = pour les messages standard (non-etendus)


    CANConfigureFilterMask  (CAN1,
                            CAN_FILTER_MASK0,
                            CAN_MASQUE_SPV, CAN_SID,
                            CAN_FILTER_MASK_IDE_TYPE); // si IDE, on ne le lit pas
    
    CANLinkFilterToChannel  (CAN1, CAN_FILTER0, CAN_FILTER_MASK0, CAN_CHANNEL1);
    
    CANEnableFilter         (CAN1, CAN_FILTER0, TRUE);

    /* Step 6: Enable interrupt and events. Enable the receive
     * channel not empty event (channel event) and the receive
     * channel event (module event).
     * The interrrupt peripheral library is used to enable
     * the CAN interrupt to the CPU. */
    CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);

    
    CANEnableModuleEvent (CAN1, CAN_RX_EVENT, TRUE);

    /* These functions are from interrupt peripheral
     * library. */
    INTSetVectorPriority(INT_CAN_1_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_CAN_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_CAN1, INT_ENABLED);

    /* Step 7: Switch the CAN mode
     * to normal mode. */
    CANSetOperatingMode(CAN1, CAN_NORMAL_OPERATION);
    while(CANGetOperatingMode(CAN1) != CAN_NORMAL_OPERATION);

}

///**
//* @fn char * shortToASCII(short filtre)
//* @brief transforme la valeur du filtre sur 11 bits en code ASCII pour envoie sur l'UART
//*/
//void shortToASCII(short filtre)
//{
//    //! sur 16 bits, MAX = 65535
//    char i = 0;
//    short temp = filtre;
//    while(i<5)
//    {
//        valASCII[i]=(char)(temp/puissance10(4-i)) +0x30;
//        temp = temp-(int)(valASCII[i]-0x30)*puissance10(4-i);
//        i++;
//    }
//}

/**
* @fn void CAN1RxMsgProcess(void)
* @brief reception d'un message cote superviseur
*/
void CAN1RxMsgProcess(void)
{
    /* This function will check if a CAN
    * message is available in CAN1 channel 1.
    * If so , the message is read.*/

    CANRxMessageBuffer * message;

    if(isCAN1MsgReceivedCH1 == FALSE)
    {
        return;
    }

    /* Message was received. Reset message received flag to catch
    * the next message and read the message. Note that
    * you could also check the CANGetRxMessage function
    * return value for null to check if a message has
    * been received. */
    isCAN1MsgReceivedCH1 = FALSE;
    message = CANGetRxMessage(CAN1,CAN_CHANNEL1);

    //! test visuel
    LED3 = LED_OFF;

    if(message->msgEID.DLC == 0)
    {
        if(message->msgSID.SID == adresseInvit)
        {
            //! sauvegarde de l'ID du nouveau boost
            char caseTabBoostConnectes = adresseInvit-CAN_FILTRE_DEMARRAGE;
            tabBoostConnectes[caseTabBoostConnectes][0] = adresseInvit;
//            putUartStr("Enregistré ID : ");
//            shortToASCII(adresseInvit);
//            putUartC(valASCII[0]);
//            putUartC(valASCII[1]);
//            putUartC(valASCII[2]);
//            putUartC(valASCII[3]);
//            putUartC(valASCII[4]);
//            putUartC('\r');
//            putUartC('\n');

            //! on incremente l'adresse fourni pour la prochaine invite
            adresseInvit++;
            if(adresseInvit >= CAN_FILTRE_MAX) adresseInvit = CAN_FILTRE_DEMARRAGE;
            /******************************************************************/
            // prevenir via UART si le nbr max est connecte
            /******************************************************************/
            //! on verifie qu'elle n'est pas utilisee
            caseTabBoostConnectes = adresseInvit-CAN_FILTRE_DEMARRAGE;
            char compteur = 0;
            while(tabBoostConnectes[caseTabBoostConnectes][0]!=0 && compteur<CAN_NOMBRE_MODULES_POSSIBLES)
            {
                caseTabBoostConnectes++;
                if(caseTabBoostConnectes >= CAN_FILTRE_MAX) caseTabBoostConnectes = 0;

                compteur++;
            }
            if(compteur == CAN_NOMBRE_MODULES_POSSIBLES) putUartStr("Nombre MAX de boost connectés /!\\");
            else adresseInvit = caseTabBoostConnectes + CAN_FILTRE_DEMARRAGE;

//            unsigned short i;
//            for(i=0; i<65000; i++) Nop();
            
            inviteEnCours = 0;
            timerInviteEnCours = 0;
            timerAvantNouvelleInvite = 0;
            LED1 = LED_OFF;

            
        }
        else if(consigneEnCours == 1)
        {
            //! acquittement de la consigne
            consigneEnCours = 0;
            timerConsigneEnCours = 0;

            //LED2 = LED_OFF;

//            putUartStr("ACK : ");
//            shortToASCII((short)(message->msgSID.SID));
//            putUartC(valASCII[0]);
//            putUartC(valASCII[1]);
//            putUartC(valASCII[2]);
//            putUartC(valASCII[3]);
//            putUartC(valASCII[4]);
//            putUartC(' ');
//            putUartC( (tabBoostConnectes[(short)(message->msgSID.SID)-CAN_FILTRE_DEMARRAGE][1] >> 8) + 0x30);
//            putUartC('\r');
//            putUartC('\n');
        }        
    }
    else if(message->msgEID.DLC == 4)
    {
        //! acquittement de la requete par reponse
        requeteEnCours = 0;
        timerRequeteEnCours = 0;

        unsigned char dataRecues[4];
        dataRecues[0] = message->data[0]; // = 0x18
        dataRecues[1] = message->data[1];
        dataRecues[2] = message->data[2];
        dataRecues[3] = message->data[3];

//        char i; BYTE buffer[10]; float dataFloat[4];
        
//        snprintf(buffer, 10, "Hello %d", dataRecues[0]);
//        putUartStr(buffer); putUartC('\r'); putUartC('\n');

//        dataFloat[1] = (float)(dataRecues[1]);
//        snprintf(buffer,10, "%d", dataRecues[1]);
//        putUartStr(buffer); putUartC('\r'); putUartC('\n');
//        snprintf(buffer,10, "%f", dataFloat[1]);
//        putUartStr(buffer); putUartC('\r'); putUartC('\n');

//        for(i=0; i<4; i++)
//        {
//            dataFloat[i] = (float)(10*dataRecues[i]*0.0195);
//            snprintf(buffer,10, "%lf", dataRecues[i]);
//            putUartStr(buffer);
//            putUartC('\r');putUartC('\n');
//
//        }
       

        //! stockage des valeurs recus
        char adresseActuel = (message->msgSID.SID) - CAN_FILTRE_DEMARRAGE;
//        tabBoostConnectes[adresseActuel][1]=0;
//        tabBoostConnectes[adresseActuel][2]=0;
        
        tabBoostConnectes[adresseActuel][1] = dataRecues[0] << 8;
        tabBoostConnectes[adresseActuel][1] = (tabBoostConnectes[adresseActuel][1] | dataRecues[1]);
        tabBoostConnectes[adresseActuel][2] = dataRecues[2] << 8;
        tabBoostConnectes[adresseActuel][2] = (tabBoostConnectes[adresseActuel][2] | dataRecues[3]);


        LED3 = LED_OFF;

//        putUartStr("Réponse : ");
//        shortToASCII((short)(message->msgSID.SID));
//        putUartC(valASCII[0]);
//        putUartC(valASCII[1]);
//        putUartC(valASCII[2]);
//        putUartC(valASCII[3]);
//        putUartC(valASCII[4]);
//        putUartC('\r');
//        putUartC('\n');
//        putUartStr("Vo = "); putUartC(dataRecues[0]+0x30); putUartC('\r'); putUartC('\n');
//        putUartStr("Vo* = "); putUartC(dataRecues[1]+0x30); putUartC('\r'); putUartC('\n');
//        putUartStr("Vi = "); putUartC(dataRecues[2]+0x30); putUartC('\r'); putUartC('\n');
//        putUartStr("Vil = "); putUartC(dataRecues[3]+0x30); putUartC('\r'); putUartC('\n');
    }

    /* Call the CANUpdateChannel() function to let
    * CAN 1 module know that the message processing
    * is done. Enable the receive channale not empty event
    * so that the CAN module generates an interrupt when
    * the event occurs the next time.*/
    CANUpdateChannel(CAN1, CAN_CHANNEL1);
    CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
}

/**
* @fn void CAN1TxSendMsg(void)
* @brief envoie d'un message du superviseur
*/
BOOL CAN1TxSendMsg(char typeReq, char consigne, short module)
{
    /* This function will send a message to
    * CAN2 with SID 202. The data payload
    * size is 1 byte. The value of the LED5Status
    * will be toggled and then sent as
    * the payload. CAN1 Channel 0 is used
    * to send the message*/

    

    //! faire les test avant de créer le message, sinon probleme de sotckage
    //! verifier si aucune trame est en cours
    if(requeteEnCours || consigneEnCours || inviteEnCours)
    {
        return FALSE;
    }

    short numTabBoostConnectes = module-CAN_FILTRE_DEMARRAGE;
    if((typeReq == REQUETE || typeReq == CONSIGNE) && ((numTabBoostConnectes<0) || (tabBoostConnectes[numTabBoostConnectes][0] == 0)))
    {
        if(typeReq == CONSIGNE)
        {
            putUartStr("adresse non enregistrée"); putUartC('\r'); putUartC('\n');
            consigneToSend = 0;
        }
        return FALSE;
    }

    /* Get a pointer to the next buffer in the channel
    * check if the returned value is null. */
    CANTxMessageBuffer * message;
    message = CANGetTxMessageBuffer(CAN1,CAN_CHANNEL0);

    if(message != NULL)
    {
        /* Form a Standard ID CAN message.
        * Start by clearing the buffer.
        * Send message to CAN2.
        * IDE = 0 means Standard ID message.
        * Send one byte of data.
        * This is the payload.*/
        message->messageWord[0] = 0;
        message->messageWord[1] = 0;
        message->messageWord[2] = 0;
        message->messageWord[3] = 0;

        //! sauvegarde du contexte de la transmission
        if(typeReq != INVITE) saveContexte(typeReq, consigne, module);

        switch(typeReq)
        {
            //! INVITE
            case INVITE:    if(inviteEnCours==0){
//                                putUartC('I');
//                                shortToASCII(module);
//                                putUartC(valASCII[0]);
//                                putUartC(valASCII[1]);
//                                putUartC(valASCII[2]);
//                                putUartC(valASCII[3]);
//                                putUartC(valASCII[4]);
//                                putUartC('\r');
//                                putUartC('\n');
                                message->msgSID.SID     = CAN_FILTRE_INVIT;
                                message->msgEID.IDE     = 0;
                                message->msgEID.DLC     = 2;
                                message->data[0]        = (BYTE)(module>>8);
                                message->data[1]        = (BYTE)module;
                                LED1 = LED_ON;
                                timerInviteEnCours = 0;
                                inviteEnCours = 1;
                                
                            }
                            break;
            //! CONSIGNE
            case CONSIGNE:  tabBoostConnectes[numTabBoostConnectes][1] = ( (0x00FF & tabBoostConnectes[numTabBoostConnectes][1]) | (consigne<<8) );
                            message->msgSID.SID     = module;
                            message->msgEID.IDE     = 0;
                            message->msgEID.DLC     = 1;
                            message->data[0]        = consigne;
                            //LED2 = LED_ON;
                            consigneToSend = 0;
                            timerConsigneEnCours = 0;
                            consigneEnCours = 1;
                            
                            break;
            //! REQUETE
            case REQUETE:   message->msgSID.SID     = module;
                            message->msgEID.IDE     = 0;
                            message->msgEID.RTR     = 1;
                            message->msgEID.DLC     = 0;
                            LED3 = LED_ON;
                            timerRequeteEnCours = 0;
                            requeteEnCours = 1;
                            
                            break;


        }
        /* This function lets the CAN module
        * know that the message processing is done
        * and message is ready to be processed. */

        CANUpdateChannel(CAN1,CAN_CHANNEL0);

        /* Direct the CAN module to flush the
        * TX channel. This will send any pending
        * message in the TX channel. */

        CANFlushTxChannel(CAN1,CAN_CHANNEL0);

        return TRUE;
    }
}


void __attribute__((vector(46), interrupt(ipl4), nomips16)) CAN1InterruptHandler(void)
{
    /* This is the CAN1 Interrupt Handler.
    * Note that there are many source events in the
    * CAN1 module for this interrupt. These
    * events are enabled by the  CANEnableModuleEvent()
    * function. In this example, only the RX_EVENT
    * is enabled. */


    /* Check if the source of the interrupt is
    * RX_EVENT. This is redundant since only this
    * event is enabled in this example but
    * this shows one scheme for handling events. */

    if((CANGetModuleEvent(CAN1) & CAN_RX_EVENT) != 0)
    {

        /* Within this, you can check which channel caused the
        * event by using the CANGetModuleEvent() function
        * which returns a code representing the highest priority
        * pending event. */

        if(CANGetPendingEventCode(CAN1) == CAN_CHANNEL1_EVENT)
        {
            /* This means that channel 1 caused the event.
             * The CAN_RX_CHANNEL_NOT_EMPTY event is persistent. You
             * could either read the channel in the ISR
             * to clear the event condition or as done
             * here, disable the event source, and set
             * an application flag to indicate that a message
             * has been received. The event can be
             * enabled by the application when it has processed
             * one message.
             *
             * Note that leaving the event enabled would
             * cause the CPU to keep executing the ISR since
             * the CAN_RX_CHANNEL_NOT_EMPTY event is persistent (unless
             * the not empty condition is cleared.)
             * */

            CANEnableChannelEvent(CAN1, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            isCAN1MsgReceivedCH1 = TRUE;

            //? appelle de fonction dans l'interruption ?
            //CAN1RxMsgProcess();
        }
    }

    /* The CAN1 Interrupt flag is  cleared at the end of the
    * interrupt routine. This is because the event source
    * that could have caused this interrupt  to occur
    * (CAN_RX_CHANNEL_NOT_EMPTY) is disabled. Attempting to
    * clear the CAN1 interrupt flag when the the CAN_RX_CHANNEL_NOT_EMPTY
    * interrupt is enabled will not have any effect because the
    * base event is still present. */

    INTClearFlag(INT_CAN1);
}