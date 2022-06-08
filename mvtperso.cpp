#include "mvtperso.h"
#include "Plateformes.h"
#include "Portail.h"

void Menu_Pause(int& a,point souris,int j){
    AlphaColor gris=AlphaColor(150,150,150,155);
    if(a==16777216){
        bool PAUSE=true;
        a=-100000;
        fillRect(0,0,WindW,WindH,gris);
        drawString(500,500,"Pour jouer utiliser les flèches ainsi que la souris, bonne chance",RED,19);
        drawString(500,700,"Appuyer sur R pour recommencer le niveau",RED,19);
        while(PAUSE){
            milliSleep(1);
            keyboard(souris,a,j);

            if(a==16777216){
                PAUSE=false;
                fillRect(0,0,WindW,WindH,WHITE);
            }
        }
        a=-100000;
    }
}

void Vecteur_norme(point p, point& N){
    N.x =5*1/sqrt(p.x*p.x+p.y*p.y) * p.x;
    N.y =5*1/sqrt(p.x*p.x+p.y*p.y) * p.y;

}

int Norme(point P){
    return sqrt(P.x*P.x+P.y*P.y);
}

void Vecteur_norme(point p, point_double& N){
    N.x=p.x*1/sqrt(p.x*p.x+p.y*p.y);
    N.y=p.y*1/sqrt(p.x*p.x+p.y*p.y);
}

void keyboard(point& p, int& a, int& j) {
    Event e;
    a=0;
    j=0;
    do {
        getEvent(0,e);
        if(e.type==EVT_KEY_ON){
            a =  e.key;
        }
        if(e.type==EVT_BUT_ON){
            p.x = e.pix.x();
            p.y = e.pix.y();
            j=e.button;
        }
    } while(e.type!=EVT_NONE);
}

//constructeur

Personnage::Personnage(int x, int y){
    position={x,y};
}

//informatif

point Personnage::get_position(){
    return position;
}

int Personnage::get_dir(){
    return dir;
}

point Personnage::get_speed(){
    return vitesse;
}

//modifier a la main

void Personnage::modif_dir(int b){
    dir=b;
}

void Personnage::Change_vitesse_perso(int vx,int vy){
    vitesse={vx,vy};
}

