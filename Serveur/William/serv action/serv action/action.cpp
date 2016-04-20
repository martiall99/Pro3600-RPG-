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
bool Action::eff(Personnage &adv, Personnage &moi)
{
	debug("ERREUR, utilisation du eff() par defaut de Action");
	return false;
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
	bool a = moi.utiliserPa(coutPa);
	if (a)
		adv.recevoirDegats(minD, maxD);
	return a ;
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
	bool a = enleverPAMana(adv, moi);
	if (a)
		adv.recevoirDegatsMagiques(minD, maxD);
	return a ;
}


PotionGenerique::PotionGenerique(int id, std::string nom , std::string desc, int n): Action(id,nom,desc+ ": "+to_string(n)+"sur"+to_string(n))
{
	nbr = n;
	nbrInit = n;
}
bool PotionGenerique::peutEff(Personnage &adv, Personnage &moi)
{
	return(nbr > 0);
}
bool PotionGenerique::enlever1potion()
{
	if (nbr > 0) 
	{
		nbr--;
		string r = a_descr;
		int a = r.find_last_of(':');
		r.erase(a);
		r.append(":" + to_string(nbr) + "sur" + to_string(nbrInit));
		a_descr = r;
		return true;
	}
	else
	{
		debug("ERREUR, demande d'enlever une potion alors qu'on en n'a plus aucune");
		return false;
	}

}
int PotionGenerique::nbrRestant()
{
	return(nbr);
}

PotionSoinGenerique::PotionSoinGenerique(int id, std::string nom, std::string desc, int n ,int soinm, int soinM): PotionGenerique(id, nom, desc, n)
{
	healMin = soinm;
	healMax = soinM;
}
bool PotionSoinGenerique::eff(Personnage &adv, Personnage &moi)
{
	bool a = enlever1potion();
	if (a)
	{
		moi.recevoirSoins(healMin, healMax);
		return true;
	}
	else
	{
		return false;
	}	
}
