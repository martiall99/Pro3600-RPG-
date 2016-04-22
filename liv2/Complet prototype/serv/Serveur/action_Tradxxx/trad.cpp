#include "traducteur.h"

using namespace std;

TradActions::TradActions()
{
}
string TradActions::toString()
{
	string r = "";
	if (attaqueSimple.a_id!=-1)//sinon nous renvoie aussi ceux qui sont pas initialisés
		r += attaqueSimple.toString() + "/";
	if (attaquePuissante.a_id != -1)
		r += attaquePuissante.toString() + "/";
	if (bouleFeu.a_id != -1)
		r += bouleFeu.toString() + "/";
	if (potionFaible.a_id != -1)
		r += potionFaible.toString() + "/";
	if (potionForte.a_id != -1)
		r += potionForte.toString() ;
	return(r);
}
string TradActions::listeID()
{
	string r = "";
	if (attaqueSimple.a_id != -1)//sinon nous renvoie aussi ceux qui sont pas initialisés
		r += "1;";
	if (attaquePuissante.a_id != -1)
		r += "2;";
	if (bouleFeu.a_id != -1)
		r += "3;";
	if (potionFaible.a_id != -1)
		r += "4;";
	if (potionForte.a_id != -1)
		r += "5;";

	return(r);// ATTENTION le ';' a la fin est NECESSAIRE
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





