/* 
 * File:   spi.c
 * Author: Vincent
 *
 * Created on 26 octobre 2013, 14:57
 */

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>

#pragma config FWDTEN=OFF, CP=OFF, POSCMOD=XT, FNOSC=PRIPLL
#pragma config FPLLIDIV=DIV_2, FPLLMUL=MUL_20, FPLLODIV=DIV_1, FPBDIV=DIV_2


/*** MACROS *******************************************************************/
   unsigned int sriClk = 3000000;  // d?bit voulu : 3Mb/s
   unsigned int sroClk = 40000000; // Frequence de travail du p?riph?riqe : 40MHz


    //! Fréquence CPU
    #define SYS_FREQ                    (80000000L)

    //! Fréquence UART
    #define UART_FREQ                   (40000000L)

    //! Baudrate
    #define BAUDRATE                    115200

    // Config slave select CS_IL => VIL
    #define slave_selectIL_active()       LATAbits.LATA4 = 0      // RA4 => TDI => JTAG (3)
    #define slave_selectIL_desactive()    LATAbits.LATA4 = 1

    // Config slave select CS_0 => VO
    #define slave_selectO_active()       LATAbits.LATA5 = 0      // RA5 => TDO => JTAG (5)
    #define slave_selectO_desactive()    LATAbits.LATA5 = 1

    // Config slave select CS_I => VI
    #define slave_selectI_active()       LATAbits.LATA0 = 0      // RA0 => TMS => JTAG (7)
    #define slave_selectI_desactive()    LATAbits.LATA0 = 1






int main(int argc, char** argv) {

    int i;
    unsigned int config;

    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL);

    // Désactivation du JTAG pour accéder aux PORTA
   // mJTAGPortEnable(DEBUG_JTAGPORT_OFF);

    config=SPI_OPEN_MODE16;    // SPI configuration PIC32
    config|=SPI_OPEN_ON;     // SPI périphérique est activé
    config|=SPI_OPEN_MSTEN;  // agit comme un maître de bus
    config|=SPI_OPEN_SMP_END;    // Données d'entrée échantillonnées à la fin du temps de sortie de données
    //config|=SPI_OPEN_FRMEN;  // le mode de tram est permis
    //config|=SPI_OPEN_FRMSYNC; //trame d'impulsion de synchronisation de sortie (mode Master)


    // SPI 1, Config des ports entrée/sortie, régle le débit binaire à 20MHz.
    SpiChnOpen(SPI_CHANNEL4, config, sroClk/sriClk);

    // Config slave select CS_IL => VIL
    PORTSetPinsDigitalOut(IOPORT_A, BIT_4);
    PORTSetBits(IOPORT_A, BIT_4);

    // Config slave select CS_0 => VO
    PORTSetPinsDigitalOut(IOPORT_A, BIT_5);
    PORTSetBits(IOPORT_A, BIT_5);

    // Config slave select CS_I => VI
    PORTSetPinsDigitalOut(IOPORT_A, BIT_0);
    PORTSetBits(IOPORT_A, BIT_0);


     // brochage module SPI4 :
    // SDI3 = RF4  => MISO3A => UEXT2 (7)
    // SDO3 = RF5  => MOSI3A => UEXT2 (8)  (envoi du pic32 vers l'adc)
    // SS3 = RF12  => AC1RX  
    // SCK3 = RF13  => UEXT2 (9)


     while(1) {

        //- mettre SS à 0
        //- lancer la transmission SPI
        //- mettre SS à 1

        // Gestion de /SS via GPIO
        // Envoi de caractère sur front descendant
        slave_selectIL_active();

        // Envoi
        // Envoi des données '11110000' sur le canal maître sur SPI1
        SpiChnPutC(SPI_CHANNEL4,0x00F0 );

        // On attend la fin de transmission
        // On attend la réception d'un caractère qui ne viendra jamais
        SpiChnGetC(SPI_CHANNEL4);

        // Fin de transmission
        slave_selectIL_desactive();

        // Temporisation software
        for (i=0; i<100; i++);
        
///////////////////////////////////////////////////////////////////////////////
               // Gestion de /SS via GPIO
        // Envoi de caractère sur front descendant
        slave_selectO_active();

        // Envoi
        // Envoi des données '11110000' sur le canal maître sur SPI1
        SpiChnPutC(SPI_CHANNEL4,0x00F0 );

        // On attend la fin de transmission
        // On attend la réception d'un caractère qui ne viendra jamais
        SpiChnGetC(SPI_CHANNEL4);

        // Fin de transmission
        slave_selectO_desactive();

/////////////////////////////////////////////////////////////////////////////
         // Temporisation software
        for (i=0; i<100; i++);

                // Gestion de /SS via GPIO
        // Envoi de caractère sur front descendant
        slave_selectI_active();

        // Envoi
        // Envoi des données '11110000' sur le canal maître sur SPI1
        SpiChnPutC(SPI_CHANNEL4,0x00F0 );

        // On attend la fin de transmission
        // On attend la réception d'un caractère qui ne viendra jamais
        SpiChnGetC(SPI_CHANNEL4);

        // Fin de transmission
        slave_selectI_desactive();


        // Temporisation software
        for (i=0; i<100; i++);
    }




    return (EXIT_SUCCESS);
}

