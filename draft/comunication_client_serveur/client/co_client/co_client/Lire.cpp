#include "Lire.h"

using namespace std;
/*
void Lire_Fichier()
	{
		en_attente = list<string>();
		nom = "";
		lock = nom + ".nouv";
		att_ms = 200;
		continu = false;
	}
void arretUrgence()
	{
		continu = false;
	}
void DestrLire_Fichier()
	{
		continu = false;
	}
bool demarer(string file)
	{
		nom = file;
		if (fichExist(nom))
		{
			continu = true;
			//			timer_start(Lire_Fichier::lit, att_ms);
			return true;
		}
		return false;
	}
void lit()
	{
		if (continu)
		{
			if (fichExist(lock)) // si le fichier n a pas déjà été lu
				lireFich();
		}
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
bool lireFich()
	{
		if (!fichExist(nom + ".nouv")) // si le fichier a déjà été lu
		{
			cout << "ERREUR: pas de nouveau message pour: " + nom << endl;
			return false;
		}

		ifstream monFlux(nom.c_str());
		if (!monFlux)
		{
			cout << "ERREUR: Impossible de lire le fichier: " + nom << endl;
			return false;
		}
		string buffer = "";
		getline(monFlux, buffer);//normalement le fichier ne doit jamais contenir plus d'une ligne (donc + d'un message)

								 //DEBUG:
		cout << "on lit dans: " + nom + "la ligne: " + buffer << endl;

		en_attente.push_back(buffer);//on ajoute au FIFO
		monFlux.close();

		delFich(lock, true);//on supprime la "notification" de nouveau message pour laisser l'autre envoyer de nouveau

		return true;
	}


	*/
