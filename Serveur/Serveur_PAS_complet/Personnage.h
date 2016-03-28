#pragma once


#include "Conteneurs_carac_action\Conteneur_carac.h"
#include "Conteneurs_carac_action\conteneurAction.h"

#include "action_Tradxxx\trad_attaq.h"

//personnage
class Personnage
{
private:
	Conteneur_carac caracs;
public://ouioui ce sont bien ses variables
	
	Trad_attaq attaques;
	/*
	Trad_magie magies;
	Trad_obj objets;
	*/
public:
	void recevoirDegats(int min, int max);// utilise aleat() et implemente la formule de degats (qui depend de la DEF de ce perso) qu'on avait mise dans le liv1
	void recevoirDegatsMagiques(int min, int max);// meme chose avec RES 
	void recevoirSoins(int min, int max);
	void changerArmure(int ajMin, int ajMax);
	void regenPa();
	bool utiliserPa(int coutPa); //renvoie true si le personnage a assez de Pa et les soustrait
	bool utiliserMana(int coutMana); //renvoie true si le personnage a assez de mana et la soustrait
	void Act(std::string a);// SI l'action ac ="00" => changeAQuiJouer() de maitre_jeu  , SINON utilise rechID() des 4 traducteurs puis effectue la bonne action puis lance tour() 
	void initTraducteurs();// ICI elle ne FAIT RIEN DU TOUT (dans le livrable 3 ce sera pas le cas), elle n'est PAS appelée par le constructeur 
	std::string listeActionsPos(int id_j);//on recupere les 3 attaques.listeID(), magies.listeID(), objets.listeID()  et on les concatène avec en séparateur ' /  '
	std::string etatsPerso();//recupere le caracs.toString() et sépare par ' . '

	int aleat(int min, int max); // utiliser rand pour faire un nombre aleat entre min et max https://openclassrooms.com/courses/l-aleatoire-en-c-et-c-se-servir-de-rand-1
};

