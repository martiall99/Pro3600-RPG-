#include "fauxPerso.h"
#include "debug.h"
using namespace std;

Personnage::Personnage(std::string n)
{
	nom = n;
}
void Personnage::recevoirDegats(int min, int max)// utilise aleat() et implemente la formule de degats (qui depend de la DEF de ce perso) qu'on avait mise dans le liv1
{
	debug(nom + " recoit degats [ " + to_string(min) + "," + to_string(max) + "]");
}

void Personnage::recevoirDegatsMagiques(int min, int max)
{
	debug(nom + " recoit degats Mag [ " + to_string(min) + "," + to_string(max) + "]");
}// meme chose avec RES 
void Personnage::recevoirSoins(int min, int max)
{
	debug(nom + " recoit soins [ " + to_string(min) + "," + to_string(max) + "]");
}
void Personnage::changerArmure(int nouv)
{
	debug(nom + " chang armure , nouv: " + to_string(nouv) );
}

bool Personnage::aPA(int pa)
{
	return(true);
}
bool Personnage::utiliserPa(int coutPa) //renvoie true si le personnage a assez de Pa et les soustrait
{
	debug(nom + " utilise " + to_string(coutPa)+" PA");
	return(aPA(coutPa));
}

bool Personnage::aMana(int man)
{
	return(true);
}
bool Personnage::utiliserMana(int man)
{
	debug(nom + " utilise " + to_string(man)+" Mana");
	return(aMana(man));
}


