#include "mvtperso.h"
#include "Portail.h"
#include "Plateformes.h"


Portail::Portail(Color color){
   col=color;
}

point Portail::get_portal_position(){
    return position_portail;
}

void Portail::get_portal_w_h(int &w, int &h){
    w=w_portail;
    h=h_portail;
}

void Portail::set_portal_position(point p){
    position_portail=p;
}

void Portail::Draw_portal(){
   fillRect(position_portail.x-w_portail/2,position_portail.y-h_portail/2,w_portail,h_portail,col);
}

void Portail::erase_portal(){
   fillRect(position_portail.x-w_portail/2,position_portail.y-h_portail/2,w_portail,h_portail,WHITE);
}

void teleportation(Personnage &Perso, Portail Port1, Portail Port2,int W,int H, bool &Au_sol){
    int x=Perso.get_position().x;
    int y=Perso.get_position().y;
    int dir=Perso.get_dir();

    int xP=Port1.get_portal_position().x;
    int yP=Port1.get_portal_position().y;
    int xP2=Port2.get_portal_position().x;
    int yP2=Port2.get_portal_position().y;

    int wP=0;
    int hP=0;
    Port1.get_portal_w_h(wP,hP);
    int vx=Perso.get_speed().x;

    if (dir==0){
        if (x+W>=xP-wP/2 && x+W<xP+wP/2 && y>yP-hP/2 && y<yP+hP/2){
            Au_sol=false;
            if (xP2>=WindW){
                Perso.Change_vitesse_perso(-vx-5,0);
                Perso.modif_dir(1);
                Perso.Change_coord_perso(xP2-W,yP2);
            }
            else if (xP2<=0){
                Perso.Change_vitesse_perso(vx+5,0);
                Perso.Change_coord_perso(xP2+W,yP2);
            }
            else {
                Perso.Change_coord_perso(xP2,yP2);
            }

        }
    }
    if (dir==1){ //0 : orientation du perso vers la droite; 1 : orientation du perso vers la gauche
        if (x<=xP+wP/2 && x>xP-wP/2 && y>yP-hP/2 && y<yP+hP/2){
            Au_sol=false;

            if (xP2>=WindW){
                Perso.Change_coord_perso(xP2-W,yP2);
                Perso.Change_vitesse_perso(-5,0);

            }
            else if (xP2<=0){
                Perso.Change_coord_perso(xP2+W,yP2);
                Perso.modif_dir(0);
                Perso.Change_vitesse_perso(-vx+5,0);
            }
            else {
                Perso.Change_coord_perso(xP2,yP2);
            }

        }
    }


}

point collision_tir(point point_vise,plateforme ASols,plateforme APlafonds,int X_hero,int Y_hero,int Taille_hero,int Ventre_hero,bool& portail_horizontale){ //cette fonction va renvoyer la collision entre le tir et l'obstacle

    point_double norme={0.,0.};
    point Vecteur_hero_to_clique={ point_vise.x -(X_hero+Ventre_hero/2),point_vise.y -(Y_hero-Taille_hero/2)};
    Vecteur_norme(Vecteur_hero_to_clique,norme);
    point projection={X_hero+Ventre_hero/2,Y_hero-Taille_hero/2};
    point pt_base=projection;
    int i=0;

    bool* COLLISIONS= Collisions(ASols,APlafonds,projection,1,1);
    bool rien_touche=((!COLLISIONS[0])&&(!COLLISIONS[1])&&(!COLLISIONS[2])&&(!COLLISIONS[3]));
    while (rien_touche){
        projection.x = pt_base.x+i*norme.x;
        projection.y = pt_base.y+i*norme.y;

        COLLISIONS= Collisions(ASols,APlafonds,projection,2,2);
        rien_touche=((!COLLISIONS[0])&&(!COLLISIONS[1])&&(!COLLISIONS[2])&&(!COLLISIONS[3]));
        i=i+1;
    }
    if(COLLISIONS[0]){ //si collision au plafond
        portail_horizontale=true;
    }
    if(COLLISIONS[1]){//si collision au sol
        portail_horizontale=true;
    }
    return projection;
}


    //keyboard(souris,a,j);


