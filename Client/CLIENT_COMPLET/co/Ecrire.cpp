#include "Ecr.h"
#include "chrono.h"
#include "debug.h"
using namespace std;
	


Ecrire_Fichier::Ecrire_Fichier(int att)
	{
		en_attente = list<string>();
		nom = "";
		lock = nom + ".nouv";
		att_ms = att;
		continu = false;
	}
void Ecrire_Fichier::ajoutAttente(string mess)
	{
		en_attente.push_back(mess);
	}
void Ecrire_Fichier::arretUrgence()
	{
		continu = false;
	}
void Ecrire_Fichier::DetrEcrire_Fichier()
	{
		continu = false;
		delFich(nom);
		delFich(lock);
	}
bool Ecrire_Fichier::demarer(string file)
	{
		nom = file;
		lock = nom + ".nouv";
		if (creerVide(nom))
		{
			continu = true;
			LanceTimerEcrire(this, att_ms);
			return true;
		}
		return false;
	}

bool Ecrire_Fichier::creerVide(string name)
	{
		ofstream monFlux(name.c_str());
		//debug((bool)monFlux, "Flux ecrire client");
		if (!monFlux)
		{
			cout << "ERREUR: Impossible de créer le fichier: " + name << endl;
			return false;
		}
		monFlux.close();
		return true;
	}
bool Ecrire_Fichier::delFich(string name, bool aff )
	{
		int i = remove(name.c_str());
		if (i != 0)
		{
			if (aff)
				cout << "ERREUR: Impossible de supprimer le fichier: " + name << endl;
			return false;
		}
		return true;

	}
bool Ecrire_Fichier::fichExist(string fich, bool aff)
	{
		ifstream monFlux(fich.c_str());
		if (!monFlux)
		{
			if (aff)
				cout << "ERREUR: Impossible d'ouvrir le fichier: " + fich << endl;
			return false;
		}
		monFlux.close();
		return true;
	}
bool Ecrire_Fichier::ecritDans(string mess)
	{
		ofstream monFlux(nom.c_str());
		if (!monFlux)
		{
			cout << "ERREUR: Impossible d'écrire dans le fichier: " + nom << endl;
			return false;
		}
		monFlux << mess << endl;
		monFlux.close();

		creerVide(lock);//on signale un nouveau message


		return true;
	}
void Ecrire_Fichier::ecrit()
	{
		if (continu)
		{
			if (!en_attente.empty())
			{
				if (!fichExist(lock)) // si le fichier a déjà été lu 
				{
					debug("---------------------------------------Ecrit------------------");
					ecritDans(en_attente.front());
					en_attente.pop_front();
				}
			}
		}
	}

void Ecrire_Fichier::LanceTimerEcrire(Ecrire_Fichier *func, unsigned int att_m)
{
	std::thread(
		[func, att_m]() //on capture toutes les varaibles 
	{
		while (func->continu)
		{
			func->ecrit();
			std::this_thread::sleep_for(std::chrono::milliseconds(att_m));
		}
	}
	).detach();
}

