#include "Lire.h"
#include "debug.h"
#include "chrono.h"


using namespace std;

Lire_Fichier::Lire_Fichier(int att, bool nu)
{
	en_attente = list<string>();
	num = nu;
	nom = "";
	lock = nom + ".nouv";
	att_ms = att;
	continu = false;
	timer = false;
}
void Lire_Fichier::arretUrgence()
	{
		timer = false;
		continu = false;
	}
void Lire_Fichier::DestrLire_Fichier()
	{
		timer = false;
		continu = false;
	}
void Lire_Fichier::demarer(string file)
	{
		nom = file;
		lock = nom + ".nouv";
		timer = true;
		LanceTimerLire(this, att_ms);
		verif();
		
	}
bool Lire_Fichier::verif()
{
	if (fichExist(nom))
	{
		continu = true;
		return true;
	}
	else
	{
		if (continu)//si on avait la connexion avant
			deco();

		continu = false;
		return false;
	}
}

void Lire_Fichier::lit()
	{
		if (continu)
		{
			if (fichExist(lock)) // si le fichier n a pas déjà été lu
			{
				lireFich();
			}
		}
	}
bool Lire_Fichier::delFich(string name, bool aff )
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
bool Lire_Fichier::fichExist(string fich, bool aff )
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
bool Lire_Fichier::lireFich()
	{
		if (!fichExist(lock)) // si le fichier a déjà été lu
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
		en_attente.push_back(buffer);//on ajoute au FIFO
		monFlux.close();

		delFich(lock, true);//on supprime la "notification" de nouveau message pour laisser l'autre envoyer de nouveau

		return true;
	}
void Lire_Fichier::LanceTimerLire(Lire_Fichier *func, unsigned int att_m)
{
	std::thread(
		[func, att_m]() //on capture toutes les varaibles 
	{
		while (func->timer)
		{	
			func->verif();						
			if (func->continu)
			{
				func->lit();				
				func->transmetC();				
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(att_m));
		}
	}
	).detach();
}

void Lire_Fichier::transmetC()//transfere le texte du message à decodeTypeMessage()
{
	while (!en_attente.empty())
	{
		string a = en_attente.front();
		en_attente.pop_front();
		//decodeTypeMessage(a);
		//debug("Transmis Serveur -> Client :" + a);
	}
}



//CELLES qui suivent on les met dans le main.cpp !

/*
void Lire_Fichier::transmetC()//transfere le texte du message à decodeTypeMessage()
{
	while (!en_attente.empty())
	{
		string a = en_attente.front();
		en_attente.pop_front();
		//decodeTypeMessage(a);
		debug("Transmis Serveur -> Client :" + a);
	}
}
void Lire_Fichier::deco()//appelé lorsque le serveur se deco (pb connexion) , lance servPerdu()
{
//servPerdu();
debug("Perte du serveur" );

}

*/