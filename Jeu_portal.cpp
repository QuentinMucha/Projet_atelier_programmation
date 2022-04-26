
#include "mvtperso.h"
#include "Plateformes.h"


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

//    putNativeBitmap (0,WindH/2, perso_statique_d);
//    putNativeBitmap (60,WindH/2, perso_statique_g);
//    putNativeBitmap (120,WindH/2, perso_mvt1_d);
//    putNativeBitmap (180,WindH/2, perso_mvt1_g);
//    putNativeBitmap (240,WindH/2, perso_mvt2_d);
//    putNativeBitmap (300,WindH/2, perso_mvt2_g);

    NativeBitmap Images_perso[6]={perso_statique_d,perso_statique_g,
                                  perso_mvt1_d, perso_mvt1_g, perso_mvt2_d, perso_mvt2_g};


    plateforme Niveau1_sol=plateforme(4,sol_segments_niveau_1());
    plateforme Niveau1_plafond=plateforme(1,plafond_segments_niveau_1());
    while(true){
        Niveau1_sol.draw(2);
        Niveau1_plafond.draw(1);
        gametest(WindW,WindH,Ventre_hero1,Taille_hero1,Images_perso);

    }
    Niveau1_plafond.destructeur();
    Niveau1_sol.destructeur();

    return 0;
}
