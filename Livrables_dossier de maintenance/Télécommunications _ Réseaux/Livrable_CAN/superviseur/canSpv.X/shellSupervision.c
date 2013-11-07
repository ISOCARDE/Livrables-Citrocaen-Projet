/**
* @file shellSupervision.c
* @brief Corps des fonctions de l'interface shell et de calcul de valeur
* électrique de la puissance et du courant
* @author VINCENT Simon
* @firm ISOCARDE?
* @version 0.1
* @date 02 octobre 2013
*/

/*** INCLUDES *****************************************************************/

#include "includes.h"

/* GLOBALS*********************************************************************/



/**
 * @fn void ShellInit()
 * @brief affiche le header du shell et initialise les variables globales
 */
void ShellInit(){
    
    k=0;
    helpStr = /*"\n\reth         start ethernet mode an stop wifi mode\r\nwifi "
            "       start wifi mode and stop ethernet mode"*/ //pas de mode wifi
            "\r\nip          udapte "
            "ip value for ethernet module\r\nnetmask     udapte netmask value f"
            "or ethernet module\r\nconfig      print ip informations for runnin"
            "g mode\r\nlist        print informations about connected boost mod"
            "ules\r\nref         udapte output voltage reference value\n\rhelp "
            "       print supported commands\r\n";
    //eth=1; pas de mode wifi
    IsCmd=1;                    //Permet de definir si on entre une commande
    histCmd = 0;
    
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
    "boost converter supervision module interface. Enter help to know the suppo"
    "rted commands\n\r"
    ;

    putUartStr(initStr);
}

/**
 * @fn void Prompt()
 * @brief affiche le prompt
 */
void Prompt(){

    unsigned char prmpt[9] = "boost:~# ";
    int i;

    for(i=0;i<9;i++)
        putUartC(prmpt[i]);

}

/**
 * @fn void shell(void)
 * @brief gère l'interface shell
 */
