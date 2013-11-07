canSpv.X

Ce dossier contient les fichiers sources et le fichiers pré-compilé en .hex
du superviseur le plus avancé à l'heure actuelle. C'est-à-dire qu'il comprends
la gestion des LED en fontion d'un module boost (ou plusieurs) connecté ou non,
la gestion d'interface shell via liaison série avec un PC,
la gestion du bus CAN côté superviseur, c'est-à-dire le module client sur le bus.

Remarque: le superviseur utilise le CAN1 sur les plateforme OLIMEX MAXI-WEB.

Remarque2: c'est la LED 2 verte qui indique la présence ou non d'un boost.

Remarque3: la vitesse par défaut sur le port serial est de 115200 bauds


Les fichiers sources ne nécessitent pas de libraries particulières pour être
compilés.
Les fichiers ont été codés/compilés sur MPLAB X v1.60 avec le compiler toolchain
C32 v2.02
