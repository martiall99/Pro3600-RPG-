#include "Serveur.h"



Serveur::Serveur()
	{
		dir = "D:/TEST_PRO3600/";
		att_ms = 200;
	}
bool Serveur::initS()
	{
		debug("demar ST1=>");
		bool a = St1.demarer(dir + "St1.txt");
		ecrit_timer(St1, 10800);
		//St1.ecrit();

		//if (a = true)
		debug("ok ");
		debug("demar ST2=>");
		a = St2.demarer(dir + "St2.txt");
		if (a = true)
			debug("ok ");
		debug("demar lecture=>", true);
		//a = demLecture();
		if (a = true)
			debug("ok ");

		if ((!St1.continu) || (!St2.continu))
			return false;
		else
			return true;
	}

	/*
	bool Serveur::demLecture()
	{
	_1tS.demarer(dir + "1tS.txt");
	_2tS.demarer(dir + "2tS.txt");
	if ((!_1tS.continu) || (!_2tS.continu))
	return false;
	else
	return true;
	}
	*/
void Serveur::arretTemp()
	{
		St1.arretUrgence();
		St2.arretUrgence();
		//_1tS.arretUrgence();
		//_2tS.arretUrgence();
	}
void Serveur::arret()
	{
		St1.DetrEcrire_Fichier();
		St2.DetrEcrire_Fichier();
		//_1tS.arretUrgence();
		//_2tS.arretUrgence();
	}

void Serveur::ecrit_timer(Ecrire_Fichier fich, unsigned int att_ms)
	{
		std::thread(
			[&fich, att_ms]() //on capture toutes les variables en reference SAUF att_ms (ATTENTION)
		{
			while (true)
			{
				fich.ecrit();
				std::this_thread::sleep_for(std::chrono::milliseconds(att_ms));
			}
		}
		).detach();
	}
void Serveur::lit_timer(Lire_Fichier fich, unsigned int att_ms)
	{
		std::thread(
			[&fich, att_ms]() //on capture toutes les variables en reference SAUF att_ms (ATTENTION)
		{
			while (true)
			{
				fich.lit();
				std::this_thread::sleep_for(std::chrono::milliseconds(att_ms));
			}
		}
		).detach();
	}
Ecrire_Fichier Serveur::getSt1()
	{
		return St1;
	}