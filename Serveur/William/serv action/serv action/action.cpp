#include "action.h"
#include "debug.h"


#include "fauxPerso.h" // --------------------A SUPPRIMER !!!!

using namespace std;

Action::Action(int id, string nom, string desc)
{
    a_id = id;
    a_nom = nom;
    a_descr = desc;

}
string Action::toString()
{
	string s = to_string(a_id) + ";" + a_nom + ";" + a_descr;
		return s;
}

void Action::eff(Personnage &adv, Personnage &moi)
{
	debug("ERREUR, utilisation du eff() par defaut de Action");
}


bool Action::peutEff(Personnage &adv, Personnage &moi)
{
	debug("ERREUR , utilisation du peutEFF() par defaut de action");
	return false;
}


AttaqueGenerique::AttaqueGenerique(int id, std::string nom , std::string desc , int coutP, int dMin, int dMax) : Action(id, nom, desc)
{
	
	coutPa = coutP;
	minD = dMin;
	maxD = dMax;
}
bool AttaqueGenerique::peutEff(Personnage &adv, Personnage &moi)
{
	return (moi.aPA(coutPa));
}
bool AttaqueGenerique::eff(Personnage &adv, Personnage &moi)
{
	adv.recevoirDegats(minD, maxD);
	return moi.utiliserPa(coutPa);
}


MagieAttaqueGenerique::MagieAttaqueGenerique(int id , std::string nom , std::string desc , int coutP , int coutM , int dMin , int dMax ) :Action(id, nom, desc)
{
	coutPa = coutP;
	coutMana = coutM;
	minD = dMin;
	maxD = dMax;
}
bool MagieAttaqueGenerique::eff(Personnage &adv, Personnage &moi)
{
	adv.recevoirDegatsMagiques(minD, maxD);
	return (moi.utiliserPa(coutPa)&& moi.utiliserMana(coutMana));
}
bool MagieAttaqueGenerique::peutEff(Personnage &adv, Personnage &moi)
{
	return (moi.aPA(coutPa) && moi.aMana(coutMana));
}