void Personnage::Change_coord_perso(int X,int Y){
    position={X,Y};
}
void Personnage::Change_vitesse_perso(point V){
    vitesse=V;
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


void Zone_win(point position,int Ventre_hero,int Taille_hero,int& a,point souris,int j,bool& finit){

        int Xvert_haut=WindW/2+7*Ventre_hero;
        int epaisseur=150;
        int Yvert_haut=9*WindH/10-5*Taille_hero;
        int hauteur=3*Taille_hero;
        AlphaColor Green=AlphaColor(0,255,0,150);
        fillRect(Xvert_haut,Yvert_haut,epaisseur,hauteur,Green);
        if((position.x<Xvert_haut+epaisseur)&&(position.x>Xvert_haut)&&(position.y<Yvert_haut+hauteur)&&(position.y>Yvert_haut)){
            drawString(500,500,"YOU WON",GREEN,40);
            a=-10000;
            drawString(200,200,"PRESS ENTER TO SWITCH TO LEVEL ", BLACK,20);
            bool PAUSE=true;
            while(PAUSE){
                milliSleep(1);
                keyboard(souris,a,j);
                if(a==16777220){
                    PAUSE=false;
                    finit=true;
                }
            }
            a=-100000;
        }
    }



void Personnage::Game_Over(int Wind,int H,int& a,point souris,int j,int Xdep,int Ydep){
    if(position.y>Wind+H){
        AlphaColor red=AlphaColor(150,0,0,155);
        bool PAUSE=true;
        fillRect(0,0,WindW,WindH,red);
        a=-10000;
        drawString(500,500,"GAME OVER, PRESS R",BLACK);
        while(PAUSE){
            milliSleep(1);

            keyboard(souris,a,j);
            if(a==114){
                PAUSE=false;
                fillRect(0,0,WindW,WindH,WHITE);
                position.x=Xdep;
                position.y=Ydep;
                vitesse={0,0};
            }
        }
    }
}

//jeu


void gametest(int w,int h, int W1, int H1, NativeBitmap I[6],int Niveau){
    

    // Définition du personnage
    int X_dep=w/4;
    int Y_dep=h/2+100;
    Personnage Perso(X_dep,Y_dep);
    point P=Perso.get_position();
    fillRect(P.x,P.y,10,10,BLUE);

    int a=0; //variable liée au keybord
    int j=0; //variable liée à la souris
    bool Au_Sol = false; // booléen : personnage sur une plateforme true ou non false
    int dt =1; // pas de temps

    // Définition des plateformes

    plateforme Niveau_sol=plateforme(4,sol_segments_niveau_1(W1,H1));
    plateforme Niveau_plafond=plateforme(1,plafond_segments_niveau_1());
    if(Niveau==2){
        Niveau_sol=plateforme(4,sol_segments_niveau_2(W1,H1));
        Niveau_plafond=plateforme(1,plafond_segments_niveau_2());
    }
    Niveau_sol.draw(2);
    Niveau_plafond.draw(1);

    // Définition des portails

    Portail Portail_rouge(RED);
    Portail Portail_bleu(BLUE);
    point souris={WindW/2,WindH/2};
    point souris2={WindW/2,WindH/2};
    point projection;
    bool finit=false;
    while(!finit){
        point V_anterieur=Perso.get_speed();
        //MENUS
        Menu_Pause(a,souris,j);
        Perso.Game_Over(WindH,H1,a,souris,j,X_dep,Y_dep);
        Zone_win(Perso.get_position(),W1,H1,a,souris,j,finit);
        if(a==114){
            Perso.Change_coord_perso(X_dep,Y_dep);
            Perso.Change_vitesse_perso(0,0);
            Portail_bleu.erase_portal();
            Portail_rouge.erase_portal();
            Portail_bleu.set_portal_position({-1000,-1000});
            Portail_rouge.set_portal_position({-1000,-1000});
        }

        //FIN MENU PAUSE
        Portail_bleu.erase_portal();
        Portail_rouge.erase_portal();

        bool portail_horizontal=false;
        if((souris.x!=souris2.x)&&(souris.y!=souris2.y)){//si la position du clique change
            projection=collision_tir(souris,Niveau_sol,Niveau_plafond,P.x,P.y,W1,H1,portail_horizontal,Perso.get_dir());

            souris2=souris;}


        //affichage des portails

        if (j==1){
            Portail_bleu.set_orientation(portail_horizontal);
            Portail_bleu.set_portal_position(projection);
        }
        if (j==3){
            Portail_rouge.set_orientation(portail_horizontal);
            Portail_rouge.set_portal_position(projection);
        }
        Portail_bleu.Draw_portal();
        Portail_rouge.Draw_portal();

        //Téléportation
        teleportation(Perso,Portail_rouge,Portail_bleu,W1,H1,Au_Sol,Niveau_sol,Niveau_plafond);
        teleportation(Perso,Portail_bleu,Portail_rouge,W1,H1,Au_Sol,Niveau_sol,Niveau_plafond);


        //affichage du personnage
        fillRect(P.x,P.y,W1+1,H1,WHITE);
        keyboard(souris,a,j);
        Perso.modif_vitesse(a,Au_Sol);
        Naturel(Perso,Au_Sol,dt);
        point V=Perso.get_speed();
        if(Norme(V)>15){
            Perso.Change_vitesse_perso(V_anterieur);
        }
        P =Perso.get_position();

        Perso.affiche_perso(I,a);

        //        milliSleep(dt);
        
        //affichage numero plateforme pour debuggage
        int numero_plateforme_du_perso=plateforme_personnage(P.x,W1,Niveau_sol.Liste_Segment,Niveau_sol.nombre_segment);
        milliSleep(10);
        if(numero_plateforme_du_perso==-1){
            drawString(100,100,"plateforme -1 donc erreur",BLUE,13);
        }
        //fin affichage

        //sequence collision
        Segment_plateforme NotrePlateforme=Niveau_sol.Liste_Segment[numero_plateforme_du_perso];
        bool* etat_collisions=Collisions(Niveau_sol,Niveau_plafond,P.x,P.y,W1,H1);

        if(etat_collisions[0]){ //si le hero se prend le plafond
            Perso.Change_coord_perso(P.x,Niveau_plafond.Liste_Segment[0].altitude+Niveau_plafond.Liste_Segment[0].epaisseur);

        }
        Niveau_plafond.draw(1);
        if(etat_collisions[1]){ //si le hero a les pieds sur le sol
            Perso.Change_coord_perso(P.x,NotrePlateforme.altitude-H1);
            Au_Sol=true;
            Niveau_sol.draw(2);
        }

        if(etat_collisions[1]){ //si le hero a les pieds sur le sol
            Perso.Change_coord_perso(P.x,NotrePlateforme.altitude-H1);
            Au_Sol=true;
            Niveau_sol.draw(2);
        }

        if(!etat_collisions[1]){ //si le hero n'a pas les pieds sur la plateforme
            Au_Sol=false;
            Niveau_sol.draw(2);
        }

        if(NotrePlateforme.Vide){ //si c'est vide en dessous
            Au_Sol=false;
        }

        if(etat_collisions[2]){//si on se prend un mur a gauche
            Perso.Change_coord_perso(NotrePlateforme.extremite_G,P.y);
        }

        if(etat_collisions[3]){//si on se prend un mur a droite
            Perso.Change_coord_perso(NotrePlateforme.extremite_D-W1,P.y);
        }

    }
    Niveau_plafond.destructeur();
    Niveau_sol.destructeur();
}
