#include "debug.h"
#include "action.h"
#include "fauxPerso.h"


using namespace std;



int main()
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
	debug("\nsans erreur =>");
	atq = { 12,"attaque","zou",5,20,25 };
	debug(atq.toString());
	atq.eff(perso1, perso2);


	debug("fin", true);
	return 0;

}