/**
* @file interfaceShell.c
* @brief Création de l'interface Shell
* IDE MPLAB X vs Beta 7.02
* Compilateur XC32 vs 2.0
* @author VINCENT Simon / Isocarde
* http://www.isocarde.fr.ht
* @version 0.1
* @date 1 Novembre 2013
*/

/*** INCLUDES *****************************************************************/
#include "main.h"

/**
 * @fn void ShellInit()
 * @brief Configuration codec audio TLV320AIC23 via liaison SPI
 */
void ShellInit(){

    unsigned char * initStr ="\r"
    " ****** * * ******* ******      ***    ******    **    ****** ***   ***"
    "\n\r*  **** * * *** *** * *** *    *   *  *  ****   *  *   * **** *  *  * "
    "*\n\r* *     * *   * *   * *** *   *  *  * * *      * ** *  * *    * * * *"
    " *\n\r* *     * *   * *   * ** *    * *** * * *     * **** * * ***  * ** *"
    "* *\n\r* *     * *   * *   * * * *   *  *  * * *     * *  * * * *    * * *"
    " * *\n\r*  **** * *   * *   * *  * *   *   *  *  **** * *  * * * **** * * "
    " *  *\n\r ****** * *   * *   * *   * *   ***    ****** * *  * * ****** * *"
    "   * *\n\r"
    "citrocaen corp. with isocarde partnership\n\r"
    "boost converter module interface. Enter help to know the supported command"
    "s\n\r"
    ;
    helpStr = "\n\rauto        start automatic mode and stop manual"
    " mode\n\r            udapte voltage reference value with ref command\rmanu"
    "al      start manual mode and stop automatic mode\n\r            udapte du"
    "ty cycle value with pwm command\n\rref         udapteoutput voltage refere"
    "nce value\n\rpwm         udapte duty cycle value\n\rmeas        print curr"
    "ent analog values\n\rcan         print can controller configuration\n\rfil"
    "ter      udapte can filter\n\rhelp        print supported commands\n\r";

     k = 0;
     algo=1;
//    filter[0]= 'F';
//    filter[1]= 'F';
//    filter[2]= 'A';
//    Vil = 5.5;;
//    Vo=12.9;
//    Vi=5.7;
    IsCmd =1;                    //Permet de definir si on entre une commande
    histCmd= 0;
    ref=24;

    putUartStr(initStr);
}

/**
 * @fn void Prompt()
 * @brief Affiche le Prompt
 */
void Prompt(){

    unsigned char prmpt[9] = "boost:~# ";
    int i;

    for(i=0;i<9;i++)
        putUartC(prmpt[i]);

}

/*
 * @fn void shell(void)
 * @brief gère l'interface shell
 */
