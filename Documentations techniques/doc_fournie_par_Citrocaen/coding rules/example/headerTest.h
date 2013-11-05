/**
* @file headerTest.h
* @brief Programme de demonstration pour l'illustration des regles de
* codage C à l'ENSICAEN dans les enseignements de Systemes Embarques
* IDE MPLAB X vs Beta 7.02
* Compilateur C32 vs 2.0
* @author nom1 nom2 groupe promo
* @version 0.1
* @date 21 février 2012
*/

#ifndef   __HEADER_TEST__
#define   __HEADER_TEST__

/* INCLUDES DEPENDENCIES ***************/
#include <p32xxxx.h>
#include <plib.h>


/* MACROS ***************/
#define SYS_FREQ  	80000000    /*Vitesse travail bus matrix et CPU*/
#define PB_DIV    	2			/*diviseur bus peripherique*/
                                /*Ne pas modifier qu'ici !*/
#define CONFIG_INVALID	0 
#define	HANDLE_INVALID	0	
#define	HANDLE_VALID	1	
								
															
/* DEFINITIONS ***************/
typedef unsigned int	HandleAic23;	// entier non signe sur 32bits
typedef unsigned int 	ConfigAic23; 	// entier non signe sur 32bits
	
/**
* @struct strDataCnv
* @brief Sauvegarde donnee apres conversion de l'AIC23. pointeur
* sur la zone memoire allouee dans le Tas et taille de la zone
*/
typedef struct {
        int buffSize
        int* allocCnvTab
} StrDataCnv;

/* EXTERNAL GLOBAL VARIABLES ***************/
extern ConfigAic23 configRestore;

		
/* FUNCTION PROTOTYPES ***************/

/**
 * @fn HandleAic23 aic23Pic32_open( char* returnData, 
 * ConfigAic23 configCodec );
 * @brief Configuration codec audio TLV320AIC23 via liaison SPI
 * @param returnData caractere representatif de l'etat de la configuration
 * @param  configCodec configuration du codec audio (cf. datasheet)
 * @return HANDLE_INVALID si echec de configuration
 */
 HandleAic23 aic23Pic32_open( char* returnData, ConfigAic23 configCodec );


#endif // fin __HEADER_TEST__
