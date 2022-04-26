#pragma once
#include <cmath>
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <ctime>
#include <Imagine/Graphics.h>
using namespace Imagine;



int keyboard();

struct point {
    int x;
    int y;
};


class Personnage{
    point position;
    point vitesse={0,0};

public:
    Personnage(int x, int y);
    point get_position();
    void gravite(bool b,int dt);
    void modif_vitesse(int a, bool& b);
    void mouvement(int dt);
    void frein(bool b);
    void affiche_perso(NativeBitmap I[6], int a);
    void efface_perso(int W1,int H1);

};

void gametest(int w,int h, int W1, int H1, NativeBitmap I[6]);

