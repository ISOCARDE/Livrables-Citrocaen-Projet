%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%                BOOST CONVERTER               %%%%%%
%%%%%%            ISOCARDE / AUTOMATIQUE            %%%%%%
%%%%%%                 24/10/2013                   %%%%%%
%%%%%%     Equation Electrique/seconde prise        %%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all
close all
clc

%Tension souhait�e en sortie
Vo_1 = 18;
Vo_2 = 24;
Vo_3 = 30;
Vo_4 = 36;

% d�finition des variables
RL = 0.0298;
RC = 0.5;
RS = 0.22;
L = 15e-6;
C = 9.4e-6;
alpha = 0.5;      % rapport cyclique moyen
Te = 0.00001;     % �quivaut � une fr�quence de 100kHz

%% Fonction de transfert pour Vo = 18V
Vin = 12;
R = 100;

Gdo_1 = (Vo_1*Vo_1)/Vin;
OmZ2_1 = (R/L)*(Vin/Vo_1)*(Vin/Vo_1);
Om0_1 = (1/sqrt(L*C))*(Vin/Vo_1); f0_1 = Om0_1/(2*pi);
Q_1 = Om0_1/((RL+RS/4)/L+1/(C*(R)));

%fonction de transfert
B_1 = Gdo_1*[-1/OmZ2_1 1];
A_1 = [1/(Om0_1*Om0_1) 1/(Om0_1*Q_1) 1];

% A_reel = [1 -0.8669 -0.2097];
% B_reel = [0 181.4 -180.4];
G_nominal_commande_1 =  tf(B_1,A_1);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% DISCRET %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
G_disc1 = c2d(G_nominal_commande_1,Te,'zoh'); 
G_disc1.variable = 'z^-1';
B_disc1 = G_disc1.num{1};
A_disc1 = G_disc1.den{1};
d=0;

%% Mod�le de comportement
% d�finition du polynome caracteristique
%     ksi = 1;
%     omega0 =10000%2*pi*10000;
%     pr = -ksi*omega0 + i*omega0*sqrt(1-ksi*ksi);
%     zr = exp(pr*Te);
%     Pc0 = conv([1 -zr],[1 -conj(zr)]); 
%     
%     taux= 1/(3*omega0);
%     zaux=exp(-Te/taux);
%     
%     Pc1 = conv([1 -zaux],[1 -zaux]);
%     Pc1 = conv(conv([1 -zaux],[1 -zaux]),Pc1);
%     Pc = conv(Pc0,Pc1)
%     roots(Pc)
%     
% % les perturbations � rejeter
%     D = [1 -1];
%     [Rd Rn] = bezout_G(conv(A,D),B,Pc);
%     Rd = conv(Rd,D); % d�nominateur du r�gulateur
% 
% % poursuite parfaite
%     Rp = Pc/sum(B);
% 
%     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %Definition de la fonction de transfert du syst�me boucl� 
% A_R1=conv(A,Rd);
% F1=tf(A_R1,Pc,Te);
%  
% figure();
% pzmap(F1)
% title('Position des p�les et des z�ros de la Fonction de Transfert : Y/Vy');
% 
% figure();
% bode(F1)
% title('Bode de Y/Vy');
% 
% figure();
% F1_2 = tf(Rn,Rd)
% bode(F1_2)
% title('Bode de U/Uy');
%     
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% consigne_bf=1;
% bruit_bf = 1;
% pertu_sortie_bf=1;
% pertu_entree_bf=0;

%% Calcul fonction transfert pour Vo = 24V

Gdo_2 = (Vo_2*Vo_2)/Vin;
OmZ2_2 = (R/L)*(Vin/Vo_2)*(Vin/Vo_2);
Om0_2 = (1/sqrt(L*C))*(Vin/Vo_2); f0_2 = Om0_2/(2*pi);
Q_2 = Om0_2/((RL+RS/4)/L+1/(C*(R)));

% Fonction de transfert
B_2 = Gdo_2*[-1/OmZ2_2 1];
A_2 = [1/(Om0_2*Om0_2) 1/(Om0_2*Q_2) 1];

G_nominal_commande_2 =  tf(B_2,A_2);

% Calcul de la fonction de transfert en discret
G_disc2 = c2d(G_nominal_commande_2,Te,'zoh'); 
G_disc2.variable = 'z^-1';
B_disc2 = G_disc2.num{1};
A_disc2 = G_disc2.den{1};
d=0;


%% Calcul fonction transfert pour Vo = 30V

Gdo_3 = (Vo_3*Vo_3)/Vin;
OmZ2_3 = (R/L)*(Vin/Vo_3)*(Vin/Vo_3);
Om0_3 = (1/sqrt(L*C))*(Vin/Vo_3); f0_3 = Om0_3/(2*pi);
Q_3 = Om0_3/((RL+RS/4)/L+1/(C*(R)));

% Fonction de transfert
B_3 = Gdo_3*[-1/OmZ2_3 1];
A_3 = [1/(Om0_3*Om0_3) 1/(Om0_3*Q_3) 1];

G_nominal_commande_3 =  tf(B_3,A_3);

