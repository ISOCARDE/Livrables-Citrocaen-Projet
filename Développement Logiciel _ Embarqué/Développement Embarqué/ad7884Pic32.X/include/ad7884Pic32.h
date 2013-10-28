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
* @brief Configuration liaison SPI cot� MCU
*
* @param chSPI : canal SPI utilis�
* @param freq : d�bit voulu
* @return 1 si la configuration est r�ussi, 0 sinon
*/
Handle ad7884Pic32Open(chSPI, freq);


/**
* @fn void ad7634Pic32Read(Handle, chSPI, pData, SlaveS)
* @brief Configuration liaison SPI cot� MCU
*
* @param Handle : Permet de v�rifier si la configuration SPI cot� MCU est bien r�alis�e
* @param chSPI : canal SPI utili�
* @param pData : pointeur qui r�cup�re les donn�es
* @param SlaveS : broche /SS utilis�e
*/
void ad7884Pic32Read(Handle, chSPI, pData, SlaveS);

/**
* @fn ad7634Pic32Close(Handle, chSPI)
* @brief ferme le canal SPI utils�
*
* @param Handle : Permet de v�rifier si la configuration SPI cot� MCU est bien r�alis�e
* @param chSPI : canal SPI � fermer
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