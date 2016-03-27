#ifndef CLIENT_E
#define CLIENT_E
#include "Lire.h"
#include "Ecr.h"

class Client_E
{
	std::string dir;
	int id;
	Ecrire_Fichier _1tS;
	Lire_Fichier St1;

public:
	Client_E(int idC, std::string dire = "D:/TEST_PRO3600/");
	bool initC();
	bool demLecture();
	void arretTemp();
	void arret();
	void envoiS(std::string mess);
	bool verif();
};

#endif