% Calcul de la fonction de transfert en discret
G_disc3 = c2d(G_nominal_commande_3,Te,'zoh'); 
G_disc3.variable = 'z^-1';
B_disc3 = G_disc3.num{1};
A_disc3 = G_disc3.den{1};
d=0;

%% Calcul fonction transfert pour Vo = 36V

Gdo_4 = (Vo_4*Vo_4)/Vin;
OmZ2_4 = (R/L)*(Vin/Vo_4)*(Vin/Vo_4);
Om0_4 = (1/sqrt(L*C))*(Vin/Vo_4); f0_4 = Om0_4/(2*pi);
Q_4 = Om0_4/((RL+RS/4)/L+1/(C*(R)));

% Fonction de transfert
B_4 = Gdo_4*[-1/OmZ2_4 1];
A_4 = [1/(Om0_4*Om0_4) 1/(Om0_4*Q_4) 1];

G_nominal_commande_4 =  tf(B_4,A_4);

% Calcul de la fonction de transfert en discret
G_disc4 = c2d(G_nominal_commande_4,Te,'zoh'); 
G_disc4.variable = 'z^-1';
B_disc4 = G_disc4.num{1};
A_disc4 = G_disc4.den{1};
d=0;
% A_reel = [1 -0.7954 -0.188];
% B_reel = [0 2.366 0];
% G_reel = tf(B_reel,A_reel,Te);
% G_reel.variable = 'z^-1';
figure
bode(G_nominal_commande_1,G_nominal_commande_2,G_nominal_commande_3,G_nominal_commande_4)
bandwidth(G_nominal_commande_1)
bandwidth(G_nominal_commande_2)
bandwidth(G_nominal_commande_3)
bandwidth(G_nominal_commande_4)
%% Jonction des syst�mes pour analyse post�rieure
 sys(:,:,1) = G_disc1;
 sys(:,:,2) = G_disc2;
 sys(:,:,3) = G_disc3;
 sys(:,:,4) = G_disc4;
%  sys(:,:,4) = G_reel;
%% DESIGN REGULATEUR A RENTRER DANS LE FICHIER .C
num_IMC = 3.70429313276254e-005*[1 1];
den_IMC = [1 -1];
reg = tf(num_IMC,den_IMC,Te,'Variable','z^-1');
%% Point de fonctionnement Vo = 18 V
Pc_1 = conv(conv(A_disc1,A_disc1),den_IMC); % Polinome caract�ristique
Rd_1 = conv(A_disc1,den_IMC)-conv(B_disc1,num_IMC);
Rn_1 = conv(A_disc1,num_IMC);
num_S1 = conv(A_disc1,Rd_1);
num_T1 = conv(B_disc1,Rn_1);
num_GS1 = conv(B_disc1,Rd_1);
num_RS1 = conv(A_disc1,Rn_1);
S1 = tf(num_S1,Pc_1);
T1 = tf(num_T1,Pc_1);
GS1 = tf(num_GS1,Pc_1);
RS1 = tf(num_RS1,Pc_1);
figure
subplot(2,2,1)
bode(S1)
subplot(2,2,2)
bode(T1)
subplot(2,2,3)
bode(GS1)
subplot(2,2,4)
bode(RS1)

%% Point de fonctionnement Vo = 24 V
Pc_2 = conv(conv(A_disc2,A_disc2),den_IMC); % Polinome caract�ristique
Rd_2 = conv(A_disc2,den_IMC)-conv(B_disc2,num_IMC);
Rn_2 = conv(A_disc2,num_IMC);
num_S2 = conv(A_disc2,Rd_2);
num_T2 = conv(B_disc2,Rn_2);
num_GS2 = conv(B_disc2,Rd_2);
num_RS2 = conv(A_disc2,Rn_2);
S2 = tf(num_S2,Pc_2);
T2 = tf(num_T2,Pc_2);
GS2 = tf(num_GS2,Pc_2);
RS2 = tf(num_RS2,Pc_2);
figure
subplot(2,2,1)
bode(S2)
subplot(2,2,2)
bode(T2)
subplot(2,2,3)
bode(GS2)
subplot(2,2,4)
bode(RS2)

%% Point de fonctionnement Vo = 30 V
Pc_3 = conv(conv(A_disc3,A_disc3),den_IMC); % Polinome caract�ristique
Rd_3 = conv(A_disc3,den_IMC)-conv(B_disc3,num_IMC);
Rn_3 = conv(A_disc3,num_IMC);
num_S3 = conv(A_disc3,Rd_3);
num_T3 = conv(B_disc3,Rn_3);
num_GS3 = conv(B_disc3,Rd_3);
num_RS3 = conv(A_disc3,Rn_3);
S3 = tf(num_S3,Pc_3);
T3 = tf(num_T3,Pc_3);
GS3 = tf(num_GS3,Pc_3);
RS3 = tf(num_RS3,Pc_3);
figure
subplot(2,2,1)
bode(S3)
subplot(2,2,2)
bode(T3)
subplot(2,2,3)
bode(GS3)
subplot(2,2,4)
bode(RS3)
figure
bode(G_disc1*reg,G_disc2*reg,G_disc3*reg,G_disc4*reg);
grid