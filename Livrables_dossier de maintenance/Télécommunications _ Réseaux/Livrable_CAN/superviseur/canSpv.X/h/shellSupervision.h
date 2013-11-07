/**
* @file UartFonction.h
* @brief
* @author VINCENT Simon
* @version 0.1
* @date 28 octobre 2013
*/

#ifndef __SHELL_SUPERVISION__
#define __SHELL_SUPERVISION__

/* MACROS *********************************************************************/

#define MAX_STRING  20

/* GLOBALS*********************************************************************/

char Cmd[MAX_STRING];
int k;
unsigned char * helpStr;
//int eth; pas de mode wifi
float values[255][3];
//unsigned short tabBoostConnect[255][3];
float Vil;
short vo;
float Vo;
float Vi;
//char nbBoost;
unsigned char IPaddr[4];
unsigned char IP[20];
unsigned char Netmask[4];
unsigned char Net[20];
char VoEtoileC[10],IlC[10], VoC[10], ViC[10];
int IsCmd;                    //Permet de definir si on entre une commande
char histCmd;

/* FUNCTION PROTOTYPES ********************************************************/

/**
 * @fn void ShellInit()
 * @brief affiche le header du shell
 */
void ShellInit();


/**
 * @fn void Prompt()
 * @brief affiche le prompt
 */
void Prompt();

/**
 * @fn void shell()
 * @brief gère l'interface shell
 */
void shell();

/**
 * @fn float power(float, float)
 * @brief calcul la puissance d'entrée
 */
float power(float, float);

/**
 * @fn int outCurrent(float, float)
 * @brief calcul la puissance d'entrée
 */
int outCurrent(float, float);

/**
 * @fn float lCurrent(float, float)
 * @brief calcul le courant de l'inductence
 */
float lCurrent(float,float);

#endif