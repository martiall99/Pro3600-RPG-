#ifndef Lir_E
#define Lir_E

#include <iostream>
#include <fstream>
#include <string> 
#include <list>




class Lire_Fichier
{

public:
	bool timer;
	bool continu;//sert a indiquer si fonctionne
	std::list<std::string> en_attente;
	std::string nom;
	std::string lock;
	int att_ms;
	bool num;//vaut vrai si =1 faux si =2 (differencier client 1 et 2 et ce quia rrive au serveur de  1 ou 2

public:
	Lire_Fichier(int att = 200, bool nu=true);
	void arretUrgence();
	void DestrLire_Fichier();
	void demarer(std::string file);
	void lit();
	void transmetC();
	void transmetS();
	bool verif();
private:
	bool delFich(std::string name, bool aff = false);
	bool fichExist(std::string fich, bool aff = false);
	bool lireFich();
	void LanceTimerLire(Lire_Fichier *func, unsigned int att_m);
	void deco();
};


#endif // !Lir
#pragma once
