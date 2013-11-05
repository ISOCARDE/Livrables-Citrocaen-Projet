/**
* @file CANFunctions.h
* @brief gestion de la com CAN
* @author Alain WERCK
* @date 25/10/2013
*/

#ifndef _CAN_FUNCTIONS_H_
#define _CAN_FUNCTIONS_H_

#include "GenericTypeDefs.h"
#include ".\gpio.h"
#include <p32xxxx.h>
#include <sys/kmem.h>
#include "plib.h"

#define SYSTEM_FREQ 80000000
#define CAN_BUS_SPEED 500000 // on desire une vitesse de 500Kbps sur le bus (voir rapport pour le calcul)

#define CAN1_BRPVAL	0x7	// CAN speed select - 0x7 for 500kbps, 0xF for 250Kbps, 0x3 for 1Mbps
#define CAN2_BRPVAL     0x7	// Use same speed for both CAN modules. Time quanta per bit is set to 10

extern BYTE CAN1MessageFifoArea[2 * 8 * 16];	/* This is the CAN1 FIFO message area.	*/
extern BYTE CAN2MessageFifoArea[2 * 8 * 16];	/* This is the CAN2 FIFO message area.	*/

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
void CAN1Init(void);

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
void CAN2Init(void);

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
    void CAN2RxMsgProcess(void);

  Description:
	This function checks if a message is available to be read in
	CAN2 FIFO1. If a message is available, the function will check
	byte 0 (boolean flag) of the CAN message payload and will switch 
	LED5 accordingly. It then calls CAN2TxSendLEDMsg().
  ***************************************************************************/
void CAN2RxMsgProcess(void);

/****************************************************************************
  Function:
    void CAN1TxSendLEDMsg(void);

  Description:
	This function will send a CAN message with SID 0x202. In the payload,
	it sends one byte which is a toggle state for LED5. FIFO0 is used for
	sending the message.
  ***************************************************************************/
void CAN1TxSendLEDMsg(void);

/****************************************************************************
  Function:
    void CAN2TxSendLEDMsg(void);

  Description:
	This function will send a CAN message with SID 0x201. In the payload,
	it sends one byte which is a toggle state for LED6. FIFO0 is used for
	sending the message.
  ***************************************************************************/
void CAN2TxSendLEDMsg(void);

#endif
