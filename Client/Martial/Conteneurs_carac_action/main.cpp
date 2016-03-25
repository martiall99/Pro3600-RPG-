#include <iostream>
#include "conteneurAction.h"
#include "Conteneur_carac.h"

using namespace std;



int main()
{
    Cont_action conteneur = {"Titre","type","descr"};
    cout << conteneur.toString() << endl;

    Conteneur_carac conteneur1 = {"PV","Mana","PA","DEF","RES",
     "CRIT", "ESQ", "RENV"};
     cout << conteneur1.toString() << endl;

    return 0;

}
