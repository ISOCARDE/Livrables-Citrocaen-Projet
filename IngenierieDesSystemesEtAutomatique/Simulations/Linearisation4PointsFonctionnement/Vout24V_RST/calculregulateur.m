
function [reg,Rn,Rd,Rp,Pc]= calculregulateur(B,A,w_reg,mu)
    Pc1 = [1 2*w_reg w_reg*w_reg];
    Pc2prim = [1 mu*w_reg];
    Pc2 = conv(conv(Pc2prim,Pc2prim),Pc2prim);
    Pc = conv(Pc1,Pc2);
        
    %%%%%% partie rajoutée
%    Pc = conv(Pc,Pc2prim);
%    Pc = conv(Pc,Pc2prim);
    %%%%%%%%%%%
    
    %Modele des perturbations
    D=[1 0];
    
    %Calcul du polynome Aprime
    Aprim=conv(A,D);
    
    %Résolution de l'équation de Bezou
    [Rdprim,Rn] = bezou(Aprim,B,Pc);
    
    Rd=conv(Rdprim,D);
    
    reg=tf(Rn,Rd);
    
    %Calcul de Rp
    Rp=Pc/B(2);
end