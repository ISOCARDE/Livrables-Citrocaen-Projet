/**
* @file canBoost.h
* @brief gestion du CAN cote boost
* @author Alain WERCK
* @date 27/10/2013
*/

#ifndef CANBOOST_H
#define	CANBOOST_H

#define CAN_MASQUE_BOOST        0b11111111111

/*** GLOBALES *****************************************************************/
volatile short filtreBoost;   // compris dans l'intervalle 0 to 2046 (2047 reserve !)
char consigneBoost;
volatile char valASCII[5];
volatile char etat;

/*** PROTOTYPE ****************************************************************/

/****************************************************************************
  Function:
    void CAN2Init(void);

  Description:
	This function initializes CAN2 module. It sets up speed, FIFOs,
	filters and interrupts. FIFO0 is set up for TX with 8 message
	buffers. FIFO1 is set up for RX with 8 message buffers. Filter 0
	is set with Mask 0 for SID 0x202. Only RXNEMPTY interrupt and
	RBIF interrupt is enabled.
  ***************************************************************************/
void CANxInit(short filtre);
void CANxInitFiltre(short filtre);
void shortToASCII(short filtre);
/****************************************************************************
  Function:
    void CAN2RxMsgProcess(void);

  Description:
	This function checks if a message is available to be read in
	CAN2 FIFO1. If a message is available, the function will check
	byte 0 (boolean flag) of the CAN message payload and will switch
	LED5 accordingly. It then calls CAN2TxSendLEDMsg().
  ***************************************************************************/
void CANxRxMsgProcess(void);
/****************************************************************************
  Function:
    void CAN2TxSendLEDMsg(void);

  Description:
	This function will send a CAN message with SID 0x201. In the payload,
	it sends one byte which is a toggle state for LED6. FIFO0 is used for
	sending the message.
  ***************************************************************************/
void CANxTxSendMsg(char typeReq);

#endif	/* CANBOOST_H */

