#include "trad_attaq.h"

using namespace std;

Trad_attaq::Trad_attaq()
{
    AttaqueSimple a_1(1,"Attaque simple", "L'attaque de base du jeu.");
    AttaquePuissante a_2(2,"Attaque puissante", "Une attaque qui inflige plus de degats que l'attaque simple.");
    Bouclier a_3(3,"Bouclier", "Reduits les prochains degats recus.");
    Action no_action(0,"","");
}

Action Trad_attaq::rechID(int id_r)
{
    if(id_r == 1)
        return(a_1);
    if(id_r == 2)
        return(a_2);
    if(id_r == 3)
        return(a_3);
    return(no_action);
}

string Trad_attaq::listeID()
{
    return("1;2;3");
}

string Trad_attaq::toString()
{
    string sortie;
    sortie = a_1.toString() + "/" + a_2.toString() + "/" + a_3.toString();
    return(sortie);
}
