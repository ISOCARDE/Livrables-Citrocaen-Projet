/**
* @file ad7634Pic32Open.c
* @brief librairie SPI pour pilotage ADC externe AD7884
* @date 22/05/2012
* Librairie SPI pour pilotage ADC externe AD7884
*/

#include "../include/ad7884Pic32.h"

/**
* @fn handle ad7634Pic32Open(chSPI, freq)
* @brief Configuration liaison SPI coté MCU
*
* @param chSPI : canal SPI utilisé
* @param freq : débit voulu
* @return 1 si la configuration est réussi, 0 sinon
*/
Handle ad7884Pic32Open(chSPI CH, freq f){

	// SPI_OPEN_MODE32 : Données utiles formatées sur 32bits
	// SPI_OPEN_MSTEN : Mode maitre
	// Broches utilisées :
	// SPI_1 : (MISO) SDI=RC4, (MOSI) SDO=RD0, SCK=RD10
	SpiChnOpen(CH, SPI_OPEN_MODE16 | SPI_CON_SMP|SPI_CON_ON | SPI_OPEN_MSTEN, (SYS_FREQ/2)/f);

        return HANDLE_VALID;
}
