#include "Plateformes.h"


//on code le personnage depuis le coin haut gauche



int main() {
    openWindow(WindW,WindH);
    plateforme Niveau1_sol=plateforme(3,sol_segments_niveau_1());
    plateforme Niveau1_plafond=plateforme(1,plafond_segments_niveau_1());
    while(true){
        Niveau1_sol.draw();
        Niveau1_plafond.draw();
    }
    return 0;
}
