/**
* @file canBoost.h
* @brief gestion du CAN cote boost
* @author Alain WERCK
* @date 27/10/2013
*/

/*** INCLUDES *****************************************************************/
    #include "main.h"

/*** PROTOTYPES ***************************************************************/

static volatile BOOL isCANxMsgReceived = FALSE;



/**
* @fn void CANxInit(void)
* @brief intialisation du CAN de boost
*/
void CANxInit(short filtre)
{
    CAN_BIT_CONFIG canBitConfig;

    /* This function will intialize
     * CANx module. */

    /* Step 1: Switch the CAN module
     * ON and switch it to Configuration
     * mode. Wait till the switch is
     * complete */

    CANEnableModule(CAN_BOOST,TRUE);

    CANSetOperatingMode(CAN_BOOST, CAN_CONFIGURATION);
    while(CANGetOperatingMode(CAN_BOOST) != CAN_CONFIGURATION);

    /* Step 2: Configure the CAN Module Clock. The
     * CAN_BIT_CONFIG data structure is used
     * for this purpose. The propagation,
     * phase segment 1 and phase segment 2
     * are configured to have 3TQ. The CANSetSpeed()
     * function sets the baud. */

    canBitConfig.phaseSeg2Tq            = CAN_BIT_3TQ;
    canBitConfig.phaseSeg1Tq            = CAN_BIT_3TQ;
    canBitConfig.propagationSegTq       = CAN_BIT_3TQ;
    canBitConfig.phaseSeg2TimeSelect    = TRUE;
    canBitConfig.sample3Time            = TRUE;
    canBitConfig.syncJumpWidth          = CAN_BIT_2TQ;

    CANSetSpeed(CAN_BOOST,&canBitConfig,SYS_FREQ,CAN_BUS_SPEED);

    /* Step 3: Assign the buffer area to the
     * CAN module.
     */

    CANAssignMemoryBuffer(CAN_BOOST,CANxMessageFifoArea,1 * 1 * CAN_TX_RX_MESSAGE_SIZE_BYTES);

    /* Step 4: Configure channel 0 for TX and size of
     * 8 message buffers with RTR disabled and low medium
     * priority. Configure channel 1 for RX and size
     * of 8 message buffers and receive the full message.
     */

    CANConfigureChannelForTx(CAN_BOOST,CAN_CHANNEL0,8,CAN_TX_RTR_DISABLED,CAN_LOW_MEDIUM_PRIORITY);
    CANConfigureChannelForRx(CAN_BOOST,CAN_CHANNEL1,8,CAN_RX_FULL_RECEIVE);

    /* Step 5: Configure filters and mask. Configure
     * filter 0 to accept SID messages with ID 0x202.
     * Configure filter mask 0 to compare all the ID
     * bits and to filter by the ID type specified in
     * the filter configuration. Filter 0 accepted
     * messages are stored in channel 1.  */

    CANConfigureFilter(CAN_BOOST, CAN_FILTER0, filtre, CAN_SID);
    CANConfigureFilterMask  (CAN_BOOST, CAN_FILTER_MASK0, CAN_MASQUE_BOOST, CAN_SID, CAN_FILTER_MASK_IDE_TYPE);
    CANLinkFilterToChannel  (CAN_BOOST, CAN_FILTER0, CAN_FILTER_MASK0, CAN_CHANNEL1);
    CANEnableFilter(CAN_BOOST, CAN_FILTER0, TRUE);

	/* Step 6: Enable interrupt and events. Enable the receive
     * channel not empty event (channel event) and the receive
     * channel event (module event).
     * The interrrupt peripheral library is used to enable
     * the CAN interrupt to the CPU. */

    CANEnableChannelEvent(CAN_BOOST, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
    CANEnableModuleEvent(CAN_BOOST, CAN_RX_EVENT, TRUE);

    /* These functions are from interrupt peripheral
     * library. */

    INTSetVectorPriority(INT_CAN_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_CAN_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_CAN, INT_ENABLED);

    /* Step 7: Switch the CAN mode
     * to normal mode. */

    CANSetOperatingMode(CAN_BOOST, CAN_NORMAL_OPERATION);
    while(CANGetOperatingMode(CAN_BOOST) != CAN_NORMAL_OPERATION);

}

/**
* @fn void CANxInitFiltre(short filtre)
* @brief changement de la valeur du filtre 0
*/
void CANxInitFiltre(short filtre)
{
    CANEnableFilter(CAN_BOOST, CAN_FILTER0, FALSE);
    CANConfigureFilter(CAN_BOOST, CAN_FILTER0, filtre, CAN_SID);
    CANEnableFilter(CAN_BOOST, CAN_FILTER0, TRUE);

//    C2FLTCON0bits.FLTEN3 = 0;/* Disable the filter */
//    Nop();
//    C2FLTCON0bits.FSEL3 = 1;/* Store messages in FIFO1 */
//    C2FLTCON0bits.MSEL3 = 0;/* Use Mask 0 */
//    C2RXF0bits.SID = filtre;/* Filter 3 SID */
//    C2RXF0bits.EXID = 0;/* Filter only SID messages */
//    C2RXM0bits.SID = 0x7FF;/* Ignore last 2 bits in comparison */
//    C2RXM0bits.MIDE = 1;/* Match only message types. */
//    C2FLTCON0bits.FLTEN0 = 1;/* Enable the filter */
//    Nop();

    timerDecoBoost = 0;
}

/**
* @fn char * shortToASCII(short filtre)
* @brief transforme la valeur du filtre sur 16 bits (short) en code ASCII pour envoie sur l'UART
*/
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
* @fn void CANxRxMsgProcess(void)
* @brief recpetion des messages cote boost
*/
void CANxRxMsgProcess(void)
{
    CANRxMessageBuffer * message;

    if(isCANxMsgReceived == FALSE)
    {
        /* CANx did not receive any message
         * so exit the function. Note that the
         * isCANxMsgReceived flag is updated
         * by the CANx ISR. */
        return;
    }

    /* Message was received. Reset isCANxMsgReceived flag
    * to catch the next message. */
    isCANxMsgReceived = FALSE;
    message = CANGetRxMessage(CAN_BOOST,CAN_CHANNEL1);

    //! maj du timer de deconnection
    timerDecoBoost = 0;

    CAN_RX_MSG_SID idInvit, idModule;
    idInvit.SID = CAN_FILTRE_INVIT;
    idModule.SID = filtreBoost;

    /*** 3 types de trames recues */
    
    //! INVITE
        if((message->msgSID.SID) == idInvit.SID)
        {
            LED3 = LED_OFF;

            //putUartStr("Invite : ");
            Nop();
            filtreBoost = ((message->data[0])<<8) | (message->data[1]);

//            shortToASCII(filtreBoost);

//            putUartC(valASCII[0]);
//            putUartC(valASCII[1]);
//            putUartC(valASCII[2]);
//            putUartC(valASCII[3]);
//            putUartC(valASCII[4]);
//            putUartC('\r');
//            putUartC('\n');

            CANUpdateChannel(CAN_BOOST, CAN_CHANNEL1);
            CANEnableChannelEvent(CAN_BOOST, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);

             //! reinitialiser le CAN avec la nouvelle adresse fournie
            CANxInitFiltre(filtreBoost);
            etat = 1;
            Nop();
            short tempo_invite = C2RXF0bits.SID;

            //! acquittement de la consigne
            CANxTxSendMsg(ACK);
            return;
        }
    //! CONSIGNE OU REQUETE
        else if((message->msgSID.SID) == idModule.SID)
        {

            LED3 = LED_OFF;
            unsigned int bufferToRead[4];

            bufferToRead[0]=message->messageWord[0];
            bufferToRead[1]=message->messageWord[1];
            bufferToRead[2]=message->messageWord[2];
            bufferToRead[3]=message->messageWord[3];

            putUartC(bufferToRead[0]>>24);
            putUartC(bufferToRead[0]>>16);
            putUartC(bufferToRead[0]>>8);
            putUartC(bufferToRead[0]);
            putUartC(bufferToRead[1]>>24);
            putUartC(bufferToRead[1]>>16);
            putUartC(bufferToRead[1]>>8);
            putUartC(bufferToRead[1]);
            putUartC(bufferToRead[2]>>24);
            putUartC(bufferToRead[2]>>16);
            putUartC(bufferToRead[2]>>8);
            putUartC(bufferToRead[2]);
            putUartC(bufferToRead[3]>>24);
            putUartC(bufferToRead[3]>>16);
            putUartC(bufferToRead[3]>>8);
            putUartC(bufferToRead[3]);

            if((((message->messageWord[1])>>24) == 0x20) && (message->msgEID.DLC == 0))
            {
                putUartStr("Réponse envoyée ");
                putUartC('\r');
                putUartC('\n');

                //! a valeur d'acquittement
                CANxTxSendMsg(REPONSE);
            }
            // verifier que la data non nulle
            else if((message->msgEID.DLC) == 1)
            {
                unsigned char tabValSortie[] = {'0','0','1','8','2','4','3','0','3','6'};
                putUartStr("Consigne : ");
                consigneBoost = message->data[0];

                putUartC(tabValSortie[consigneBoost]);
                putUartC(tabValSortie[consigneBoost+1]);
                putUartC('\r');
                putUartC('\n');

                //! acquittement de la consigne
                CANxTxSendMsg(ACK);

            }
        }

    /* Call the CANUpdateChannel() function to let
    * the CAN module know that the message processing
    * is done. Enable the event so that the CAN module
    * generates an interrupt when the event occurs.*/

    CANUpdateChannel(CAN_BOOST, CAN_CHANNEL1);
    CANEnableChannelEvent(CAN_BOOST, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, TRUE);
}

/**
* @fn void CANxTxSendMsg(void)
* @brief envoie de message du boost
*/
void CANxTxSendMsg(char typeReq)
{
    /* This function will send a message to
    * CAN1 with SID 201. The data payload
    * size is 1 byte. The value of the LED6Status
    * will be toggled and then sent as
    * the payload. */

    CANTxMessageBuffer * message;

    /* Get a pointer to the next buffer in the channel
    * check if the returned value is null. */

    message = CANGetTxMessageBuffer(CAN_BOOST,CAN_CHANNEL0);

    if(message != NULL)
    {
        /* Form a Standard ID CAN message.
        * Start by clearing the buffer.
        * Send message to CANx.
        * IDE = 0 means Standard ID message.
        * Send one byte of data.
        * This is the payload. */
        message->messageWord[0] = 0;
        message->messageWord[1] = 0;
        message->messageWord[2] = 0;
        message->messageWord[3] = 0;

        switch(typeReq)
        {
            //! REPONSE = on envoie les val necessaires a l'IHM
            case REPONSE:   message->msgSID.SID     = filtreBoost;
                            message->msgEID.IDE     = 0;
                            message->msgEID.DLC     = 4;
                            message->data[0]        = '1';
                            message->data[1]        = '2';
                            message->data[2]        = '3';
                            message->data[3]        = '4';
                            break;
            //! ACK = on envoie un message sans data !
            case ACK:       message->msgSID.SID     = filtreBoost;
                            message->msgEID.IDE     = 0;
                            message->msgEID.DLC     = 0;
                            break;
        }


        /* This function lets the CAN module
        * know that the message processing is done
        * and message is ready to be processed. */

        CANUpdateChannel(CAN_BOOST,CAN_CHANNEL0);

        /* Direct the CAN module to flush the
        * TX channel. This will send any pending
        * message in the TX channel. */

        CANFlushTxChannel(CAN_BOOST,CAN_CHANNEL0);
    }
}

void __attribute__((vector(47), interrupt(ipl4), nomips16)) CAN2InterruptHandler(void)
{

    /* This is the CANx Interrupt Handler. Note that there
    * are many events in the CANx module that can cause
    * this interrupt. These events are enabled by the
    * CANEnableModuleEvent() function. In this example,
    * only the RX_EVENT is enabled. */


    /* Check if the source of the interrupt is RX_EVENT.
    * This is redundant  since only this event is enabled
    * in this example but this shows one scheme for handling
    * interrupts. */

    if((CANGetModuleEvent(CAN_BOOST) & CAN_RX_EVENT) != 0)
    {

        /* Within this, you can check which event caused the
         * interrupt by using the CANGetPendingEventCode() function
        * to get a code representing the highest priority active
        * event.*/

        if(CANGetPendingEventCode(CAN_BOOST) == CAN_CHANNEL1_EVENT)
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

            CANEnableChannelEvent(CAN_BOOST, CAN_CHANNEL1, CAN_RX_CHANNEL_NOT_EMPTY, FALSE);
            isCANxMsgReceived = TRUE;

            //? appelle de fonction dans l'interruption ?
            //CANxRxMsgProcess();
        }
    }

    /* The CANx Interrupt flag is  cleared at the end of the
    * interrupt routine. This is because the event
    * that could have caused this interrupt  to occur
    * (CAN_RX_CHANNEL_NOT_EMPTY) is disabled. Attempting to
    * clear the CANx interrupt flag when the the CAN_RX_CHANNEL_NOT_EMPTY
    * interrupt is enabled will not have any effect because the
    * base event is still present. */

    INTClearFlag(INT_CAN);
}
