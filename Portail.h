#pragma once
#include "mvtperso.h"
#include "Plateformes.h"


void mouse(point& p, int& j);

class Portail {
    int h_portail=100;
    int w_portail=10;
    point position_portail={-100,-100};
    Color col;
public:
    Portail(Color color);
    point get_portal_position();
    void get_portal_w_h(int &w, int &h);
    void set_portal_position(point p);
    void Draw_portal();
    void erase_portal();



};

void teleportation(Personnage &Perso, Portail Port1, Portail Port2,int W,int H, bool &Au_sol,plateforme ASols,plateforme APlafonds);
point collision_tir(point point_vise,plateforme ASols,plateforme APlafonds,int X_hero,int Y_hero,int Taille_hero,int Ventre_hero,bool& portail_horizontale);