void shell(){

    int j;

    if (Cmd[k-1]=='\r'){
        if (IsCmd){

            //HELP
            if (Cmd[0]=='h' && Cmd[1]=='e' && Cmd[2]=='l' && Cmd[3]=='p' &&
                    Cmd[4]=='\r'){
                putUartStr(helpStr);

                // On affiche le prompt après chaque commande
                Prompt();
            }

            //AUTO
            else if (Cmd[0]=='a' && Cmd[1]=='u' && Cmd[2]=='t' && Cmd[3]=='o' &&
                    Cmd[4]=='\r'){
                algo=1;
                putUartStr("\n\rautomatic mode is running\n\r");

                // On affiche le prompt après chaque commande
                Prompt();
            }

            //MANUAL
            else if (Cmd[0]=='m' && Cmd[1]=='a' && Cmd[2]=='n' && Cmd[3]=='u' &&
                    Cmd[4]=='a' && Cmd[5]=='l' && Cmd[6]=='\r'){
                algo=0;
                Pwm=0;
                putUartStr("\n\rpwm mode is running\n\r");

                // On affiche le prompt après chaque commande
                Prompt();
            }

            //REF
            else if (Cmd[0]=='r' && Cmd[1]=='e' && Cmd[2]=='f' && Cmd[3]=='\r'){

                IsCmd=0;

                histCmd='r';

                if (algo==0)
                    putUartStr("\n\r/!\\ warning: pwm mode is running /!\\");

                putUartStr("\n\renter desired output voltage value : 18 or 24 or 30"
                        " or 36 (V)\n\r");
            }

            //PWM
            else if (Cmd[0]=='p' && Cmd[1]=='w' && Cmd[2]=='m' && Cmd[3]=='\r'){

                IsCmd=0;

                histCmd='p';

                if (algo)
                    putUartStr("\n\r/!\\ warning: automatic mode is running /!\\");

                putUartStr("\n\renter duty cycle value between 0 and 100 :\n\r");

            }

            //MEAS
            else if (Cmd[0]=='m' && Cmd[1]=='e' && Cmd[2]=='a' && Cmd[3]=='s' &&
                    Cmd[4]=='\r'){

                snprintf(IlC,5, "%f", lCurrent(Vil,Vi));
                snprintf(VoC,5, "%f", Vo);
                snprintf(ViC,5, "%f", Vi);

                putUartStr("\n\rcurent analog values:\n\r"
                        "Il=");
                putUartStr(IlC);
                putUartStr("mA\n\rVo=");
                putUartStr(VoC);
                putUartStr("V\n\rVi=");
                putUartStr(ViC);
                putUartStr("V\r\n");

                // On affiche le prompt après chaque commande
                Prompt();
            }

            //CAN
            else if (Cmd[0]=='c' && Cmd[1]=='a' && Cmd[2]=='n' && Cmd[3]=='\r'){
                putUartStr("\n\rcan controller configuration :\n\r"
                        "bus speed   250000 bps\n\r"
                        "data length 8 bytes\n\r"
                        "filter      0x");
                snprintf(filter,4,"%x",filtreBoost);
                if (filtreBoost<256){
                    if (filtreBoost<16)
                        putUartStr("00");
                    else
                        putUartStr("0");
                }
                putUartStr(filter);
                putUartStr("\n\rfilter mask 0xFFF\n\r");

                // On affiche le prompt après chaque commande
                Prompt();
            }

            //FILTER
            else if (Cmd[0]=='f' && Cmd[1]=='i' && Cmd[2]=='l' && Cmd[3]=='t' &&
                    Cmd[4]=='e' && Cmd[5]=='r' && Cmd[6]=='\r'){

                putUartStr("\n\rcommand filter not available with this CAN prot"
                        "ocol\n\r");
 /*             IsCmd=0;

                histCmd='f';

                putUartStr("\n\renter can filter value in hexadecimal (3 caracters)"
                        "\n\r");
*/
                // On affiche le prompt après chaque commande
                Prompt();
            }

            //touche entree
            else if (Cmd[0]=='\r'){
                putUartStr("\n\r");
                // On affiche le prompt après chaque commande
                Prompt();
            }

            //autres cas
            else{
                putUartStr("\n\rerror: enter help to know the supported commands"
                        "\n\r");

                // On affiche le prompt après chaque commande
                Prompt();
            }

        }

        // On attend que l'utilisateur entre une valeur
        else{

            //REF
            if(histCmd=='r'){

                if ((atoi(Cmd)==18 || atoi(Cmd)==24 || atoi(Cmd)==30
                        || atoi(Cmd)==36) && Cmd[2]=='\r'){
                    ref=atoi(Cmd);
                    putUartStr("\n\routput voltage value is updated\n\r");
                }
                else
                    putUartStr("\n\rerror: failed value\n\r");

                IsCmd=1;

                // On affiche le prompt après chaque commande
                Prompt();
            }

            //PWM
            else if(histCmd=='p'){

                if ((atoi(Cmd) >= 0) && (atoi(Cmd) <= 100)
                        && (Cmd[0]>='0') && (Cmd[0]<='9')
                        && ((Cmd[1]=='\r') || ((Cmd[1]>='0') && (Cmd[1]<='9')))
                        && ((Cmd[2]=='\r') || ((Cmd[2]>='0') && (Cmd[2]<='9'))
                        || (Cmd[2]==' '))
                        && (Cmd[3]=='\r' || Cmd[3]==' ')){
                    // /!\ fonction atoi ne detecte pas les erreurs
                    Pwm = atoi(Cmd);
                    putUartStr("\n\rthe duty cycle value is updated\n\r");
                }
                else
                    putUartStr("\n\rerror: failed value\n\r");

                IsCmd=1;

                // On affiche le prompt après chaque commande
                Prompt();
            }

/*            //FILTER
            else if(histCmd=='f'){

                if (((Cmd[0]>'/' && Cmd[0]<':') || (Cmd[0]>='A' && Cmd[0]<'G'))
                    && ((Cmd[1]>'/' && Cmd[1]<':') || (Cmd[1]>='A' && Cmd[1]<'G'))
                    && ((Cmd[2]>'/' && Cmd[2]<':') || (Cmd[2]>='A' && Cmd[2]<'G'))
                    && Cmd[3]=='\r'){

                    for(j=0;j<3;j++)
                        filter[j]=Cmd[j];

                    putUartStr("\r\ncan filter value is updated\r\n");
                }
                else if (((Cmd[0]>'/' && Cmd[0]<':') || (Cmd[0]>='a' && Cmd[0]<'g'))
                    && ((Cmd[1]>'/' && Cmd[1]<':') || (Cmd[1]>='a' && Cmd[1]<'g'))
                    && ((Cmd[2]>'/' && Cmd[2]<':') || (Cmd[2]>='a' && Cmd[2]<'g'))
                    && Cmd[3]=='\r'){

                    for(j=0;j<3;j++){
                        //Si c'est un chiffre
                        if (Cmd[j]<'a')
                                filter[j]=Cmd[j];
                        //Si c'est une lettre, on la convertit en majuscule
                        else
                            filter[j]=Cmd[j]-32;
                    }

                    putUartStr("\r\ncan filter value is updated\r\n");
                }
                else
                    putUartStr("\r\nerror: failed value\r\n");

                IsCmd=1;

                // On affiche le prompt après chaque commande
                Prompt();
            }
*/
            else
                IsCmd=1;

        }

            //On vide le tableau de caractère et on décrémente son indice
            while(k>0){
                Cmd[k]=' ';
                k--;
            }
            Cmd[0]=' ';
    }
}

/**
 * @fn float lCurrent(float, float)
 * @brief calcul le courant de l'inductence
 */
float lCurrent(float VI,float V){
    if (VI>V)
        return (VI-V)/(0.22/4+0.0298);
    else
        return (V-VI)/(0.22/4+0.0298);
}


