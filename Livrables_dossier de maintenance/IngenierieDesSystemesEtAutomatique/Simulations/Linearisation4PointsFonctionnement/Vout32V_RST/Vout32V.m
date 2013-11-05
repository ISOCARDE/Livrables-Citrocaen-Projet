%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%                BOOST CONVERTER               %%%%%%
%%%%%%            ISOCARDE / AUTOMATIQUE            %%%%%%
%%%%%%                 24/10/2013                   %%%%%%
%%%%%%     Equation Electrique/seconde prise        %%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all
close all
clc

%Tension souhaitée en sortie
Vo=32;

% définition des variables
RL = 0.0298;
RC = 0.5;
RS = 0.22;
L = 15e-6;
C = 9.4e-6;
alpha = 0.5;      % rapport cyclique moyen


%%
    %fonctions de transfert lien la sortie en petit signal sur 
    %la commande (rapport cyclique)

%%%%%%%%%%%%%%%%%%%%%%paramètres pour le mode nominal
Vin = 12;
R = 100;

Gdo = (Vo*Vo)/Vin;
OmZ1 = 1/(RC*C);
OmZ2 = (R/L)*(Vin/Vo)*(Vin/Vo);
Om0 = (1/sqrt(L*C))*(Vin/Vo); f0 = Om0/(2*pi);
Q = Om0/((RL+RS/4)/L+1/(C*(R+RC)));

%fonction de transfert
B1 = conv([1/OmZ1 1],[-1/OmZ2 1]);
B = Gdo*B1;
A = [1/(Om0*Om0) 1/(Om0*Q) 1];

G_nominal = tf(B,A);

% figure
% pzmap(G_nominal)
% figure
% bode(G_nominal)

%%%%%%%%%%%%%%%%%%%%%%paramètres pour Vin = 9V, R = 60
Vin = 9;
R = 60;

Gdo = (Vo*Vo)/Vin;
OmZ1 = 1/(RC*C);
OmZ2 = (R/L)*(Vin/Vo)*(Vin/Vo);
Om0 = (1/sqrt(L*C))*(Vin/Vo); f0 = Om0/(2*pi);
Q = Om0/((RL+RS/4)/L+1/(C*(R+RC)));

%fonction de transfert
B1 = conv([1/OmZ1 1],[-1/OmZ2 1]);
B = Gdo*B1;
A = [1/(Om0*Om0) 1/(Om0*Q) 1];

G_conf1 = tf(B,A);

% figure
% pzmap(G_conf1)
% figure
% bode(G_conf1)


%%%%%%%%%%%%%%%%%%%%%%paramètres pour Vin = 9V, R = 240
Vin = 9;
R = 240;

Gdo = (Vo*Vo)/Vin;
OmZ1 = 1/(RC*C);
OmZ2 = (R/L)*(Vin/Vo)*(Vin/Vo);
Om0 = (1/sqrt(L*C))*(Vin/Vo); f0 = Om0/(2*pi);
Q = Om0/((RL+RS/4)/L+1/(C*(R+RC)));

%fonction de transfert
B12 = conv([1/OmZ1 1],[-1/OmZ2 1]);
B = Gdo*B1;
A = [1/(Om0*Om0) 1/(Om0*Q) 1];

G_conf2 = tf(B,A);

% figure
% pzmap(G_conf2)
% figure
% bode(G_conf2)

%%%%%%%%%%%%%%%%%%%%%%paramètres pour Vin = 18V, R = 60
Vin = 18;
R = 60;

Gdo = (Vo*Vo)/Vin;
OmZ1 = 1/(RC*C);
OmZ2 = (R/L)*(Vin/Vo)*(Vin/Vo);
Om0 = (1/sqrt(L*C))*(Vin/Vo); f0 = Om0/(2*pi);
Q = Om0/((RL+RS/4)/L+1/(C*(R+RC)));

%fonction de transfert
B1 = conv([1/OmZ1 1],[-1/OmZ2 1]);
B = Gdo*B1;
A = [1/(Om0*Om0) 1/(Om0*Q) 1];

G_conf3 = tf(B,A);

% figure
% pzmap(G_conf3)
% figure
% bode(G_conf3)

%%%%%%%%%%%%%%%%%%%%%%paramètres pour Vin = 18V, R = 240
Vin = 18;
R = 240;

Gdo = (Vo*Vo)/Vin;
OmZ1 = 1/(RC*C);
OmZ2 = (R/L)*(Vin/Vo)*(Vin/Vo);
Om0 = (1/sqrt(L*C))*(Vin/Vo); f0 = Om0/(2*pi);
Q = Om0/((RL+RS/4)/L+1/(C*(R+RC)));

%fonction de transfert
B1 = conv([1/OmZ1 1],[-1/OmZ2 1]);
B = Gdo*B1;
A = [1/(Om0*Om0) 1/(Om0*Q) 1];

G_conf4 = tf(B,A);

% figure
% pzmap(G_conf4)
% figure
% bode(G_conf4)


%%%%%%%%%%%%%%%% tracés
% figure 
% bode(G_nominal,G_conf1,G_conf2,G_conf3,G_conf4)
% legend('G_{nominal}','G_{conf1}','G_{conf2}','G_{conf3}','G_{conf4}');
% 
% figure 
% step(G_nominal*alpha,G_conf1*alpha,G_conf2*alpha,G_conf3*alpha,G_conf4*alpha)
% legend('G_{nominal}','G_{conf1}','G_{conf2}','G_{conf3}','G_{conf4}');

%% partie commande

% on considère que les résistances parasites des capacités sont
% négligeables
Vin = 18;
R = 240;

Gdo = (Vo*Vo)/Vin;
OmZ2 = (R/L)*(Vin/Vo)*(Vin/Vo);
Om0 = (1/sqrt(L*C))*(Vin/Vo); f0 = Om0/(2*pi);
Q = Om0/((RL+RS/4)/L+1/(C*(R)));

%fonction de transfert
B = Gdo*[-1/OmZ2 1];
A = [1/(Om0*Om0) 1/(Om0*Q) 1];

G_nominal_commande =  tf(B,A);

%%%% réglages correcteur, commande prédictive
w_reg=10000; %pulsation naturelle dominante en regulation
mu=20
Te=1/(500000);

[reg,Rn,Rd,Rp,Pc]=calculregulateur(B,A,w_reg,mu);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Definition de la fonction de transfert du système bouclé 
A_R1=conv(A,Rd);
F1=tf(A_R1,Pc);
 
figure(2);
pzmap(F1)
title('Position des pôles et des zéros de la Fonction de Transfert : Y/Vy');

figure(3);
bode(F1)
title('Bode de Y/Vy');

figure(4);
F1_2 = tf(Rn,Rd)
bode(F1_2)
title('Bode de U/Uy');
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    
[Rn_tf,Rd_tf,Rp_tf]= mise_en_oeuvre2(Rn,Rd,Rp);

consigne_bf=1;
bruit_bf = 0;
pertu_sortie_bf=1;
pertu_entree_bf=0;



