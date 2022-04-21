
#include "mvtperso.h"
#include "Plateformes.h"


//on code le personnage depuis le coin haut gauche



int main() {
    openWindow(WindW,WindH);
    plateforme Niveau1_sol=plateforme(4,sol_segments_niveau_1());
    plateforme Niveau1_plafond=plateforme(1,plafond_segments_niveau_1());
    while(true){
        Niveau1_sol.draw(2);
        Niveau1_plafond.draw(1);
        gametest(WindW,WindH);

    }
    Niveau1_plafond.destructeur();
    Niveau1_sol.destructeur();

    return 0;
}
