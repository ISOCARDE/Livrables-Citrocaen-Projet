%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%                BOOST CONVERTER               %%%%%%
%%%%%%            ISOCARDE / AUTOMATIQUE            %%%%%%
%%%%%%                 24/10/2013                   %%%%%%
%%%%%%            commande non lineaire             %%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all
close all
clc

RL = 0.0298;
RC = 0.5;
RS = 0.22;
L = 15e-6;
C = 9.4e-6;
R=100;
Vin = 12;

% coefficients
f11 = (-1/L)*(RL+RS/4);
b1 = Vin/L;
f22 = -1/(R*C);

g12 = -1/L;
g21 = 1/C;


