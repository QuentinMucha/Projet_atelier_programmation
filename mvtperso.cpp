#include "mvtperso.h"

int keyboard() {
    Event e;
    do {
        getEvent(0,e);
        if(e.type==EVT_KEY_ON)
            return e.key;
    } while(e.type!=EVT_NONE);
    return 0;
}

//constructeur
Personnage::Personnage(int x, int y){
    position={x,y};
}



point Personnage::get_position(){
    return position;
}


void Personnage::draw_perso(){
    fillRect(position.x,position.y,10,10,BLUE);
}

void Personnage::erase_perso(){
    fillRect(position.x,position.y,10,10,WHITE);
}

void Personnage::move(int a){ // a variable retournée par keyboard
    //Déplacement à gauche
    if (a==16777234){
       position.x=position.x-5;
    }
    //Déplacement à droite
    if (a==16777236){
       position.x=position.x+5;
    }
    //Saut
    if (a==16777235){
       position.y=position.y-10;
    }

}



void Personnage::saut(){

}




void gametest(int w,int h){

    Personnage Perso(w/2, h/2);
    point P=Perso.get_position();
    fillRect(P.x,P.y,10,10,BLUE);
    int a=0;
    while(true){
        fillRect(P.x,P.y,10,10,WHITE);
        a=keyboard();
        Perso.move(a);
        P =Perso.get_position();
        fillRect(P.x,P.y,10,10,BLUE);
        milliSleep(10);
    }
}
