#include "mvtperso.h"
#include "Portail.h"
#include "Plateformes.h"


Portail::Portail(Color color){
   col=color;
}

point Portail::get_portal_position(){
    return position_portail;
}

bool Portail::get_orientation(){
    return orientation;
}
void Portail::set_orientation(bool Horizontal){
    orientation=Horizontal;
}

void Portail::get_portal_w_h(int &w, int &h){
    w=w_portail;
    h=h_portail;
}

void Portail::set_portal_position(point p){
    position_portail=p;
}

void Portail::Draw_portal(){
    if (orientation){
        fillRect(position_portail.x-h_portail/2,position_portail.y-w_portail/2,h_portail,w_portail,col);
    }
    else {
        fillRect(position_portail.x-w_portail/2,position_portail.y-h_portail/2,w_portail,h_portail,col);
    }
}

void Portail::erase_portal(){
    if (orientation){
        fillRect(position_portail.x-h_portail/2,position_portail.y-w_portail/2,h_portail,w_portail,WHITE);
    }
    else {
        fillRect(position_portail.x-w_portail/2,position_portail.y-h_portail/2,w_portail,h_portail,WHITE);
    }
}

void teleportation(Personnage &Perso, Portail Port1, Portail Port2,int W,int H, bool &Au_sol, plateforme ASols,plateforme APlafonds){
    int x=Perso.get_position().x;
    int y=Perso.get_position().y;
    int dir=Perso.get_dir();

    int xP=Port1.get_portal_position().x;
    int yP=Port1.get_portal_position().y;
    bool orientation=Port1.get_orientation();

    int xP2=Port2.get_portal_position().x;
    int yP2=Port2.get_portal_position().y;

    int wP,hP;
    Port1.get_portal_w_h(wP,hP);
    point V=Perso.get_speed();
    int vx=V.x;
    int vy=V.y;
    int norme=Norme(V);

    bool* Collision=Collisions(ASols,APlafonds,xP2,yP2,5,5);
    if (orientation){ //si portail horizontal

        if (x<=xP+hP/2 && x>=xP-hP/2 && y+H>=yP-wP/2 && y+H<=yP+wP/2&&Au_sol){ //si dans les limites du portail
            Au_sol=false;

            if (Collision[3]){//collision droite
                Perso.Change_vitesse_perso({-norme,0});
                Perso.modif_dir(1);
                Perso.Change_coord_perso(xP2-W-1,yP2);
            }
            else if (Collision[2]){//collision gauche
                Perso.Change_vitesse_perso(norme,0);
                Perso.Change_coord_perso(xP2+W+1,yP2);
            }
            else if (Collision[1]){//collision sol
                Perso.Change_coord_perso(xP2-W/2,yP2-wP/2-H);
                Perso.Change_vitesse_perso(vx,-10);

            }
            else{ //collision plafond
                Perso.Change_coord_perso(xP2,yP2);
            }
        }
    }
    else{
        if (dir==0){//0 : orientation du perso vers la droite; 1 : orientation du perso vers la gauche
            if (x+W>=xP-wP/2 && x+W<xP+wP/2 && y>yP-hP/2 && y<yP+hP/2){
                Au_sol=false;
                if (Collision[3]){
                    Perso.Change_vitesse_perso(-vx-5,0);
                    Perso.modif_dir(1);
                    Perso.Change_coord_perso(xP2-W,yP2);
                }
                else if (Collision[2]){
                    Perso.Change_vitesse_perso(vx+5,0);
                    Perso.Change_coord_perso(xP2+W,yP2);
                }
                else if (Collision[1]){
                    Perso.Change_coord_perso(xP2-W/2,yP2-wP/2-H);
                    Perso.Change_vitesse_perso(vx,-10);

                }
                else {
                    Perso.Change_coord_perso(xP2,yP2);
                }
            }
        }
        if (dir==1){ //0 : orientation du perso vers la droite; 1 : orientation du perso vers la gauche
            if (x<=xP+wP/2 && x>xP-wP/2 && y>yP-hP/2 && y<yP+hP/2){
                Au_sol=false;


                if (Collision[3]){
                    Perso.Change_coord_perso(xP2-W,yP2);
                    Perso.Change_vitesse_perso(vx-5,0);

                }
                else if (Collision[2]){
                    Perso.Change_coord_perso(xP2+W,yP2);
                    Perso.modif_dir(0);
                    Perso.Change_vitesse_perso(-vx+5,0);
                }
                else if (Collision[1]){
                    Perso.Change_coord_perso(xP2-W/2,yP2-wP/2-H);
                    Perso.Change_vitesse_perso(vx,-10);

                }
                else {
                    Perso.Change_coord_perso(xP2,yP2);
                }
            }
        }
    }
}

point collision_tir(point point_vise,plateforme ASols,plateforme APlafonds,int X_hero,int Y_hero,int Taille_hero,int Ventre_hero,bool& portail_horizontale,int DIRECTION){ //cette fonction va renvoyer la collision entre le tir et l'obstacle
    point_double norme={0.,0.};
    point projection;

    if (DIRECTION==1){ //gauche
        projection={X_hero,Y_hero+Taille_hero/2+5};
    }
    if (DIRECTION==0){//droite
        projection={X_hero+Ventre_hero,Y_hero+Taille_hero/2+5};
    }

    point Vecteur_hero_to_clique={ point_vise.x -projection.x,point_vise.y -projection.y};
    Vecteur_norme(Vecteur_hero_to_clique,norme);
    point pt_base=projection;
    int a,b;
    int i=0;
    bool* COLLISIONS= Collisions(ASols,APlafonds,projection,4,4);
    bool rien_touche=((!COLLISIONS[0])&&(!COLLISIONS[1])&&(!COLLISIONS[2])&&(!COLLISIONS[3]));
    while (rien_touche){
        a=projection.x;
        b=projection.y;

        projection.x = pt_base.x+i*norme.x;
        projection.y = pt_base.y+i*norme.y;

        COLLISIONS= Collisions(ASols,APlafonds,projection,4,4);
        rien_touche=((!COLLISIONS[0])&&(!COLLISIONS[1])&&(!COLLISIONS[2])&&(!COLLISIONS[3]));
        i=i+1;
    }
    drawLine(pt_base.x,pt_base.y,projection.x,projection.y,PURPLE);
    milliSleep(30);
    drawLine(pt_base.x,pt_base.y,projection.x,projection.y,WHITE);
    if(COLLISIONS[0]){ //si collision au plafond
        portail_horizontale=true;
    }
    if(COLLISIONS[1]){//si collision au sol
        portail_horizontale=true;
    }

    return projection;
}





