#include "debug.h"
#include "traducteur.h"
#include "fauxPerso.h"


using namespace std;



void test_persActions()
{
	debug("hello world");

	Action ac;
	ac = {};

	Personnage perso1("p1");
	Personnage perso2("p2");

	debug("\n---test persos");
	perso1.utiliserMana(5);
	perso1.utiliserPa(6);
	perso1.changerArmure(3);
	perso2.recevoirDegats(1, 5);
	perso2.recevoirDegatsMagiques(20, 35);
	perso1.recevoirSoins(7, 8);

	debug("\n---test action");
	debug("par defaut : => erreur normalement");
	debug(ac.toString());
	ac.eff(perso1,perso2);
	ac = { 5,"action","description" };
	AttaqueGenerique atq;
	debug(atq.toString());
	atq.eff(perso1, perso2);
	debug("\n attaque sans erreur =>");
	atq = { 12,"attaque","zou",5,20,25 };
	debug(atq.toString());
	atq.eff(perso1, perso2);
	MagieAttaqueGenerique mag = { 25,"magie offensive", "zlaam", 5,30,45,70 };
	debug("\nmagie =>");
	debug(mag.toString());
	mag.eff(perso1, perso2);
	PotionSoinGenerique pot = { 13, "Potion de vie", "Regen [5-30] par potion", 2, 5, 30 };
	debug("\npotion =>");
	debug(pot.toString());
	pot.eff(perso1, perso2);
	debug(pot.toString());
	pot.eff(perso1, perso2);
	debug(pot.toString());
	pot.eff(perso1, perso2);

	debug("fin", true);
}

int main()
{

	//test_persActions();
	Personnage p1("p1");
	Personnage p2("p2");
	TradActions trad;
	debug("initialisation traducteur");
	debug(trad.listeID());
	debug(trad.toString());
	debug("\nutilisation traducteur");
	Action *a=0;
	for (int i = 0; i < 6; i++)
	{
		a= trad.rechID(i);
		debug(a->toString());
		a->eff(p1, p2);
		debug(" ");
	}
	debug("FIN au prochain appui", true);
	return 0;
}