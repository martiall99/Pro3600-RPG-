#include "action.h"

using namespace std;

Action::Action(int id, string nom, string desc)
{
    a_id = id;
    a_nom = nom;
    a_descr = desc;
}

string Action::toString()
{
    string sortie;
    stringstream ss;
    ss << a_id;
    sortie = ss.str() + ";" + a_nom + ";" + a_descr;
    return(sortie);
}

AttaqueSimple::AttaqueSimple(int id, string nom, string desc)
{
    a_id = id;
    a_nom = nom;
    a_descr = desc;
}

void AttaqueSimple::eff(Personnage& Perso)
{
    Perso.recevoirDegats(10,15);
}

AttaquePuissante::AttaquePuissante(int id, string nom, string desc)
{
    a_id = id;
    a_nom = nom;
    a_descr = desc;
}

void AttaquePuissante::eff(Personnage& Perso)
{
    Perso.recevoirDegats(20,25);
}

Bouclier::Bouclier(int id, string nom, string desc)
{
    a_id = id;
    a_nom = nom;
    a_descr = desc;
}

void Bouclier::eff(Personnage& Perso)
{
    Perso.changerArmure(5,10);
}

PotionVie::PotionVie(int id, string nom, string desc, int regeneration)
{
    a_id = id;
    a_nom = nom;
    a_descr = desc;
    a_regeneration = regeneration;
}

void PotionVie::eff(Personnage& Perso)
{
    Perso.recevoirSoins(a_regeneration - 2,a_regeneration + 2);
}
