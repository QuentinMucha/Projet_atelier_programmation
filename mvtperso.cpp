#include "mvtperso.h"
#include "Plateformes.h"
#include "Portail.h"

void Vecteur_norme(point p, point& N){
    N.x =5*1/sqrt(p.x*p.x+p.y*p.y) * p.x;
    N.y =5*1/sqrt(p.x*p.x+p.y*p.y) * p.y;

}

void Vecteur_norme(point p, point_double& N){
    N.x=p.x*1/sqrt(p.x*p.x+p.y*p.y);
    N.y=p.y*1/sqrt(p.x*p.x+p.y*p.y);
    //    cout<<N.x<<" "<<N.y<<" ";
}

void keyboard(point& p, int& a, int& j) {
    Event e;
    a=0;
    j=0;
    do {
        getEvent(0,e);
        if(e.type==EVT_KEY_ON)
            a =  e.key;
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


//void Personnage::efface_perso(int W1,int H1){

//    fillRect(get_position().x, get_position().y, W1, H1, WHITE);
//}


//jeu

void gametest(int w,int h, int W1, int H1, NativeBitmap I[6]){
    

    // Définition du personnage
    Personnage Perso(3*w/4, h/2+100);
    point P=Perso.get_position();
    fillRect(P.x,P.y,10,10,BLUE);

    int a=0; //variable liée au keybord
    int j=0; //variable liée à la souris
    bool Au_Sol = false; // booléen : personnage sur une plateforme true ou non false
    int dt =1; // pas de temps

    // Définition des plateformes
    plateforme Niveau1_sol=plateforme(4,sol_segments_niveau_1(W1,H1));
    plateforme Niveau1_plafond=plateforme(1,plafond_segments_niveau_1());
    Niveau1_sol.draw(2);
    Niveau1_plafond.draw(1);


    // Définition des portails

    Portail Portail_rouge(RED);
    Portail Portail_bleu(BLUE);
    point souris={-1000,-1000};

    //variables utiles pour la gestion des portails
    //    point vecteur={0,0};
    //    point norm={0,0};
    //    point projection={0,0};
    point projection;
    while(true){


        //        //Gestion des portails
        //        vecteur.x = souris.x -P.x;
        //        vecteur.y = souris.y -P.y;
        //        Vecteur_norme(vecteur,norm);
        //        projection=souris;
        //        bool* COLLISIONS= Collisions(Niveau1_sol,Niveau1_plafond,projection,2,2);
        //        bool rien_touche=((!COLLISIONS[0])&&(!COLLISIONS[1])&&(!COLLISIONS[2])&&(!COLLISIONS[3]));
        //        while (rien_touche){
        //            projection.x = projection.x+norm.x;
        //            projection.y = projection.y+norm.y;
        //            cout<<projection.x<<" "<<projection.y<<" ";
        //            COLLISIONS= Collisions(Niveau1_sol,Niveau1_plafond,projection,2,2);
        //            rien_touche=((!COLLISIONS[0])&&(!COLLISIONS[1])&&(!COLLISIONS[2])&&(!COLLISIONS[3]));
        //        }


        bool portail_horizontal=false;
        projection=collision_tir(souris,Niveau1_sol,Niveau1_plafond,P.x,P.y,W1,H1,portail_horizontal);


        //affichage des portails
        Portail_bleu.erase_portal();
        Portail_rouge.erase_portal();
        if (j==1){
            Portail_bleu.set_portal_position(projection);
        }
        if (j==3){
            Portail_rouge.set_portal_position(projection);
        }
        Portail_bleu.Draw_portal();
        Portail_rouge.Draw_portal();

        //Téléportation
        teleportation(Perso,Portail_bleu,Portail_rouge,W1,H1,Au_Sol,Niveau1_sol,Niveau1_plafond);



        //affichage du personnage
        fillRect(P.x,P.y,W1+1,H1,WHITE);
        keyboard(souris,a,j);
        Perso.modif_vitesse(a,Au_Sol);
        Naturel(Perso,Au_Sol,dt);
        P =Perso.get_position();

        Perso.affiche_perso(I,a);

        milliSleep(dt);
        
        //affichage numero plateforme pour debuggage
        int numero_plateforme_du_perso=plateforme_personnage(P.x,P.y,W1,H1,Niveau1_sol.Liste_Segment,Niveau1_sol.nombre_segment);
        drawString(WindW-200,20,std::to_string(numero_plateforme_du_perso),RED);
        milliSleep(10);
        fillRect(WindW-200,0,200,20,WHITE);
        if(numero_plateforme_du_perso==-1){
            drawString(100,100,"plateforme -1 donc erreur",BLUE,13);
        }
        //fin affichage

        //sequence collision
        Segment_plateforme NotrePlateforme=Niveau1_sol.Liste_Segment[numero_plateforme_du_perso];
        bool* etat_collisions=Collisions(Niveau1_sol,Niveau1_plafond,P.x,P.y,W1,H1);

        //        if(etat_collisions[0]){ //si le hero se prend le plafond
        //            Perso.Change_coord_perso(P.x,Niveau1_plafond.Liste_Segment[0].altitude+Niveau1_plafond.Liste_Segment[0].epaisseur);

        //        }
        Niveau1_plafond.draw(1);
        if(etat_collisions[1]){ //si le hero a les pieds sur le sol
            Perso.Change_coord_perso(P.x,NotrePlateforme.altitude-H1);
            Au_Sol=true;
            Niveau1_sol.draw(2);
        }

        if(etat_collisions[1]){ //si le hero a les pieds sur le sol
            Perso.Change_coord_perso(P.x,NotrePlateforme.altitude-H1);
            Au_Sol=true;
            Niveau1_sol.draw(2);
        }

        if(!etat_collisions[1]){ //si le hero n'a pas les pieds sur la plateforme
            Au_Sol=false;
            Niveau1_sol.draw(2);
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
    Niveau1_plafond.destructeur();
    Niveau1_sol.destructeur();
}
