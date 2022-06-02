#pragma once
#include <cmath>
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <ctime>
#include <Imagine/Graphics.h>
#include <string>
using namespace Imagine;
using namespace std;


struct point {
    int x;
    int y;
};
struct point_double {
    double x;
    double y;
};

void Vecteur_norme(point p, point& N);
void Vecteur_norme(point p, point_double& N);

void keyboard(point& p, int& a, int& j);

class Personnage{
    point position;
    point vitesse={0,0};
    int dir=0; //0 : orientation du perso vers la droite; 1 : orientation du perso vers la gauche

public:
    Personnage(int x, int y);
    point get_position();
    int get_dir();
    void gravite(bool b,int dt);
    void modif_dir(int b);
    void modif_vitesse(int a, bool& b);
    void mouvement(int dt);
    void frein(bool b);
    void affiche_perso(NativeBitmap I[6], int a);
    void efface_perso(int W1,int H1);
    void Change_coord_perso(int X,int Y);
    void Change_vitesse_perso(int vx,int vy);
    point get_speed();
};


void gametest(int w,int h, int W1, int H1, NativeBitmap I[6]);

