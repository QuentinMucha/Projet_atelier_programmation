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

//informatif

point Personnage::get_position(){
    return position;
}

point Personnage::get_speed(){
    return vitesse;
}

//modifier a la main

void Personnage::Change_vitesse_perso(int vx,int vy){
    vitesse={vx,vy};
}

void Personnage::Change_coord_perso(int X,int Y){
    position={X,Y};
}

void Personnage::modif_vitesse(int a, bool &Au_sol){ // a variable retournée par keyboard
    //Déplacement à gauche
    if (a==16777234){
        vitesse.x=-5;
    }
    //Déplacement à droite
    else if (a==16777236){
        vitesse.x=5;
    }
    if (a==16777235){
        if (Au_sol){
            vitesse.y=-15;
            Au_sol=false;
        }
    }

}

//causes naturelles

void Personnage::gravite(bool Au_sol, int dt){
    if (!Au_sol) {
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

void Personnage::frein(bool Au_sol){
    if (Au_sol){
        if (vitesse.x>0){
            vitesse.x=vitesse.x-1;
        }
        if(vitesse.x<0){
            vitesse.x=vitesse.x+1;
        }
    }

    //    if(b){ //si on est au sol il faut freiner aussi
    //        if (vitesse.x>0){
    //            vitesse.x=vitesse.x-1;
    //        }
    //        if(vitesse.x<0){
    //            vitesse.x=vitesse.x+1;
    //        }
    //    }
}

void Naturel(Personnage& Perso,bool b,int dt){
    Perso.gravite(b,dt);
    Perso.mouvement(dt);
    Perso.frein(b);
}

//affichage
void Personnage::affiche_perso(NativeBitmap I[6], int a){
    //Déplacement à gauche

    if (a==16777234){
        dir =1;
        putNativeBitmap(position.x,position.y,I[3]);

    }
    //Déplacement à droite
    else if (a==16777236){
        dir =0;
        putNativeBitmap(position.x,position.y,I[2]);

    }
    else{
        if (dir == 1){
            putNativeBitmap(position.x,position.y,I[1]);
        }
        if (dir == 0){
            putNativeBitmap(position.x,position.y,I[0]);
        }
    }
}





void Personnage::efface_perso(int W1,int H1){

    fillRect(get_position().x, get_position().y, W1, H1, WHITE);
}

//jeu

void gametest(int w,int h, int W1, int H1, NativeBitmap I[6]){

    Personnage Perso(w/4, h/2);
    point P=Perso.get_position();
    fillRect(P.x,P.y,10,10,BLUE);
    int a=0;
    bool Au_Sol = false; // booléen : personnage sur une plateforme true ou non false
    int dt =1;
    plateforme Niveau1_sol=plateforme(4,sol_segments_niveau_1(W1,H1));
    plateforme Niveau1_plafond=plateforme(1,plafond_segments_niveau_1());
    Niveau1_sol.draw(2);
    Niveau1_plafond.draw(1);
    while(true){

        fillRect(P.x,P.y,W1+1,H1,WHITE);

        a=keyboard();
        Perso.modif_vitesse(a,Au_Sol);
        Naturel(Perso,Au_Sol,dt);
        P =Perso.get_position();


        Perso.affiche_perso(I,a);
        milliSleep(dt);

        //affichage numero plateforme
        drawString(WindW-200,20,std::to_string(plateforme_personnage(P.x,W1,Niveau1_sol.Liste_Segment,Niveau1_sol.nombre_segment)),RED);
        milliSleep(10);
        fillRect(WindW-200,0,200,20,WHITE);
        if(plateforme_personnage(P.x,W1,Niveau1_sol.Liste_Segment,Niveau1_sol.nombre_segment)==-1){
            drawString(100,100,"plateforme -1 donc erreur",BLUE,13);
        }
        //fin affichage

        Segment_plateforme NotrePlateforme=Niveau1_sol.Liste_Segment[plateforme_personnage(P.x,W1,Niveau1_sol.Liste_Segment,Niveau1_sol.nombre_segment)];

        if(Collisions(Niveau1_sol,Niveau1_plafond,P.x,P.y,W1,H1)[1]){
            Perso.Change_coord_perso(P.x,NotrePlateforme.altitude-H1);
            Au_Sol=true;
            Niveau1_sol.draw(2);
        }

        if(NotrePlateforme.Vide){ //si c'est vide en dessous
           Au_Sol=false;
        }

        if(NotrePlateforme.altitude>Perso.get_position().y+H1){ //si pas de plateforme aux pieds
            Au_Sol=false;
        }
    }
    Niveau1_plafond.destructeur();
    Niveau1_sol.destructeur();
}
