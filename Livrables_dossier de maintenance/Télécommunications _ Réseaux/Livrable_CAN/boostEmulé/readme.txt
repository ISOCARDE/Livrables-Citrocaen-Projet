EmulateurBoost.X

Ce dossier contient les fichiers sources et le fichier pr�-compil� en .hex
du module boost le plus avanc� � l'heure actuelle. C'est-�-dire qu'il comprend
la gestion des LED qui indiquent la pr�sence ou non d'un boost converter,
l'interface shell via la communication s�rie RS-232 et ses commandes associ�es,
la communication CAN c�t� boost, c'est-�-dire en tant que serveur qui se
contente d'envoyer les valeurs int�ressante du boost converter et de respecter
la consigne envoy�e par le superviseur. Ce module boost n'�mulant que le boost
converter, la consigne se contente de modifier la sortie PWM auquelle sera connect�e
le boost converter par la suite. A noter que les valeurs renvoy�es de Vi et Vil
sont approxim�s et la valeur de sortie Vo est calcul� par la fonction de
transfert et le r�gulateur associ� du boost converter.

Remarque: le boost utilise le CAN2 sur les plateforme OLIMEX MAXI-WEB.

Remarque2: c'est la LED 2 verte qui indique la pr�sence ou non d'un boost converter
branch� sur le module boost.

Remarque3: la vitesse par d�faut sur le port serial est de 115200 bauds


Les fichiers sources ne n�cessitent pas de libraries particuli�res pour �tre
compil�s.
Les fichiers ont �t� cod�s/compil�s sur MPLAB X v1.60 avec le compiler toolchain
XC32 v1.20