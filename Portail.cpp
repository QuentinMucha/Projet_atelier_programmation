#include "mvtperso.h"
#include "Portail.h"



Portail::Portail(Color color){
   col=color;
}
point Portail::get_portal_position(){
    return position_portail;
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
