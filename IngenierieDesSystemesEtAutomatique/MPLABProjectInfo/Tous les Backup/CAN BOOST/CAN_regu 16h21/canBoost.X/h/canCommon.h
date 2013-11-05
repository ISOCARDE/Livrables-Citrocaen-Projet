/**
* @file CANFunctions.h
* @brief gestion de la com CAN
* @author Alain WERCK
* @date 25/10/2013
*/

#ifndef _CAN_FUNCTIONS_H_
#define _CAN_FUNCTIONS_H_

#define CAN_BUS_SPEED   250000 // on desire une vitesse de 500Kbps sur le bus (voir rapport pour le calcul)

#define CAN_FILTRE_INVIT        0b11111111111
#define CAN_FILTRE_DEMARRAGE    0b11100000000
#define CAN_NOMBRE_MODULES_POSSIBLES    255   // jusqu'a 255 !!!
#define CAN_FILTRE_MAX                  CAN_FILTRE_DEMARRAGE+CAN_NOMBRE_MODULES_POSSIBLES

#define CAN_BOOST       CAN2
#define INT_CAN         INT_CAN2
#define INT_CAN_VECTOR  INT_CAN_2_VECTOR

#endif
