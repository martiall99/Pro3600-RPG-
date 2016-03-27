#ifndef ECR
#define ECR


#include <iostream>
#include <fstream>
#include <string> 
#include <list>




class Ecrire_Fichier
{
public:
bool continu;//sert a indiquer si fonctionne
std::list<std::string> en_attente;
std::string nom;
std::string lock;
unsigned int att_ms;

public:
	Ecrire_Fichier(int att = 200);
void ajoutAttente(std::string mess);
void arretUrgence();
void DetrEcrire_Fichier();
bool demarer(std::string file);
bool fichExist(std::string fich, bool aff = false);
void ecrit();

private:
bool creerVide(std::string name);
bool delFich(std::string name, bool aff = false);
bool ecritDans(std::string mess);
void LanceTimerEcrire(Ecrire_Fichier *func, unsigned int att_ms);
};

#endif // !ECR
