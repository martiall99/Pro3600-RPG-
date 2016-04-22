#include "traducteur.h"

using namespace std;

TradActions::TradActions()
{
	 attaqueSimple= AttaqueGenerique(1, "Attaque simple", "[5-25] pour 2 PA", 2, 5, 25);
	 attaquePuissante= AttaqueGenerique(2, "Attaque puissante", "[20-45] pour 4 PA", 4, 20, 45);
	 bouleFeu=MagieAttaqueGenerique(3, "Boule de feu", "[35-75] pour 2 PA et 25 mana", 2, 25, 35, 75);
	 potionFaible = PotionSoinGenerique(4, "Potion de soin faible", "[5,10] par potion", 5, 5, 10);
	 potionForte = PotionSoinGenerique(5, "Potion de soin puissante", "[15,40] par potion", 2, 15, 40);
}
string TradActions::toString()
{
	return( attaqueSimple.toString() + "/" + attaquePuissante.toString() + "/"  + bouleFeu.toString() + "/"  + potionFaible.toString() + "/" + potionForte.toString() );
}
string TradActions::listeID()
{
	return("1;2;3;4;5;");// ATTENTION le ';' a la fin est NECESSAIRE
}
Action* TradActions::rechID(int id_r)
{
	if (id_r == 1)
		return (&attaqueSimple);
	else if (id_r == 2)
		return (&attaquePuissante);
	else if (id_r == 3)
		return (&bouleFeu);
	else if (id_r == 4)
		return (&potionFaible);
	else if (id_r == 5)
		return (&potionForte);
	else
	{
		return (&erreur);
	}
}





