EmulateurBoost.X

Ce dossier contient les fichiers sources et le fichier pré-compilé en .hex
du module boost le plus avancé à l'heure actuelle. C'est-à-dire qu'il comprend
la gestion des LED qui indiquent la présence ou non d'un boost converter,
l'interface shell via la communication série RS-232 et ses commandes associées,
la communication CAN côté boost, c'est-à-dire en tant que serveur qui se
contente d'envoyer les valeurs intéressante du boost converter et de respecter
la consigne envoyée par le superviseur. Ce module boost n'émulant que le boost
converter, la consigne se contente de modifier la sortie PWM auquelle sera connectée
le boost converter par la suite. A noter que les valeurs renvoyées de Vi et Vil
sont approximés et la valeur de sortie Vo est calculé par la fonction de
transfert et le régulateur associé du boost converter.

Remarque: le boost utilise le CAN2 sur les plateforme OLIMEX MAXI-WEB.

Remarque2: c'est la LED 2 verte qui indique la présence ou non d'un boost converter
branché sur le module boost.

Remarque3: la vitesse par défaut sur le port serial est de 115200 bauds


Les fichiers sources ne nécessitent pas de libraries particulières pour être
compilés.
Les fichiers ont été codés/compilés sur MPLAB X v1.60 avec le compiler toolchain
XC32 v1.20