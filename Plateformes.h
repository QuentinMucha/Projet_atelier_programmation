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

struct Segment_plateforme{
    int extremite_G;
    int extremite_D;
    int altitude;
    int epaisseur;
};

class plateforme{ //une plateforme est une liste de segments
    int nombre_segment;
    Segment_plateforme* Liste_Segment;
    void destructeur();
public:
    plateforme(int NBR_Seg,Segment_plateforme* LISTE_SEG); //constructeur
    void draw();
};

Segment_plateforme* sol_segments_niveau_1();
Segment_plateforme* plafond_segments_niveau_1();
