#include "mvtperso.h"
#include "Plateformes.h"


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


void Personnage::modif_vitesse(int a, bool &b){ // a variable retournée par keyboard
    //Déplacement à gauche
    if (a==16777234){
        vitesse.x=-5;
    }
    //Déplacement à droite
    else if (a==16777236){
        vitesse.x=5;
    }
    if (a==16777235){
        vitesse.y=-15;
        b=true;
    }

}


void Personnage::gravite(bool b, int dt){
    if (b) {
        int ay=1;
        vitesse.y=vitesse.y+ay*dt;
    }
    else {
        vitesse.y=0;
    }
}


void Personnage::mouvement(int dt){
    position.x=position.x+vitesse.x*dt;
    position.y=position.y+vitesse.y*dt;
}

void Personnage::frein(bool b){
    if (not b){
        if (vitesse.x!=0){
            if (vitesse.x>0){
                vitesse.x=vitesse.x-1;
            }
            else{
                vitesse.x=vitesse.x+1;
            }
        }
    }
}


void gametest(int w,int h){

    Personnage Perso(w/2, h/2);
    point P=Perso.get_position();
    fillRect(P.x,P.y,10,10,BLUE);
    int a=0;
    bool b = false; // booléen : personnage sur une plateforme b=false ou non b=true
    int dt =1;
    plateforme Niveau1_sol=plateforme(4,sol_segments_niveau_1());
    plateforme Niveau1_plafond=plateforme(1,plafond_segments_niveau_1());
    Niveau1_sol.draw(2);
    Niveau1_plafond.draw(1);
    while(true){
        Perso.gravite(b,dt);
        Perso.frein(b);
        Perso.mouvement(dt);
        fillRect(P.x,P.y,10,10,WHITE);
        a=keyboard();
        Perso.modif_vitesse(a,b);
        P =Perso.get_position();
        fillRect(P.x,P.y,10,10,BLUE);
        milliSleep(dt);

        //affichage numero plateforme
        drawString(WindW-200,20,std::to_string(plateforme_personnage(P.x,Ventre_hero,Niveau1_sol.Liste_Segment,Niveau1_sol.nombre_segment)),RED);
        milliSleep(10);
        fillRect(WindW-200,0,200,20,WHITE);
        if(plateforme_personnage(P.x,Ventre_hero,Niveau1_sol.Liste_Segment,Niveau1_sol.nombre_segment)==-1){
            drawString(100,100,"plateforme -1 donc erreur",BLUE,13);
        }
        //fin affichage
        if(Collisions(Niveau1_sol,Niveau1_plafond,P.x,P.y)[1]){
            drawString(w/2,10+h/2,"IL EST COLLISIONE",RED,15);

        }

    }
    Niveau1_plafond.destructeur();
    Niveau1_sol.destructeur();
}
