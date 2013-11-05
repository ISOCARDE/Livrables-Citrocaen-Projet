/**
* @file main.c
* @brief Programme de demonstration pour l'illustration des regles de
* codage C à l'ENSICAEN dans les enseignements de Systemes Embarques
* IDE MPLAB X vs Beta 7.02
* Compilateur C32 vs 2.0
* @author nom1 nom2 groupe promo
* @version 0.1
* @date 21 février 2012
*/

/* INCLUDES DEPENDENCIES ***************/
#include "headerTest.h"

/* CONFIGURATION BITS ***************/
#pragma config FWDTEN = OFF, CP = OFF, POSCMOD = XT, FNOSC = PRIPLL
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20, FPLLODIV = DIV_1, FPBDIV = DIV_2

/* MACROS ***************/
#define macroFunction(x, y)	\
			do { 			\
			if (x != 10) 	\
			y = 3; 			\
			} while (1)

/* GLOBAL VARIABLES ***************/
HandleAic23 hAic23;	

/**
* @fn void main (void)
* @brief point d'entree du programme
*/
int main(void){

    ConfigAic23    config = 0x56;
	char dataFromPc;
	
    // Configuration codec TLV320AIC23
    hAd7634 = aic23Pic32_open( &dataFromPc, config );

	// instructions uniques
	if (hAic23 != HANDLE_INVALID)
		instUnique1();
	else
		instUnique2();
		
	while (1) {
	
		// instructions multiples
		if (dataFromPc == 'T') {
			macroFunction(2, 5);		
		} else if (dataFromPc == 'F') {
			// ...
		} else {
			// ...
		}
	}
}

