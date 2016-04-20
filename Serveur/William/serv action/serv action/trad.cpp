#include "traducteur.h"


TradActions::TradActions()
{
	 AttaqueSimple= AttaqueGenerique(1, "Attaque simple", "[5-25] pour 2 PA", 2, 5, 25);
	 AttaquePuissante= AttaqueGenerique(2, "Attaque puissante", "[20-45] pour 4 PA", 4, 20, 45);
	 BouleFeu=MagieAttaqueGenerique(3, "Boule de feu", "[35-75] pour 2 PA et 25 mana", 2, 25, 35, 75);
}