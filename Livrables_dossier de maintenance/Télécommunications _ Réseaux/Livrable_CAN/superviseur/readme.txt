canSpv.X

Ce dossier contient les fichiers sources et le fichiers pr�-compil� en .hex
du superviseur le plus avanc� � l'heure actuelle. C'est-�-dire qu'il comprends
la gestion des LED en fontion d'un module boost (ou plusieurs) connect� ou non,
la gestion d'interface shell via liaison s�rie avec un PC,
la gestion du bus CAN c�t� superviseur, c'est-�-dire le module client sur le bus.

Remarque: le superviseur utilise le CAN1 sur les plateforme OLIMEX MAXI-WEB.

Remarque2: c'est la LED 2 verte qui indique la pr�sence ou non d'un boost.

Remarque3: la vitesse par d�faut sur le port serial est de 115200 bauds


Les fichiers sources ne n�cessitent pas de libraries particuli�res pour �tre
compil�s.
Les fichiers ont �t� cod�s/compil�s sur MPLAB X v1.60 avec le compiler toolchain
C32 v2.02
