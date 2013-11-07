/**
* @file canSpv.h
* @brief gestion du CAN cote superviseur
* @author Alain WERCK
* @date 27/10/2013
*/

#ifndef CANSPV_H
#define	CANSPV_H


#define CAN_MASQUE_SPV          0b11100000000   // on accepte toute les IDs de boost

/*** GLOBALES *****************************************************************/
volatile char requeteEnCours;
volatile char consigneEnCours;
volatile char inviteEnCours;
volatile short adresseInvit;
volatile short tabBoostConnectes[255][3];
volatile char valASCII[5];
volatile char valConsigne;
volatile short adrConsigne;

/*** PROTOTYPE ****************************************************************/

/****************************************************************************
  Function:
    void CAN1Init(void);

  Description:
	This function initializes CAN1 module. It sets up speed, FIFOs,
	filters and interrupts. FIFO0 is set up for TX with 8 message
	buffers. FIFO1 is set up for RX with 8 message buffers. Filter 0
	is set with Mask 0 for SID 0x201. Only RXNEMPTY interrupt and
	RBIF interrupt is enabled.
***************************************************************************/
void CAN1Init(short filtre);

/****************************************************************************
  Function:
    void CAN1RxMsgProcess(void);

  Description:
	This function checks if a message is available to be read in
	CAN1 FIFO1. If a message is available, the function will check
	byte 0 (boolean flag) of the CAN message payload and will switch
	LED6 accordingly.
  ***************************************************************************/
void CAN1RxMsgProcess(void);

/****************************************************************************
  Function:
    void CAN1TxSendLEDMsg(void);

  Description:
	This function will send a CAN message with SID 0x202. In the payload,
	it sends one byte which is a toggle state for LED5. FIFO0 is used for
	sending the message.
  ***************************************************************************/
BOOL CAN1TxSendMsg(char typeReq, char consigne, short module);

#endif	/* CANSPV_H */

