#include "maitre_jeu.h"

maitre_jeu::maitre_jeu()
{
    num_coup_attendu=0;
    a_qui_jouer=ID_1;
    perso1(); //on rappelle les constructeurs au cas ou
    perso2();
    j_1_co=false;
    j_2_co=false;
    deb_tour=true;
}

void maitre_jeu::initBibli()
{
    string chaine_a_envoyer;
    chaine_a_envoyer = attaques.toString() + "." + magies.toString() + "." + objets.toString();
    aiguillage.envBibli(chaine_a_envoyer);
}

void maitre_jeu::debutJeu()
{
    perso1.initTraducteurs();
    perso2.initTraducteurs();

    aiguillage.envEtats(perso1.etatsPerso);
    aiguillage.envEtats(perso2.etatsPerso);

    aiguillage.envDeb();

    debTour();
}

int maitre_jeu::aGagne()
{
    if(perso1.PV <= 0)
        return ID_2;
    if(perso2.PV <= 0)
        return ID_1;
    return -1;
}

void maitre_jeu::debTour()
{
    perso1.regenPA();
    perso2.regenPA();
    maitre_jeu::tour();
}

void maitre_jeu::recoitT3A(int num_coup, int id_j, string ac)
{
    if(id_j == a_qui_jouer && num_coup == num_coup_attendu) {
            num_coup_attendu ++;
            if(id_j == ID_1) {
                aiguillage.retransmet3(ac);
                perso1.Act(ac);
            }
            if(id_j == ID_2) {
                aiguillage.retransmet3(ac);
                perso2.Act(ac);
            }
    }

}

void maitre_jeu::co(int id)
{
    if(j_1_co == false)
        j_1_co = true;
    if(j_2_co == false)
        j_2_co = true;
    aiguillage.envID();
    debutJeu();
}

void maitre_jeu::deco(int id)
{
    aiguillage.envFin(0);
}

void changeAQuiJouer()
{
    if(a_qui_jouer == ID_1)
        a_qui_jouer = ID_2;
    if(a_qui_jouer == ID_2)
        a_qui_jouer = ID_1;
}

void maitre_jeu::tour()
{
    if(aGagne() != -1) {
        aiguillage.envFin(aGagne());
    } else {

        aiguillage.envEtats(perso1.etatsPerso());
        aiguillage.envEtats(perso2.etatsPerso());

        if(a_qui_jouer == ID_1)
            aiguillage.envActs(perso1.listeActionsPos, ID_1);
        if(a_qui_jouer == ID_2)
            aiguillage.envActs(perso2.listeActionsPos, ID_2);
    }
}
