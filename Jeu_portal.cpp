
#include "mvtperso.h"
#include "Plateformes.h"
#include "Portail.h"

//on code le personnage depuis le coin haut gauche



int main() {
    openWindow(WindW,WindH);

    //chargement des images
    int Ventre_hero1,Taille_hero1;
    byte *rgb1;
    loadColorImage(srcPath("perso2_d.jpg"),rgb1,Ventre_hero1,Taille_hero1);
    NativeBitmap perso_statique_d(Ventre_hero1,Taille_hero1);
    perso_statique_d.setColorImage(0,0,rgb1,Ventre_hero1,Taille_hero1);
    delete[ ]rgb1;

    byte *rgb2;
    loadColorImage(srcPath("perso2_g.jpg"),rgb2,Ventre_hero1,Taille_hero1);
    NativeBitmap perso_statique_g(Ventre_hero1,Taille_hero1);
    perso_statique_g.setColorImage(0,0,rgb2,Ventre_hero1,Taille_hero1);
    delete[ ]rgb2;

    byte *rgb3;
    loadColorImage(srcPath("perso_mvt1_d.jpg"),rgb3,Ventre_hero1,Taille_hero1);
    NativeBitmap perso_mvt1_d(Ventre_hero1,Taille_hero1);
    perso_mvt1_d.setColorImage(0,0,rgb3,Ventre_hero1,Taille_hero1);
    delete[ ]rgb3;

    byte *rgb4;
    loadColorImage(srcPath("perso_mvt1_g.jpg"),rgb4,Ventre_hero1,Taille_hero1);
    NativeBitmap perso_mvt1_g(Ventre_hero1,Taille_hero1);
    perso_mvt1_g.setColorImage(0,0,rgb4,Ventre_hero1,Taille_hero1);
    delete[ ]rgb4;

    byte *rgb5;
    loadColorImage(srcPath("perso_mvt2_d.jpg"),rgb5,Ventre_hero1,Taille_hero1);
    NativeBitmap perso_mvt2_d(Ventre_hero1,Taille_hero1);
    perso_mvt2_d.setColorImage(0,0,rgb5,Ventre_hero1,Taille_hero1);
    delete[ ]rgb5;

    byte *rgb6;
    loadColorImage(srcPath("perso_mvt2_g.jpg"),rgb6,Ventre_hero1,Taille_hero1);
    NativeBitmap perso_mvt2_g(Ventre_hero1,Taille_hero1);
    perso_mvt2_g.setColorImage(0,0,rgb6,Ventre_hero1,Taille_hero1);
    delete[ ]rgb6;

    NativeBitmap Images_perso[6]={perso_statique_d,perso_statique_g,
                                  perso_mvt1_d, perso_mvt1_g, perso_mvt2_d, perso_mvt2_g};


        gametest(WindW,WindH,Ventre_hero1,Taille_hero1,Images_perso,1);
        fillRect(0,0,WindW,WindH,WHITE);
        gametest(WindW,WindH,Ventre_hero1,Taille_hero1,Images_perso,2);



    return 0;
}
