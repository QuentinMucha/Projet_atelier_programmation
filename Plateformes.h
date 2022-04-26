#pragma once
#include <cmath>
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <ctime>
#include <Imagine/Graphics.h>
using namespace Imagine;

const int WindW=500;
const int WindH=500;
const int Ventre_hero=10;
const int Taille_hero=10;

struct Segment_plateforme{
    int extremite_G;
    int extremite_D;
    int altitude;
    int epaisseur;
    bool Vide=false; //si true alors c'est le vide
};

class plateforme{ //une plateforme est une liste de segments
public:
    int nombre_segment;
    Segment_plateforme* Liste_Segment;
    void destructeur();
    plateforme(int NBR_Seg,Segment_plateforme* LISTE_SEG); //constructeur
    void draw(int K); // si K=1 c'est un sol si K=2 c'est un plafond
};

Segment_plateforme* sol_segments_niveau_1();
Segment_plateforme* plafond_segments_niveau_1();
int plateforme_personnage(int X_personnage,int ventre,Segment_plateforme* Seg_plat,int Longueur); //ventre est l'epaisseur du personnage
bool* Collisions(plateforme ASols, plateforme APlafonds,int X_hero,int Y_hero);
