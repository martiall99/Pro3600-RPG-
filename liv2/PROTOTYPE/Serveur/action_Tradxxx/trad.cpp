#include "traducteur.h"
#include "../co_client/debug.h"

using namespace std;

TradActions::TradActions(Personnage *papa)
{
	erreur.ajParent(this);
	moi = papa;
}

bool TradActions::ajAction(int id_a, Action *ac)
{
	int d = rech(id_a);
	if (d != -1)
	{
		debug("ERREUR l'ID numero" + to_string(id_a) + "est deja presente dans le traducteur, case " + to_string(d));
		return false;
	}

	ID.push_back(id_a);
	act.push_back(ac);
	ac->ajParent(this);//on s'ajoute en parent de l'action qu'elle puisse acceder a nos Personnage moi, adv 
	return(verifStable());
}

int TradActions::rech(int id)//renvoie le numéro de la case du tableau correspondant a l id
{
	int l = ID.size();
	for (int i = 0; i < l; i++)
	{
		if (ID[i] == id)
		{
			return i;
		}
	}
	return -1;
}

void TradActions::viderTrad()
{
	int l = size();
	for (int i = 0; i < l; i++)
	{
		delete act[i];
		act[i] = 0;
	}
	ID.erase(ID.begin(), ID.end());// erase marche sur des iterators et nous rech() renvoie un int,
								   // donc on recupere le debut de la chaine et on rajoute le numeor de la case
	act.erase(act.begin(), act.end());

}

bool TradActions::enlAction(int id_a)
{
	int a = rech(id_a);
	if (a != -1)
	{
		debug("a= " + to_string(a));

		Action *b = act[a];
		delete b;
		act.at(a) = 0;

		ID.erase(ID.begin() + a);// erase marche sur des iterators et nous rech() renvoie un int,
								 // donc on recupere le debut de la chaine et on rajoute le numeor de la case
		act.erase(act.begin() + a);
		return(verifStable());
	}
	else
	{
		debug("Erreur on essaye d'enlever l'id " + to_string(id_a) + " qui n'existe pas dans le traducteur");
		return(verifStable());
	}
}


Action* TradActions::rechID(int id_r)// utilise rech() puis r'envoie le pointeur du deuxième tableau dans la même case 
{
	int a = rech(id_r);
	if (a == -1)
	{
		debug("Pas trouvé l'id " + to_string(id_r));
		return &erreur;
	}
	else
		return act.at(a);
}

string TradActions::listeID()
{
	int l = ID.size();
	string r = "";
	for (int i = 0; i < l; i++)
	{
		if(act[i]->peutEff())// on ne propose au client que ce qu'il peut effectivement faire !
			r += to_string(ID[i]) + ";";
	}
	return r;
}

string TradActions::toString()
{
	string r = "";
	int l = ID.size();
	for (int i = 0; i < l - 1; i++)// -1 car le dernier on lui rajoute pas "/"
	{
		r += act.at(i)->toString() + "/";
	}
	r += act.at(l - 1)->toString();
	return r;
}



bool TradActions::verifStable()
{
	int l = size();
	if (l == -1)
	{
		debug("ERREUR les tableaux act et ID n'ont pas la même taille");
		return false;
	}
	for (int i = 0; i < l; i++)
	{
		for (int j = i + 1; j < l; j++)
		{
			if (ID[i] == ID[j])
			{
				debug("ERREUR deux elements du traducteur ont même ID");
				return false;
			}
		}

	}
	return true;
}

int TradActions::size()
{
	int l = ID.size();
	int l2 = act.size();
	if (l != l2)
	{
		debug("ERREUR, les ID et act n'ont pas même taille");
		return -1;
	}
	else
		return l;
}