void shell(){

    int j;
    int pt1,pt2,pt3,cr;
    int error=0;
    unsigned char ip1[3],ip2[3],ip3[3],ip4[3];
    unsigned char noBoostC[4];
    unsigned char PiC[10],IoC[10];

    if (Cmd[k-1]=='\r'){
        if (IsCmd){

            //HELP
            if (Cmd[0]=='h' && Cmd[1]=='e' && Cmd[2]=='l' && Cmd[3]=='p' &&
                    Cmd[4]=='\r'){
                putUartStr(helpStr);

                // On affiche le prompt après chaque commande
                Prompt();
            }

/*
            //ETH
            else if (Cmd[0]=='e' && Cmd[1]=='t' && Cmd[2]=='h' && Cmd[3]=='\r'){
                eth=1;
                putUartStr("\n\rethernet mode is running\n\r");

                // On affiche le prompt après chaque commande
                Prompt();
            }

            //WIFI
            else if (Cmd[0]=='w' && Cmd[1]=='i' && Cmd[2]=='f' && Cmd[3]=='i'
                    && Cmd[4]=='\r'){
                eth=0;
                putUartStr("\n\rwifi mode is running\n\r");

                // On affiche le prompt après chaque commande
                Prompt();
            }

*/          // pas de mode wifi

            //IP
            else if (Cmd[0]=='i' && Cmd[1]=='p' && Cmd[2]=='\r'){

                IsCmd=0;

                histCmd='i';

  //              if (algo==0)
  //                  putUartStr("\n\r/!\\ warning: pwm mode is running /!\\");

                putUartStr("\n\rudapte ip value for ethernet module (?.?.?.?) :"
                        "\n\r");
            }

            //NETMASK
            else if (Cmd[0]=='n' && Cmd[1]=='e' && Cmd[2]=='t' && Cmd[3]=='m'
                    && Cmd[4]=='a' && Cmd[5]=='s' && Cmd[6]=='k'
                    && Cmd[7]=='\r'){

                IsCmd=0;

                histCmd='n';

 //               if (algo)
 //                   putUartStr("\n\r/!\\ warning: automatic mode is running /!\\");

                putUartStr("\n\rudapte netmask value for ethernet module (?.?.?"
                        ".?) :\n\r");

            }

            //CONFIG
            else if (Cmd[0]=='c' && Cmd[1]=='o' && Cmd[2]=='n' && Cmd[3]=='f'
                    && Cmd[4]=='i' && Cmd[5]=='g' && Cmd[6]=='\r'){

                // !!!! AJOUT PRECISION
                sprintf(IP, "%d.%d.%d.%d", IPaddr[0],IPaddr[1],IPaddr[2],
                        IPaddr[3]);
                sprintf(Net, "%d.%d.%d.%d",Netmask[0],Netmask[1],Netmask[2],
                        Netmask[3]);

                putUartStr("\n\rethernet module ip configuration :\n\r"
                        "ip          ");
                putUartStr(IP);
                putUartStr("\n\rnetmask     ");
                putUartStr(Net);
                putUartStr("\n\r");

                // On affiche le prompt après chaque commande
                Prompt();
            }

            //LIST
            else if (Cmd[0]=='l' && Cmd[1]=='i' && Cmd[2]=='s' && Cmd[3]=='t'
                    && Cmd[4]=='\r'){
                
                if(nbrBoostConnectes==0)
                    putUartStr("\n\rnone");
                else{
                        Nop();
                    //! conversion des valeurs du tableau des boosts
//                    float * tabDesVo;
//                    tabDesVo = convertTabBoostConnectes(VO);
//                    float * tabDesVi;
//                    tabDesVi = convertTabBoostConnectes(VI);
//                    float * tabDesVil;
//                    tabDesVil = convertTabBoostConnectes(VIL);


                    for(j=0;j<CAN_NOMBRE_MODULES_POSSIBLES;j++){
                        if(tabBoostConnectes[j][0]==0)
                        {
                            Nop();
                        } else
                        {
                            // recuperation des valeurs
                            float valDeVoEtoile = convertTabBoostConnectes(j,VOETOILE);
                            float valDeVo = convertTabBoostConnectes(j,VO);
                            float valDeVi = convertTabBoostConnectes(j,VI);
                            float valDeVil = convertTabBoostConnectes(j,VIL);

                            // calcul et mise en format ASCII
                            sprintf(noBoostC, "%d", j);                                         // n° du boost affiché
                            snprintf(VoEtoileC,5,"%f",valDeVoEtoile);
                            snprintf(ViC,5, "%f",valDeVi);                                      // Vi = ? V
                            float valIlC = lCurrent(valDeVil,valDeVi);
                            snprintf(IlC,10, "%f",valIlC);                                      // Il = ? A
                            snprintf(PiC,6, "%f",power( valDeVi,lCurrent(valDeVil,valDeVi)));   // Pi = ? W
                            snprintf(VoC,5, "%f",valDeVo*10);                                   // Vo = ? V
                            sprintf(IoC, "%d",outCurrent(valDeVo*10,power(valDeVi,lCurrent(valDeVil,valDeVi))));// Io = ? mA

                            // affichage sur l'interface shell
                            putUartStr("\n\rboost");
                            putUartStr(noBoostC);
                            putUartStr("      Vo*=");
                            putUartStr(VoEtoileC);
                            putUartStr("V Vi=");
                            putUartStr(ViC);
                            putUartStr("V Il=");
                            putUartStr(IlC);
                            putUartStr("A Pi=");
                            putUartStr(PiC);
                            putUartStr("W Vo=");
                            putUartStr(VoC);
                            putUartStr("V Io=");
                            putUartStr(IoC);
                            putUartStr("mA (rendement#1)");
                        }
                    }
                }
                putUartStr("\r\n");

                // On affiche le prompt après chaque commande
                Prompt();
            }

            //REF
            else if (Cmd[0]=='r' && Cmd[1]=='e' && Cmd[2]=='f' && Cmd[3]=='\r'){
                
                if(nbrBoostConnectes==0){
                    putUartStr("\n\rno boost converter connected\n\r");
                    Prompt();
                }

                else{
                    IsCmd=0;
                    histCmd='b';
                    putUartStr("\n\renter number of desired boost converter :\n\r");
                }
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
            if(histCmd=='b'){
                
                if((atoi(Cmd)>=0 && atoi(Cmd)<CAN_NOMBRE_MODULES_POSSIBLES) &&
                        (Cmd[0]>='0' && Cmd[0]<='9') &&
                        ((Cmd[1]>='0' && Cmd[1]<='9') || Cmd[1]=='\r') &&
                        ((Cmd[2]>='0' && Cmd[2]<='4') || Cmd[2]=='\r' ||
                        Cmd[2]==' ')
                        ){

                    adrConsigne=atoi(Cmd)+CAN_FILTRE_DEMARRAGE;
                    histCmd='r';
                    //IsCmd=0;
                    putUartStr("\n\renter desired output voltage value : 18 or 24 or 30"
                        " or 36 (V)\n\r");
                    
                }
                else{

                    putUartStr("\n\rerror: failed value\n\r");
                    IsCmd=1;
                    // On affiche le prompt après chaque commande
                    Prompt();
                }
                
                
            }
            
            else if(histCmd=='r'){

                if ((atoi(Cmd)==18) && Cmd[2]=='\r'){
                    valConsigne = 1;
                    consigneToSend = 1;
                    putUartStr("\n\routput voltage value is updated\n\r");
                }
                else if(atoi(Cmd)==24 && Cmd[2]=='\r'){
                    valConsigne = 2;
                    consigneToSend = 1;
                    putUartStr("\n\routput voltage value is updated\n\r");
                }
                else if(atoi(Cmd)==30 && Cmd[2]=='\r'){
                    valConsigne = 3;
                    consigneToSend = 1;
                    putUartStr("\n\routput voltage value is updated\n\r");
                }
                else if(atoi(Cmd)==36 && Cmd[2]=='\r'){
                    valConsigne = 4;
                    consigneToSend = 1;
                    putUartStr("\n\routput voltage value is updated\n\r");
                }
                else
                    putUartStr("\n\rerror: failed value\n\r");

                IsCmd=1;
                // On affiche le prompt après chaque commande
                Prompt();
            }

            //IP
            if(histCmd=='i'){
                
                error=0;

                // On vérifie la position du premier point
                for(j=0;j<4;j++){
                    if (Cmd[j]=='.'){
                        if (j==0){
                            error=1;
                        }
                        else{
                            pt1=j;
                        }
                        break;
                    }
                    else{
                        if (j==3){
                            error=1;
                            pt1=j;
                            break;
                        }
                    }
                }
                
                // On vérifie la position du deuxieme point
                for(j=pt1+1;j<pt1+5;j++){
                    if(error)
                        break;
                    else{
                        if (Cmd[j]=='.'){
                            if (j==pt1+1){
                                error=1;
                            }
                            else{
                                pt2=j;
                            }
                            break;
                        }
                        else{
                            if (j==pt1+4){
                                error=1;
                                pt2=j;
                                break;
                            }
                        }
                    }                    
                }

                // on verifie la position du troisieme point
                for(j=pt2+1;j<pt2+5;j++){
                    if(error)
                        break;
                    else{
                        if (Cmd[j]=='.'){
                            if (j==pt2+1){
                                error=1;
                            }
                            else{
                                pt3=j;
                            }
                            break;
                        }
                        else{
                            if (j==pt2+4){
                                error=1;
                                pt3=j;
                                break;
                            }
                        }
                    }
                }

                // on verifie la position du retour à la ligne (entrée)
                for(j=pt3+1;j<pt3+5;j++){
                    if(error)
                        break;
                    else{
                        if (Cmd[j]=='\r'){
                            if (j==pt3+1){
                                error=1;
                            }
                            else{
                                cr=j;
                            }
                            break;
                        }
                        else{
                            if (j==pt3+4){
                                error=1;
                                break;
                            }
                        }
                    }
                }

                if(error){
                    putUartStr("\n\rerror: failed value\n\r");
                }

                else{

                    // On verifie que les caractères entre les points soient des chiffres
                    for(j=0;j<pt1;j++){
                        if ((Cmd[j]>='0') && (Cmd[j]<='9'))
                            ip1[j]=Cmd[j];
                        else{
                            error=1;
                            break;
                        }
                    }
                    for(j=pt1+1;j<pt2;j++){
                        if (error)
                            break;
                        else{
                            if ((Cmd[j]>='0') && (Cmd[j]<='9'))
                                ip2[j-(pt1+1)]=Cmd[j];
                            else{
                                error=1;
                                break;
                            }
                        }
                    }
                    for(j=pt2+1;j<pt3;j++){
                        if (error)
                            break;
                        else{
                            if ((Cmd[j]>='0') && (Cmd[j]<='9'))
                                ip3[j-(pt2+1)]=Cmd[j];
                            else{
                                error=1;
                                break;
                            }
                        }
                    }
                    for(j=pt3+1;j<cr;j++){
                        if (error)
                            break;
                        else{
                            if ((Cmd[j]>='0') && (Cmd[j]<='9'))
                                ip4[j-(pt3+1)]=Cmd[j];
                            else{
                                error=1;
                                break;
                            }
                        }
                    }

                    if(error){
                        putUartStr("\n\rerror: failed value\n\r");
                    }

                    // on verifie que chaque entre-point est entre 0 et 255
                    else if((atoi(ip1) >= 0) && (atoi(ip1) <= 255)
                            && (atoi(ip2) >= 0) && (atoi(ip2) <= 255)
                            && (atoi(ip3) >= 0) && (atoi(ip3) <= 255)
                            && (atoi(ip4) >= 0) && (atoi(ip4) <= 255)){
                        IPaddr[0]=atoi(ip1);
                        IPaddr[1]=atoi(ip2);
                        IPaddr[2]=atoi(ip3);
                        IPaddr[3]=atoi(ip4);
                        putUartStr("\n\rip value is updated\n\r");
                    }
                    else
                        putUartStr("\n\rerror: failed value\n\r");
                }

                IsCmd=1;

                // On affiche le prompt après chaque commande
                Prompt();
            }

            //NETMASK
            else if(histCmd=='n'){

                error=0;

                // On vérifie la position du premier point
                for(j=0;j<4;j++){
                    if (Cmd[j]=='.'){
                        if (j==0){
                            error=1;
                        }
                        else{
                            pt1=j;
                        }
                        break;
                    }
                    else{
                        if (j==3){
                            error=1;
                            pt1=j;
                            break;
                        }
                    }
                }

                // On vérifie la position du deuxieme point
                for(j=pt1+1;j<pt1+5;j++){
                    if(error)
                        break;
                    else{
                        if (Cmd[j]=='.'){
                            if (j==pt1+1){
                                error=1;
                            }
                            else{
                                pt2=j;
                            }
                            break;
                        }
                        else{
                            if (j==pt1+4){
                                error=1;
                                pt2=j;
                                break;
                            }
                        }
                    }
                }

                // on verifie la position du troisieme point
                for(j=pt2+1;j<pt2+5;j++){
                    if(error)
                        break;
                    else{
                        if (Cmd[j]=='.'){
                            if (j==pt2+1){
                                error=1;
                            }
                            else{
                                pt3=j;
                            }
                            break;
                        }
                        else{
                            if (j==pt2+4){
                                error=1;
                                pt3=j;
                                break;
                            }
                        }
                    }
                }

                // on verifie la position du retour à la ligne (entrée)
                for(j=pt3+1;j<pt3+5;j++){
                    if(error)
                        break;
                    else{
                        if (Cmd[j]=='\r'){
                            if (j==pt3+1){
                                error=1;
                            }
                            else{
                                cr=j;
                            }
                            break;
                        }
                        else{
                            if (j==pt3+4){
                                error=1;
                                break;
                            }
                        }
                    }
                }

                if(error){
                    putUartStr("\n\rerror: failed value\n\r");
                }

                else{

                    // On verifie que les caractères entre les points soient des chiffres
                    for(j=0;j<pt1;j++){
                        if ((Cmd[j]>='0') && (Cmd[j]<='9'))
                            ip1[j]=Cmd[j];
                        else{
                            error=1;
                            break;
                        }
                    }
                    for(j=pt1+1;j<pt2;j++){
                        if (error)
                            break;
                        else{
                            if ((Cmd[j]>='0') && (Cmd[j]<='9'))
                                ip2[j-(pt1+1)]=Cmd[j];
                            else{
                                error=1;
                                break;
                            }
                        }
                    }
                    for(j=pt2+1;j<pt3;j++){
                        if (error)
                            break;
                        else{
                            if ((Cmd[j]>='0') && (Cmd[j]<='9'))
                                ip3[j-(pt2+1)]=Cmd[j];
                            else{
                                error=1;
                                break;
                            }
                        }
                    }
                    for(j=pt3+1;j<cr;j++){
                        if (error)
                            break;
                        else{
                            if ((Cmd[j]>='0') && (Cmd[j]<='9'))
                                ip4[j-(pt3+1)]=Cmd[j];
                            else{
                                error=1;
                                break;
                            }
                        }
                    }

                    if(error){
                        putUartStr("\n\rerror: failed value\n\r");
                    }

                    // on verifie que la valeur du netmask est possible
                    else if((((atoi(ip1) == 128) || (atoi(ip1) == 192) ||
                            (atoi(ip1) == 224) || (atoi(ip1) == 240) ||
                            (atoi(ip1) == 248) || (atoi(ip1) == 252) ||
                            (atoi(ip1) == 254) || (atoi(ip1) == 255)) &&
                            (atoi(ip2) == 0) && (atoi(ip3) == 0) &&
                            (atoi(ip4) == 0)) ||
                            (((atoi(ip2) == 128) || (atoi(ip2) == 192) ||
                            (atoi(ip2) == 224) || (atoi(ip2) == 240) ||
                            (atoi(ip2) == 248) || (atoi(ip2) == 252) ||
                            (atoi(ip2) == 254) || (atoi(ip2) == 255)) &&
                            (atoi(ip1) == 255) && (atoi(ip3) == 0) &&
                            (atoi(ip4) == 0)) ||
                            (((atoi(ip3) == 128) || (atoi(ip3) == 192) ||
                            (atoi(ip3) == 224) || (atoi(ip3) == 240) ||
                            (atoi(ip3) == 248) || (atoi(ip3) == 252) ||
                            (atoi(ip3) == 254) || (atoi(ip3) == 255)) &&
                            (atoi(ip2) == 255) && (atoi(ip1) == 255) &&
                            (atoi(ip4) == 0)) ||
                            (((atoi(ip4) == 128) || (atoi(ip4) == 192) ||
                            (atoi(ip4) == 224) || (atoi(ip4) == 240) ||
                            (atoi(ip4) == 248) || (atoi(ip4) == 252) ||
                            (atoi(ip4) == 254) || (atoi(ip4) == 255)) &&
                            (atoi(ip2) == 255) && (atoi(ip3) == 255) &&
                            (atoi(ip1) == 255))
                            ){
                        Netmask[0]=atoi(ip1);
                        Netmask[1]=atoi(ip2);
                        Netmask[2]=atoi(ip3);
                        Netmask[3]=atoi(ip4);
                        putUartStr("\n\rnetmask value is updated\n\r");
                    }
                    else
                        putUartStr("\n\rerror: failed value\n\r");
                }

                IsCmd=1;

                // On affiche le prompt après chaque commande
                Prompt();
            }


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
 * @fn float power(float V, float I)
 * @brief calcul la puissance d'entrée
 */
float power(float V, float I) {
    return V*I;
}

/**
 * @fn int outCurrent(float V, float P)
 * @brief calcul du courant de sortie
 */
int outCurrent(float V,float P){
    return (int)(P*1000/V);
}

/**
 * @fn float lCurrent(float, float)
 * @brief calcul le courant de l'inductence
 */
float lCurrent(float VilCurrent,float V){
    if (VilCurrent>V){
        return (VilCurrent-V)/(0.22/4+0.0298);
    }
    else{
        return (V-VilCurrent)/(0.22/4+0.0298);
    }
}

