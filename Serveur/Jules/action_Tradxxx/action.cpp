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

void AttaqueSimple::eff(Personnage& Cible, Personnage& Lanceur)
{
    if(Lanceur.utiliserPa(2))
        Cible.recevoirDegats(10,15);
}

AttaquePuissante::AttaquePuissante(int id, string nom, string desc)
{
    a_id = id;
    a_nom = nom;
    a_descr = desc;
}

void AttaquePuissante::eff(Personnage& Cible, Personnage& Lanceur)
{
    if(Lanceur.utiliserPa(4))
        Cible.recevoirDegats(20,25);
}

Bouclier::Bouclier(int id, string nom, string desc)
{
    a_id = id;
    a_nom = nom;
    a_descr = desc;
}

void Bouclier::eff(Personnage& Cible, Personnage& Lanceur)
{
    if(Lanceur.utiliserPa(3))
        Cible.changerArmure(5,10);
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
    Perso.recevoirSoins(a_regeneration,a_regeneration);
}

Magie::Magie(int id,std::string nom, std::string desc, int regeneration, int degats, int mana, int pa)
{
    a_id = id;
    a_nom = nom;
    a_descr = desc;
    a_regeneration = regeneration;
    a_degats = degats;
    a_mana = mana;
    a_pa = pa;
}

Magie::eff(Personnage& Cible, Personnage& Lanceur)
{
    if(Lanceur.utiliserPa(a_pa) && Lanceur.utiliserMana(a_mana)) {
        Cible.recevoirSoins(a_regeneration, a_regeneration);
        Cible.recevoirDegatsMagiques(a_degats, a_degats);
    }
}
