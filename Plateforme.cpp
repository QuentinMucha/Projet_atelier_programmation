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
        if(Seg_plat[i].extremite_D==Seg_plat[i].extremite_G)
            Resultat[i]=true;
        else
            Resultat[i]=false;
    }
    return Resultat;//ne pas oublier de delete
}


int plateforme_personnage(int X_personnage,int ventre,Segment_plateforme* Seg_plat,int Longueur){
    int Moitie_droite=X_personnage+ventre/2;
    int Moitie_gauche=X_personnage-ventre/2;
    for(int i=0;i<Longueur;i++){
        if((Moitie_gauche<=Seg_plat[i].extremite_D)&&((Moitie_droite)>=(Seg_plat[i].extremite_G))){
            return i;
        }
    }
    std::cout<<"plateforme -1";
    return -1;
}

bool* Collisions(plateforme ASols,plateforme APlafonds,int X_hero,int Y_hero,int Ventre_hero,int Taille_hero){
    int NbrSols=ASols.nombre_segment;
    Segment_plateforme* Sols=ASols.Liste_Segment;
    int NbrPlafonds=APlafonds.nombre_segment;
    Segment_plateforme* Plafonds=APlafonds.Liste_Segment;

    int plate_hero=plateforme_personnage(X_hero,Ventre_hero,Sols,NbrSols);
    bool* Resultatt=new bool[3];  //(X,Y)
    Resultatt[0]=false;//collision droite ou gauche
    Resultatt[1]=false;//collision sol
    Resultatt[2]=false;//collision plafond
    assert(plate_hero>-1);
    if((Y_hero+Taille_hero)>=Sols[plate_hero].altitude){ //si en dessous du sol
        Resultatt[1]=true;
    }

    if(plate_hero==0){ //si a gauche de l'ecran
        if(X_hero<=Sols[plate_hero].extremite_G){ //si on sort de l'image a gauche
            Resultatt[0]=true;
        }
    }
    if(plate_hero==NbrSols-1){ //si a droite de l'ecran
        if(X_hero>=Sols[plate_hero].extremite_D-Ventre_hero){ //si on sort de l'image a gauche
            Resultatt[0]=true;
        }
    }
    if((plate_hero!=NbrSols-1)){//si pas a droite
        if(((Y_hero+Taille_hero)<Sols[plate_hero+1].altitude)){ //si suceptible de se prendre le mur
            if(Presence_mur(Sols,NbrSols)[plate_hero]){//si presence mur entre plate_hero et plate_hero+1
                if((X_hero+Ventre_hero)>Sols[plate_hero].extremite_D){//si le personnage est dans le mur;
                    Resultatt[0]=true;
                }
            }
        }
    }
    if((plate_hero!=0)){//si pas a gauche
        if(((Y_hero+Taille_hero)<Sols[plate_hero-1].altitude)){ //si suceptible de se prendre le mur
            if(Presence_mur(Sols,NbrSols)[plate_hero-1]){//si presence mur entre plate_hero et plate_hero-11
                if((X_hero+Ventre_hero)>Sols[plate_hero].extremite_G){//si le personnage est dans le mur;
                    Resultatt[0]=true;
                }
            }
        }
    }
    if((Y_hero)<=Plafonds[plate_hero].altitude) //si au dessus du plafond
        Resultatt[2]=true;
    //il est encore necessaire de faire les collisions au plafond
    return Resultatt;
}







