#include "Personnage.h"
#include "co_client\debug.h"

#include <cstdlib>
#include <ctime> 

using namespace std;

Personnage::Personnage( string name, int pv, int mana, int pa, int def, int res, int cri, int esq, int renv)
{
	caracs = { pv, mana, pa, def, res, cri, esq, renv };
	nom = name;

}


int Personnage::aleat(int min, int max) // utiliser rand pour faire un nombre aleat entre min et max https://openclassrooms.com/courses/l-aleatoire-en-c-et-c-se-servir-de-rand-1
{
	int nombre_aleatoire = 0;
	nombre_aleatoire = rand() % (abs(max - min));
	nombre_aleatoire += min;
	//debug(nombre_aleatoire);
	return (nombre_aleatoire);
}

void Personnage::recevoirDegats(int min, int max,  Personnage &source)// utilise aleat() et implemente la formule de degats (qui depend de la DEF de ce perso) qu'on avait mise dans le liv1
{
	int cr = aleat(0, 100);//on tire 3 nombres aleat entre 0 100 puis on comparera a la valeur de la carac corespondante
	int esq = aleat(0, 100);//si c'est inferieure a celle ci c'est que lecomportement spécial est appliqué
	int ren = aleat(0, 100);

	int def = aleat(1, caracs.DEF);//je rand la defense aussi
	int a = aleat(min, max);

	if (esq < caracs.ESQ)//si il y a esquive
	{
		debug(nom+" esquive !");
		return;
	}
	else if (ren < caracs.RENV)
	{
		debug(nom+" renvoie les degats !");
		return(source.recevoirDegats(min, max, *this));//on renvoie les degats vers l'attaquant
	}
	else if (cr < caracs.CRIT)
	{
		debug(nom+" attaque critique !");
		a *= 3;//on multiplie els degats infligés par 3 si il y a coup critique
	}

//	debug(nom+" pv avant: " + to_string(caracs.PV) + " rand degats: " + to_string(a));
	if (def != 0)
		caracs.PV -= a * (1 - (double)def / 100.0);//attaque randomisée pondérée par 1-defense (avec defense un rand en %age )
	else
		caracs.PV -= a;
//	debug(" pv apres" + to_string(caracs.PV));
}

void Personnage::recevoirDegatsMagiques(int min, int max, Personnage &source)// meme chose avec RES 
{
	int cr = aleat(0, 100);//on tire 3 nombres aleat entre 0 100 puis on comparera a la valeur de la carac corespondante
	int esq = aleat(0, 100);//si c'est inferieure a celle ci c'est que lecomportement spécial est appliqué

	int res = aleat(1, caracs.RES);//je rand la defense aussi
	int a = aleat(min, max);

	if (esq < caracs.ESQ)//si il y a esquive
	{
		debug(nom + " esquive !");
		return;
	}	
	else if (cr < caracs.CRIT)
	{
		debug(nom+" attaque critique !");
		a *= 3;//on multiplie els degats infligés par 3 si il y a coup critique
	}

//	debug(nom+" pv avant: " + to_string(caracs.PV) + " rand degats: " + to_string(a));
	if (res != 0)
		caracs.PV -= a * (1 - (double)res / 100.0);//attaque randomisée pondérée par 1-defense (avec defense un rand en %age )
	else
		caracs.PV -= a;
//	debug(" pv apres" + to_string(caracs.PV));

}

void Personnage::recevoirSoins(int min, int max)
{
	int a = aleat(min, max);
//	debug(nom+" pv avant: " + to_string(caracs.PV) + " rand soins: " + to_string(a));
	caracs.PV += a;//rmq pour linstant on peut se soigner au dessus de sa vie initiale ...
//	debug(" pv apres" + to_string(caracs.PV));
}

void Personnage::changerArmure(int nouv)
{
	debug("---\nChangement armure , ancienne def " + to_string(caracs.DEF) + ", nouvelle " + to_string(nouv));
	caracs.DEF = nouv;
}

void Personnage::regenPa()
{
	//pour lisntant c'est la regen de base
	caracs.PA += REGEN_PA_INIT;
}

bool Personnage::utiliserPa(int coutPa) //renvoie true si le personnage a assez de Pa et les soustrait
{
	if (aPA(coutPa))
	{
		debug("PA suffisants => OK pour " + to_string(coutPa));
		caracs.PA -= coutPa;
		return true;
	}
	else
	{
		debug("NON : PA INsuffisants: "+to_string(caracs.PA)+" < " +to_string(coutPa));
		return false;
	}

}

bool  Personnage::utiliserMana(int coutMana) //renvoie true si le personnage a assez de mana et la soustrait
{
	if (aMana(coutMana))
	{
		debug("mana suffisants => OK pour " + to_string(coutMana));
		caracs.Mana -= coutMana;
		return true;
	}
	else
	{
		debug("NON : mana INsuffisants: " + to_string(caracs.Mana) + " < " + to_string(coutMana));
		return false;
	}

}

void Personnage::initTraducteurs()
{
	attaques.attaqueSimple = AttaqueGenerique(1, "Attaque simple", "[5-25] pour 2 PA", 2, 5, 25);
	attaques.attaquePuissante = AttaqueGenerique(2, "Attaque puissante", "[20-45] pour 4 PA", 4, 20, 45);
	magies.bouleFeu = MagieAttaqueGenerique(3, "Boule de feu", "[35-75] pour 2 PA et 25 mana", 2, 25, 35, 75);
	objets.potionFaible = PotionSoinGenerique(4, "Potion de soin faible", "[5,10] par potion", 5, 5, 10);
	objets.potionForte = PotionSoinGenerique(5, "Potion de soin puissante", "[15,40] par potion", 2, 15, 40);
}

string Personnage::listeActionsPos()//on recupere les 3 attaques.listeID(), magies.listeID(), objets.listeID()  et on les concatène sans séparateur (il est deja ajoute par les traducteurs)
{
	
	string r = "";
	
	r = attaques.listeID() + magies.listeID() + objets.listeID();
	
	
	return r;
}

string Personnage::etatsPerso()//recupere le caracs.toString() 
{
	return(caracs.toString());
}

bool Personnage::aPA(int pa)
{
	if (caracs.PA >= pa)
		return(true);
	else
		return false;
}
bool Personnage::aMana(int man)
{
	if (caracs.Mana >= man)
		return(true);
	else
		return false;
}









