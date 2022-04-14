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
public:
    Personnage(int x, int y);
    point get_position();
    void draw_perso();
    void erase_perso();
    void move(int a);
    void saut();

};

void gametest(int w, int h);
