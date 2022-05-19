#pragma once
#include "mvtperso.h"


void mouse(point& p, int& j);

class Portail {
    int h_portail=100;
    int w_portail=10;
    point position_portail={0,0};

    Color col;
public:
    Portail(Color color);
    point get_portal_position();
    void set_portal_position(point p);
    void Draw_portal();
    void erase_portal();



};
