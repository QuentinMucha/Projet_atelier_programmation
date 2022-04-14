#include "Plateformes.h"

plateforme::plateforme(int NBR_Seg,Segment_plateforme* LISTE_SEG){ //il faut que nbr_seg = len(liste_seg)
    nombre_segment=NBR_Seg;
    Liste_Segment=new Segment_plateforme[NBR_Seg];
    for(int i=0;i<NBR_Seg;i++){
        Liste_Segment[i]=LISTE_SEG[i];

    }
}

void plateforme::draw(){ //si extremite tracer mur jusqu'en bas, et tracer le plafond egalement
    int W,H;
    for(int i=0;i<nombre_segment;i++){
        W=Liste_Segment[i].extremite_D-Liste_Segment[i].extremite_G;
        H=Liste_Segment[i].epaisseur;
        fillRect(Liste_Segment[i].extremite_G,Liste_Segment[i].altitude,W,H,BLACK);
    }
}

void plateforme::destructeur(){
    delete[] Liste_Segment;
}

Segment_plateforme* sol_segments_niveau_1(){
    Segment_plateforme* Resultat=new Segment_plateforme[3];
    Resultat[0]={0,250,WindH-10,9};
    Resultat[1]={300,350,WindH-50,9};
    Resultat[2]={350,500,WindH-100,9};
    return Resultat;
}

Segment_plateforme* plafond_segments_niveau_1(){
    Segment_plateforme* Resultat=new Segment_plateforme[3];
    Resultat[0]={0,500,WindH-400,9};

    return Resultat;
}
