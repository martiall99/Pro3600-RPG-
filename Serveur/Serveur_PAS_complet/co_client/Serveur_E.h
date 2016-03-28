#ifndef SERVE_E
#define SERVE_E

#include "Lire.h"
#include "Ecr.h"

class Serveur_E
{
public:
	std::string dir;
	Ecrire_Fichier St1;
	Ecrire_Fichier St2;
	Lire_Fichier _1tS;
	Lire_Fichier _2tS;

public:
	Serveur_E(std::string dire = "D:/TEST_PRO3600/");
	bool initS();

	bool demLecture();

	void arretTemp();
	void arret();
	void envoi1(std::string mess);
	void envoi2(std::string mess);
	bool verif1();
	bool verif2();
};

#endif

