#include "Client_E.h"
#include "debug.h"

using namespace std;

Client_E::Client_E(int idC, std::string dire)
{
	dir = dire;
	id = idC;
	_1tS = Ecrire_Fichier(300);
	if (id == 1)
		St1 = Lire_Fichier(300, true);
	else
		St1 = Lire_Fichier(300, false);
}
bool Client_E::initC()
{
	_1tS.demarer(dir + std::to_string(id) + "tS.txt");
	demLecture();
	if (!_1tS.continu)
		return false;
	else
		return true;
}
bool Client_E::demLecture()
{
	St1.demarer(dir + "St" + std::to_string(id) + ".txt");
	if (!St1.continu)
		return false;
	else
		return true;
}
void Client_E::arretTemp()
{
	St1.arretUrgence();
	_1tS.arretUrgence();
}
void Client_E::arret()
{
	arretTemp();
	system("timeout 1");//on attend une seconde avant de vraiment arreter
	_1tS.DetrEcrire_Fichier();
	St1.DestrLire_Fichier();
}
void Client_E::envoiS(std::string mess)
{
	_1tS.ajoutAttente(mess);
	debug("\n\nAJOUT");
}
bool Client_E::verif()
{
	debug(_1tS.continu, "C1->serv:");
	debug(St1.continu, "Serv-> C1:");
	return(_1tS.continu && St1.continu);
}
void Client_E::recoitS(std::string mess)
{
	debug("Transmis Serveur ->  Client1   :" + mess);
}