#include "Personnage.h"
#include "co_client\debug.h"

#include <cstdlib>//pour rand
#include <ctime> //pour rand
#include "test_classe_perso.h"


void initRand()
{
	srand(time(NULL)); // initialisation de rand pour les 2 personnages 
}


void test_p()
{
	debug("hello world");

	//test recevoir degats
	initRand();//init le rand pour linstant juste
	Personnage lala;
	Personnage lalo;

	lalo.regenPa();
	debug("Lolo\n" + lalo.caracs.toStringExplicit());
	debug("lala \n" + lala.caracs.toStringExplicit(), true);

	lala.recevoirDegatsMagiques(20, 30, lalo);
	lalo.recevoirDegats(0, 20, lala);
	lala.recevoirSoins(0, 2);

	lala.changerArmure(12);
	lalo.regenPa();

	lalo.utiliserPa(25);
	lalo.utiliserPa(2);

	lala.utiliserMana(200);
	lala.utiliserMana(20);
	debug("Lolo\n" + lalo.caracs.toStringExplicit());
	debug("lala \n" + lala.caracs.toStringExplicit());
}