#include "Plateformes.h"

plateforme::plateforme(int NBR_Seg,Segment_plateforme* LISTE_SEG){ //il faut que nbr_seg = len(liste_seg)
    nombre_segment=NBR_Seg;
    Liste_Segment=new Segment_plateforme[NBR_Seg];
    for(int i=0;i<NBR_Seg;i++){
        Liste_Segment[i]=LISTE_SEG[i];

    }
}

void plateforme::draw(int K){ //si extremite tracer mur jusqu'en bas, et tracer le plafond egalement
    int W,H;
    for(int i=0;i<nombre_segment;i++){
        if(!Liste_Segment[i].Vide){
            W=Liste_Segment[i].extremite_D-Liste_Segment[i].extremite_G;
            H=Liste_Segment[i].epaisseur;
            if(K==1){
                fillRect(Liste_Segment[i].extremite_G,Liste_Segment[i].altitude,W,H,BLACK);}
            if(K==2){
                fillRect(Liste_Segment[i].extremite_G,Liste_Segment[i].altitude,W,1000,BLACK);}
        }
        if(Liste_Segment[i].Vide){
            drawString(5+Liste_Segment[i].extremite_G,WindH-10,"VIDE",RED,15);
        }
    }
}

void plateforme::destructeur(){
    delete[] Liste_Segment;
}

Segment_plateforme* sol_segments_niveau_1(int Ventre_hero,int Taille_hero){
    Segment_plateforme* Resultat=new Segment_plateforme[4];
    Resultat[0]={0,WindW/2,9*WindH/10,9};
    Resultat[1]={WindW/2,WindW/2+3*Ventre_hero,WindH+10,10,true};
    Resultat[2]={WindW/2+3*Ventre_hero,WindW/2+5*Ventre_hero,9*WindH/10-Taille_hero,9};
    Resultat[3]={WindW/2+5*Ventre_hero,WindW,9*WindH/10-2*Taille_hero,9};
    return Resultat;
}

Segment_plateforme* plafond_segments_niveau_1(){
    Segment_plateforme* Resultat=new Segment_plateforme[3];
    Resultat[0]={0,WindW,WindH/10,9};

    return Resultat;
}

bool* Presence_mur(Segment_plateforme* Seg_plat,int Longueur){ //assert len(Seg_Plat)==Longueur
    bool* Resultat=new bool[Longueur-1];
    for(int i=0;i<Longueur-1;i++){
        if(Seg_plat[i].extremite_D==Seg_plat[i+1].extremite_G)
            Resultat[i]=true;
        else
            Resultat[i]=false;
    }
    return Resultat;//ne pas oublier de delete
}


int plateforme_personnage(int X_personnage,int Y_personnage,int ventre,int taille,Segment_plateforme* Seg_plat,int Longueur){
    for(int i=0;i<Longueur;i++){
        if((X_personnage+ventre/2<=Seg_plat[i].extremite_D)&&((X_personnage+ventre/2)>=(Seg_plat[i].extremite_G))){
            return i;
        }
    }
    return -1;
}

int plafond_personnage(int X_personnage,int Y_personnage,int ventre,int taille,Segment_plateforme* Seg_plat,int Longueur){
    for(int i=0;i<Longueur;i++){
        if((X_personnage+ventre/2<=Seg_plat[i].extremite_D)&&((X_personnage+ventre/2)>=(Seg_plat[i].extremite_G))){
            return i;
        }
    }
    return -1;
}

bool* Collisions(plateforme ASols,plateforme APlafonds,int X_hero,int Y_hero,int Ventre_hero,int Taille_hero){
    int NbrSols=ASols.nombre_segment;
    Segment_plateforme* Sols=ASols.Liste_Segment;
    //    int NbrPlafonds=APlafonds.nombre_segment;
    Segment_plateforme* Plafonds=APlafonds.Liste_Segment;

    int plate_hero=plateforme_personnage(X_hero,Y_hero,Ventre_hero,Taille_hero,Sols,NbrSols);
    bool* Resultatt=new bool[4];  //(X,Y)
    int pied_hero=Y_hero+Taille_hero;
    int cote_droit_hero=X_hero+Ventre_hero;
    int cote_gauche_hero=X_hero;
    bool* liste_murs=Presence_mur(Sols,NbrSols);
    Resultatt[3]=false;//collision droite
    Resultatt[2]=false;//collision gauche
    Resultatt[1]=false;//collision sol
    Resultatt[0]=false;//collision plafond

    if((pied_hero)>=Sols[plate_hero].altitude){ //si en dessous du sol
        Resultatt[1]=true;
    }

    if(plate_hero==0){ //si a gauche de l'ecran
        if(cote_gauche_hero<=Sols[plate_hero].extremite_G){ //si on sort de l'image a gauche
            Resultatt[2]=true;
        }
    }

    if(plate_hero==NbrSols-1){ //si a droite de l'ecran
        if(cote_droit_hero>=Sols[plate_hero].extremite_D){ //si on sort de l'image a droite
            Resultatt[3]=true;
        }
    }

    if((plate_hero!=NbrSols-1)){//si pas a droite
        if(pied_hero>Sols[plate_hero+1].altitude){ //si suceptible de se prendre le mur
            if(liste_murs[plate_hero]){//si presence mur entre plate_hero et plate_hero+1
                if((cote_droit_hero)>Sols[plate_hero].extremite_D){//si le personnage est dans le mur;
                    Resultatt[3]=true;
                }
            }
        }
    }

    if((plate_hero!=0)){//si pas a gauche
        if((pied_hero)>Sols[plate_hero-1].altitude){ //si suceptible de se prendre le mur
            if(liste_murs[plate_hero-1]){//si presence mur entre plate_hero et plate_hero-1
                if(cote_gauche_hero<Sols[plate_hero].extremite_G){//si le personnage est dans le mur;
                    Resultatt[2]=true;
                }
            }
        }
    }

    if((Y_hero)<=Plafonds[plafond_personnage(X_hero,Y_hero,Ventre_hero,Taille_hero,Sols,NbrSols)].altitude){ //si au dessus du plafond
        Resultatt[0]=true;}
    delete[] liste_murs;
    return Resultatt;
}





bool* Collisions(plateforme ASols,plateforme APlafonds,point coord_hero,int Ventre_hero,int Taille_hero){

    return Collisions(ASols,APlafonds,coord_hero.x,coord_hero.y,Ventre_hero,Taille_hero);
}


