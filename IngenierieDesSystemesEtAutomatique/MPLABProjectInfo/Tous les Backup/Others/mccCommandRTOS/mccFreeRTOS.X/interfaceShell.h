/**
* @file interfaceShell.h
* @brief Création de l'interface Shell
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author VINCENT Simon / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/
#ifndef INTERFACESHELL_H
#define	INTERFACESHELL_H

/*** DEFINE MACRO *************************************************************/
 #define MAX_STRING1  20

/*** GLOBAL VARIABLE **********************************************************/
char Cmd[MAX_STRING1];
int k; // = 0
unsigned char * helpStr; /* = "\n\rauto        start automatic mode and stop manual"
    " mode\n\r            udapte voltage reference value with ref command\rmalu"
    "al      start manual mode and stop automatic mode\n\r            udapte du"
    "ty cycle value with pwm command\n\rref         udapteoutput voltage refere"
    "nce value\n\rpwm         udapte duty cycle value\n\rmeas        print curr"
    "ent analog values\n\rcan         print can controller configuration\n\rfil"
    "ter      udapte can filter\n\rhelp        print supported commands\n\r";*/
int Pwm;
int ref;
int algo; //=1;
char filter[3]; //="FFA";
float Vil; //=10;
float Vo; //=12;
float Vi; //=5;
char IlC[10], VoC[10], ViC[10];
int IsCmd; // =1;                    //Permet de definir si on entre une commande
char histCmd ; //= 0;


/**
 * @fn void ShellInit()
 * @brief Configuration codec audio TLV320AIC23 via liaison SPI
 */
void ShellInit();

/**
 * @fn void Prompt()
 * @brief Affiche le Prompt
 */
void Prompt();

/*
 * @fn void shell(void)
 * @brief gère l'interface shell
 */
void shell();

/**
 * @fn float lCurrent(float, float)
 * @brief calcul le courant de l'inductence
 */
float lCurrent(float ,float );

#endif	/* INTERFACESHELL_H */

