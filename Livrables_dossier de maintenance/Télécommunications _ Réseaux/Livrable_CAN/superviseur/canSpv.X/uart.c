/**
* @file uart.c
* @brief gestion de l'UART 1
* @author Alain WERCK
* @date 25/10/2013
*/

/*** INCLUDES *****************************************************************/

    #include "includes.h"

/*** INTERRUPTS ***************************************************************/

/***************************************************************************//**
 * Vecteur d'interruption de l'UART1
 ******************************************************************************/
void __ISR(_UART1_VECTOR, ipl1) IntUart1Handler(void) {
    short i;

    // Si on a reçu une donnée
    if (INTGetFlag(INT_SOURCE_UART_RX(UART1))) {

        //On la stocke dans un tableau
        Cmd[k] = getUartC();

        // on affiche le caractère à l'écran
        putUartC(Cmd[k]);

        if(Cmd[k]==127){ // backspace OU suppr selon la config du terminal
            //efface le dernier caratère écrit dans le tableau
            if (k>0){
                Cmd[k]=' ';
                k--;
                putUartC('\r');
                if (IsCmd)
                    Prompt();
                for(i=0;i<k;i++)
                    putUartC(Cmd[i]);
                putUartStr(" \r");
                if (IsCmd)
                    Prompt();
                for(i=0;i<k;i++)
                    putUartC(Cmd[i]);
            }

        }
        else if(Cmd[k]=='\b'){ //backspace
            if (k>0){
                Cmd[k]=' ';
                putUartC(' ');
                putUartC('\b');
                k--;
            }
            else
                if(IsCmd){
                    putUartC('\r');
                    Prompt();
                }
        }
        else
            //On incrémente l'indice du tableau
            k++;

        // On baisse le flag
        INTClearFlag(INT_SOURCE_UART_RX(UART1));
    }

    // On ignore les interruptions sur TX
    if (INTGetFlag(INT_SOURCE_UART_TX(UART1)))
        INTClearFlag(INT_SOURCE_UART_TX(UART1));
}

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
    
    while(ptString[i] != '\0')
    {
        putUartC(ptString[i]);
        i++;
    }
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