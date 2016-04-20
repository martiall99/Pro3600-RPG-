#include "action.h"
#include "debug.h"


#include "fauxPerso.h" // --------------------A SUPPRIMER  et remplacer par le VRAI!!!!

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


bool MagieGenerique::enleverPAMana(Personnage &adv, Personnage &moi)
{
	return(moi.utiliserPa(coutPa) && moi.utiliserMana(coutMana));
}
MagieGenerique::MagieGenerique(int id, std::string nom, std::string desc, int coutP, int coutM) :Action(id, nom, desc)
{
	coutPa = coutP;
	coutMana = coutM;
}
bool MagieGenerique::peutEff(Personnage &adv, Personnage &moi)
{
	return (moi.aPA(coutPa) && moi.aMana(coutMana));
}

MagieAttaqueGenerique::MagieAttaqueGenerique(int id , std::string nom , std::string desc , int coutP , int coutM , int dMin , int dMax ) :MagieGenerique(id, nom, desc)
{
	coutPa = coutP;
	coutMana = coutM;
	minD = dMin;
	maxD = dMax;
}
bool MagieAttaqueGenerique::eff(Personnage &adv, Personnage &moi)
{
	adv.recevoirDegatsMagiques(minD, maxD);
	return enleverPAMana(adv,moi);
}


PotionGenerique::PotionGenerique(int id, std::string nom , std::string desc, int n): Action(id,nom,desc)
{
	nbr = n;
}
bool PotionGenerique::peutEff(Personnage &adv, Personnage &moi)
{
	return(nbr > 0);
}
void PotionGenerique::enlever1potion()
{
	if (nbr > 0)
		nbr--;
	else
		debug("ERREUR, demande d'enlever une potion alors qu'on en n'a plus aucune");

}




