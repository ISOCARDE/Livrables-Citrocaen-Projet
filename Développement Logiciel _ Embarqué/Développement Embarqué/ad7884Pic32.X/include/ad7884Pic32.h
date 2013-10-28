/**
* @file ad7884Pic32.h
* @brief librairie SPI pour pilotage ADC externe AD7884
* @author BLIN Valentin
* @version 1
* @date 18/05/2012
*
* Librairie SPI pour pilotage ADC externe AD7884
*
*
*/

#include <plib.h>

/* MACROS**************/

#define SYS_FREQ (80000000)
#define HANDLE_VALID    1
#define HANDLE_INVALID  0

/* DEFINITIONS ***************/

typedef int Handle;
typedef int* pData;
typedef int chSPI;
typedef int freq;
typedef struct{
    IoPortId Port;
    unsigned int Bit;
}SlaveS;


#define 	RC3 		LATCbits.LATC3			// On pourra directement faire RC3 = 1;
#define		SCCS		LATDbits.LATD7
#define		CNVST		LATDbits.LATD4
#define		CSad		LATDbits.LATD5
#define		BUSY		PORTDbits.PORTD6


/* FUNCTION PROTOTYPES ***************/

/**
* @fn handle ad7634Pic32Open(chSPI, freq)
* @brief Configuration liaison SPI coté MCU
*
* @param chSPI : canal SPI utilisé
* @param freq : débit voulu
* @return 1 si la configuration est réussi, 0 sinon
*/
Handle ad7884Pic32Open(chSPI, freq);


/**
* @fn void ad7634Pic32Read(Handle, chSPI, pData, SlaveS)
* @brief Configuration liaison SPI coté MCU
*
* @param Handle : Permet de vérifier si la configuration SPI coté MCU est bien réalisée
* @param chSPI : canal SPI utilié
* @param pData : pointeur qui récupère les données
* @param SlaveS : broche /SS utilisée
*/
void ad7884Pic32Read(Handle, chSPI, pData, SlaveS);

/**
* @fn ad7634Pic32Close(Handle, chSPI)
* @brief ferme le canal SPI utilsé
*
* @param Handle : Permet de vérifier si la configuration SPI coté MCU est bien réalisée
* @param chSPI : canal SPI à fermer
* @return
*/
void ad7634Pic32Close(Handle, chSPI);



/**
* @fn void delay(int)
* @brief Attente
*
* @param int ->	le delay en s
*/
//void delay(unsigned int);