#include "mvtperso.h"
#include "Portail.h"



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

    if (dir==0){
        if (x+W>=xP-wP/2 && x+W<xP+wP/2 && y>yP-hP/2 && y<yP+hP/2){
            Perso.Change_coord_perso(xP2,yP2);
            Perso.Change_vitesse_perso(5,0);
            Au_sol=false;
        }
        cout<<"x="<<x+W+10<<" xP="<<xP-wP<<" y="<<y<<" yP-hP="<<yP-hP<<" yP+hP="<<yP+hP<<endl;
    }
    if (dir==1){
        if (x<=xP+wP/2 && x>xP-wP/2 && y>yP-hP/2 && y<yP+hP/2){
            Perso.Change_coord_perso(xP2-W,yP2-H);
            Perso.Change_vitesse_perso(-5,0);
            Au_sol=false;

        }
    }


}
