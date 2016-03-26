#include "Ecr.h"
#include "chrono.h"
#include "debug.h"
using namespace std;
	

/*
	void Ecrire_Fichier()
	{
		en_attente = list<string>();
		nom = "";
		lock = nom + ".nouv";
		att_ms = 200;
		continu = false;
	}
	void ajoutAttente(string mess)
	{
		en_attente.push_back(mess);
	}
	void arretUrgence()
	{
		continu = false;
	}
	void DetrEcrire_Fichier()
	{
		continu = false;
		delFich(nom);
		delFich(lock);
	}
	bool demarer(string file)
	{
		nom = file;
		debug("creation " + file);
		if (creerVide(nom))
		{
			debug("ok");
			continu = true;
			//			timer_start(&ecrit);
			return true;
		}
		debug("Nok");
		return false;
	}

	bool creerVide(string name)
	{
		ofstream monFlux(name.c_str());
		if (!monFlux)
		{
			cout << "ERREUR: Impossible de créer le fichier: " + name << endl;
			return false;
		}
		monFlux.close();
		return true;
	}
	bool delFich(string name, bool aff = false)
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
	bool fichExist(string fich, bool aff = false)
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
	bool ecritDans(string mess)
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
	void ecrit()
	{
		if (continu)
		{
			if (en_attente.size() > 0)
			{
				if (!fichExist(lock)) // si le fichier a déjà été lu 
				{
					ecritDans(en_attente.front());
					en_attente.pop_front();
				}
			}
		}
	}

*/