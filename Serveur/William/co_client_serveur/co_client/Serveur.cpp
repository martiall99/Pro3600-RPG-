#include "Serveur_E.h"
#include "debug.h"

using namespace std;

Serveur_E::Serveur_E(std::string dire)
{
	dir = dire;
	St1 = Ecrire_Fichier(300);
	St2 = Ecrire_Fichier(300);
	_1tS = Lire_Fichier(true, 300, true);
	_2tS = Lire_Fichier(true, 300, false);
}
bool Serveur_E::initS()
{
	St1.demarer(dir + "St1.txt");
	St2.demarer(dir + "St2.txt");
	demLecture();
	if ((!St1.continu) || (!St2.continu))
		return false;
	else
		return true;
}

bool Serveur_E::demLecture()
{
	_1tS.demarer(dir + "1tS.txt");
	_2tS.demarer(dir + "2tS.txt");
	if ((!_1tS.continu) || (!_2tS.continu))
		return false;
	else
		return true;
}

void Serveur_E::arretTemp()
{
	St1.arretUrgence();
	St2.arretUrgence();
	_1tS.arretUrgence();
	_2tS.arretUrgence();
}
void Serveur_E::arret()
{
	arretTemp();
	system("timeout 1");//on attend une seconde avant de vraiment arreter
	St1.DetrEcrire_Fichier();
	St2.DetrEcrire_Fichier();
	_1tS.DestrLire_Fichier();
	_2tS.DestrLire_Fichier();
}
void Serveur_E::envoi1(std::string mess)
{
	St1.ajoutAttente(mess);
}
void Serveur_E::envoi2(std::string mess)
{
	St2.ajoutAttente(mess);
}
bool Serveur_E::verif1()
{
	return(_1tS.continu && St1.continu);
}
bool Serveur_E::verif2()
{
	return(_2tS.continu && St2.continu);
}
