#include "action.h"
#include "../co_client/debug.h"

#include "traducteur.h"
#include "../Personnage.h"

using namespace std;

Action::Action(int id, string nom, string desc)
{

	a_id = id;
	a_nom = nom;
	a_descr = desc;
	parent = 0;
}

void Action::ajParent(TradActions *papa)
{
	parent = papa;
}

string Action::toString()
{
	string s = to_string(a_id) + ";" + a_nom + ";" + a_descr;
	return s;
}
bool Action::eff()
{
	stableSansCible();//annonce si en plus il y a un pb
	debug("ERREUR, utilisation du eff() par defaut de Action");
	return false;
}
bool Action::peutEff()
{
	stableSansCible();//annonce si en plus il y a un pb
	debug("ERREUR , utilisation du peutEFF() par defaut de action");
	return false;
}
bool Action::stableEtCible()
{
	if (!stableSansCible())
	{
		return false;
	}
	else if (parent->moi->cible == 0)
	{
		debug("ERREUR: Le personnage n'a pas de cible");
		return false;
	}
	return true;
}
bool Action::stableSansCible()
{
	if (parent == 0)
	{
		debug("ERREUR: l'action voulue n'a pas de traducteur parent");
		return false;
	}
	else if ((parent->moi == 0))
	{
		debug("ERREUR:traducteur n'est pas li� a un personnage");
		return false;
	}
	return true;
}

AttaqueGenerique::AttaqueGenerique(int id, std::string nom, std::string desc, int coutP, int dMin, int dMax) : Action(id, nom, desc)
{
	coutPa = coutP;
	minD = dMin;
	maxD = dMax;
}
bool AttaqueGenerique::peutEff()
{
	if (!stableEtCible())
		return false;
	else
	{
		Personnage *moi = parent->moi;
		return (moi->aPA(coutPa));
	}
}
bool AttaqueGenerique::eff()
{
	if (!stableEtCible())
		return false;
	else
	{
		Personnage *moi = parent->moi;
		Personnage *adv = parent->moi->cible;
		bool a = moi->utiliserPa(coutPa);
		if (a)
			adv->recevoirDegats(minD, maxD, *moi);
		return a;
	}
}


bool MagieGenerique::enleverPAMana()
{
	if (!stableEtCible())
		return false;
	else
	{
		Personnage *moi = parent->moi;
		return(moi->utiliserPa(coutPa) && moi->utiliserMana(coutMana));
	}
}
MagieGenerique::MagieGenerique(int id, std::string nom, std::string desc, int coutP, int coutM) :Action(id, nom, desc)
{
	coutPa = coutP;
	coutMana = coutM;
}
bool MagieGenerique::peutEff()
{
	if (!stableEtCible())
		return false;
	else
	{
		Personnage *moi = parent->moi;
		return (moi->aPA(coutPa) && moi->aMana(coutMana));
	}
}

MagieAttaqueGenerique::MagieAttaqueGenerique(int id, std::string nom, std::string desc, int coutP, int coutM, int dMin, int dMax) :MagieGenerique(id, nom, desc)
{
	coutPa = coutP;
	coutMana = coutM;
	minD = dMin;
	maxD = dMax;
}
bool MagieAttaqueGenerique::eff()
{
	if (!stableEtCible())
		return false;
	else
	{
		Personnage *moi = parent->moi;
		Personnage *adv = parent->moi->cible;
		bool a = peutEff();
		if (a)
		{
			enleverPAMana();
			adv->recevoirDegatsMagiques(minD, maxD, *moi);
		}
		return a;
	}
}


PotionGenerique::PotionGenerique(int id, std::string nom, std::string desc, int n) : Action(id, nom, desc + ": " + to_string(n) + "sur" + to_string(n))
{
	nbr = n;
	nbrInit = n;
}
bool PotionGenerique::peutEff()
{
	if (!stableEtCible())
		return false;
	else
	{
		return(nbr > 0);
	}
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

PotionSoinGenerique::PotionSoinGenerique(int id, std::string nom, std::string desc, int n, int soinm, int soinM) : PotionGenerique(id, nom, desc, n)
{
	healMin = soinm;
	healMax = soinM;
}
bool PotionSoinGenerique::eff()
{
	if (!stableEtCible())
		return false;
	else
	{
		Personnage *moi = parent->moi;
		bool a = enlever1potion();
		if (a)
		{
			moi->recevoirSoins(healMin, healMax);
			return true;
		}
		else
		{
			return false;
		}
	}
}
