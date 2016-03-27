#ifndef MAITRE_JEU_H
#define MAITRE_JEU_H

#include "personnage.h"
#include "aiguillage.h"
#include <iostream>
#include <string>

class maitre_jeu
{
    public:

        maitre_jeu();

        //util par aiguillage
        void recoitT3A(int num_coup, int id_j, std::string ac);//verifie id et num_coup, puis incremente  num_coup_attendu, puis retransmet3() puis Act() de personnage

        //util par transfert
        void co(int id);//SI j_1_co==false le met a true        OU           SI j_2_co==false le met a vrai ET et lance envID() ET lance debutJeu()
        void deco(int id);// arrete le jeu avec un envFin() avec en id 0 pour dire que c'est une erreur/pas de gagnant

        //util par perso
        void changeAQuiJouer();// change id puis SI deb_tour==true met deb_tourà false et lance debTour() SINON met deb_tour à true et lance tour();
        void tour();// 0) regarde a_qui_jouer ( PUIS vérifie aGagne() , interromp tout et envFin() si c'est le cas ) puis  1)recupere etatsPersos()  2) envEtats 3)recupere listeActionsPos() du bon joueur  puis 4) envActs() au bon joueur

    private:

        void initBibli();// on récupère les 3  attaques.toString(), magies.toString(), objets.toString()   puis appelle envBibli()
        void debutJeu();// 1) initTraducteurs() des 2 persos 2) initBibli() , 3)etatsPersos() des 2 puis envEtats()  4)  envDeb() 5) debTour()
        int aGagne();//renvoie l'id du joueur qui a gagné (joueur adverse a PV<=0 ) ou  -1 si
        void debTour();//applique le  regenPA  de chaque personnage, puis lance tour()

        int num_coup_attendu;
        int a_qui_jouer;
        Personnage perso1;
        Personnage perso2;
        bool j_1_co;
        bool j_2_co;
        bool deb_tour;
};

#endif // MAITRE_JEU_H
