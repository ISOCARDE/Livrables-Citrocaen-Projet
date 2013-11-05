//
//
///*
// * File:   timerPwm.h
// * Author: Vincent
// *
// * Created on 28 octobre 2013, 02:01
// */
//
///*** INCLUDES *****************************************************************/
//#include "timer3.h"
//
///*** INTERRUPTS ***************************************************************/
///***************************************************************************//**
// * Vecteur d'interruption du timer 2
// ******************************************************************************/
//__ISR(_TIMER_4_VECTOR, ipl2) Timer4Handler(void) {
//
//    // On baisse le flag
//    mT3ClearIntFlag();
//
//    //mPORTAToggleBits( BIT_1 );
//    // Début de traitement
//    if ( rapportCyclique = 0.4 )
//         rapportCyclique = 0.5;
//    else if( rapportCyclique = 0.5 )
//        rapportCyclique = 0.5;
//
//}
///*** FUNCTIONS ****************************************************************/
///***************************************************************************//**
// * Configuration du timer 2
// ******************************************************************************/
//void timer3Init(void) {
//    OpenTimer4( T4_ON | T4_SOURCE_INT | T4_PS_1_1, T4_TICK  );
//
//    //PORTSetPinsDigitalOut(IOPORT_A, BIT_1 ); // Definition des sorties
//
//   // PORTClearBits(IOPORT_A, BIT_1); // Initialisation ? 0 les portes
//
//
//}
//
///***************************************************************************//**
// * Configuration des interruptions associées au timer 3
// ******************************************************************************/
//void timer3IntConfig(void) {
//    // PWM a une priorité de 2,
//    // car il est vital qu'il soit traité immédiatement
//     ConfigIntTimer4( T4_INT_ON | T4_INT_PRIOR_2 );
//}
//
