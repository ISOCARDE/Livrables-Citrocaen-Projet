/*******************************************************************************
* @file uart.c
* @brief gestion de l'UART pour communiquer entre le pic32 et le PC avec une liaison serie RS232
* @author Alain WERCK
* @date 11/02/2013
*******************************************************************************/

/*** INCLUDES *****************************************************************/

    #include <plib.h>
    //#include <stdlib.h>
    //#include <string.h>
    #include ".\h\timerFunctions.h"
    #include ".\h\gpio.h"

/*** CONFIG *******************************************************************/

// POSCMOD = XT (externe 3,5MHz-10MHz) ou HS (externe 10MHz-40MHz)
// PLL si FNOSC = PRIPLL
// CPUfreq = 8MHz   (ext. christal explorer 16) / FPLIDIV .
//                  doit être compris entre 4MHz < ? < 5MHz (datasheet)
// CPUfreq = ( (8MHz (ext. explorer 16) / FPLLIDIV) x FPLLMUL ) / FPLLODIV
// FPBDIV = DIV_2 pré-config de la freq du bus periph. MAJ en soft dans le code
    #pragma config FWDTEN=OFF, CP=OFF, POSCMOD=XT, FNOSC=PRIPLL
    #pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPLLODIV=DIV_1, FPBDIV=DIV_2

/*** MACROS *******************************************************************/

    //! Fréquence CPU
    #define SYS_FREQ    (80000000L)

    //! Fréquence UART
    #define UART_FREQ   (40000000L)

    //! Baudrate
    #define BAUDRATE    115200

/*** PROTOTYPES ***************************************************************/

unsigned char getUartC(void);
void putUartStr(unsigned char *ptString);
void putUartC(unsigned char keyCode);

/*** INTERRUPTS ***************************************************************/

/***************************************************************************//**
 * Vecteur d'interruption de l'UART1
 ******************************************************************************/
void __ISR(_UART1_VECTOR, ipl1) IntUart1Handler(void) {

    // Si on a reçu une donnée
    if (INTGetFlag(INT_SOURCE_UART_RX(UART1))) {

        // On la renvoie
        putUartC(getUartC());

        // Plus un message de confirmation
        putUartStr(" Succès !");

        // On baisse le flag
        INTClearFlag(INT_SOURCE_UART_RX(UART1));
    }

    // On ignore les interruptions sur TX
    if (INTGetFlag(INT_SOURCE_UART_TX(UART1)))
        INTClearFlag(INT_SOURCE_UART_TX(UART1));
}



//unsigned char receivedData = 'x';



/**
 * @fn unsigned char getUartC()
 * @brief reception d'un caractere envoyé sur le port serie
 */
unsigned char getUartC(){
    while(!UARTReceivedDataIsAvailable(UART1));
    return UARTGetDataByte(UART1);
}

/**
 * @fn void putUartC ( unsigned char keyCode )
 * @brief envoie d'un caractere au terminal du PC relie par liaison serie
 */
void putUartC(unsigned char keyCode){
    while(!UARTTransmitterIsReady(UART1));
    UARTSendDataByte(UART1, (BYTE) keyCode);
    while (!UARTTransmissionHasCompleted(UART1));
}

/**
 * @fn void putUartStr ( string keyCode )
 * @brief envoie d'une chaine de caractere au terminal du PC relie par liaison serie
 */
void putUartStr(unsigned char *ptString){
    int i=0;
    
    while(ptString[i]!='\0') {
        putUartC(ptString[i]);
        i++;
    }

    // retour a la ligne
    putUartC('\r');
    putUartC('\n');
}

/**
 * @fn void UART_Init (void)
 * @brief initialisation du module UART1
 */
void UART_Init(void) {

    // Mode de base
    UARTConfigure(UART1, UART_ENABLE_PINS_TX_RX_ONLY);

    // Configuration des interruptions
    UARTSetFifoMode(UART1, UART_INTERRUPT_ON_TX_NOT_FULL |
                            UART_INTERRUPT_ON_RX_NOT_EMPTY);

    // 8 bits de donnée, pas de parité, 1 bit de stop
    UARTSetLineControl(UART1,  UART_DATA_SIZE_8_BITS |
                                UART_PARITY_NONE |
                                UART_STOP_BITS_1);

    // Configuration baudrate
    UARTSetDataRate(UART1, UART_FREQ, BAUDRATE);

    // Activation UART en transmission et réception
    UARTEnable(UART1,  UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
    
    /*** Configuration de l'interruption associée à l'UART en réception (démasquage) ***/   
    INTEnable(INT_SOURCE_UART_RX(UART1), INT_ENABLED);

    /*** Set Interrupt priorities */
    INTSetVectorPriority(INT_VECTOR_UART(UART1), INT_PRIORITY_LEVEL_1);
    INTSetVectorSubPriority(INT_VECTOR_UART(UART1), INT_SUB_PRIORITY_LEVEL_0);
}

/**
* @fn void main (void)
* @brief point d'entrée du programme
*/
int main(void){

    //Optimisation du fonctionnement du CPU
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    // Désactivation du JTAG pour libérer des broches
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);
        
    // Initialisation
    UART_Init();
    initTimer1();
    initGPIO();

    // Activation des interruptions
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
    
    while(1){
        // clignotement de la LED1
        if(isOneSecondUp() == TRUE){
            if(LED1 == LED_ON)
                LED1 = LED_OFF;
            else LED1 = LED_ON;
        }
    }
}