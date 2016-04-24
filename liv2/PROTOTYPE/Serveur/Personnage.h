#pragma once


#include "Conteneurs_carac_action\Conteneur_carac.h"
#include "Conteneurs_carac_action\conteneurAction.h"

#include "action_Tradxxx\traducteur.h"

#define REGEN_PA_INIT 55 //nbr par tour

//personnage
class Personnage
{
public:
	Conteneur_carac caracs;
	Personnage *cible;
public://ouioui ce sont bien ses variables
	
	TradActions attaques;	
	TradActions magies;
	TradActions objets;
	std::string nom;
	
public:
	Personnage(std::string name = "Sans nom", int pv = 1000, int mana = 100, int pa = 0, int def = 5, int res = 3, int cri = 7, int esq = 6, int renv = 2);
	~Personnage();
	void recevoirDegats(int min, int max, Personnage &source);// utilise aleat() et implemente la formule de degats (qui depend de la DEF de ce perso) qu'on avait mise dans le liv1
	void recevoirDegatsMagiques(int min, int max, Personnage &source);// meme chose avec RES 
	void recevoirSoins(int min, int max);
	void changerArmure(int aj);
	void regenPa();
	bool utiliserPa(int coutPa); //renvoie true si le personnage a assez de Pa et les soustrait
	bool utiliserMana(int coutMana); //renvoie true si le personnage a assez de mana et la soustrait
	void Act(std::string a, Personnage &adv);// SI l'action ac ="00" => changeAQuiJouer() de maitre_jeu  , SINON utilise rechID() des 4 traducteurs puis effectue la bonne action puis lance tour() 
	void initTraducteurs();// ICI elle ne FAIT RIEN DU TOUT (dans le livrable 3 ce sera pas le cas), elle n'est PAS appelée par le constructeur 
	std::string listeActionsPos();//on recupere les 3 attaques.listeID(), magies.listeID(), objets.listeID()  et on les concatène avec en séparateur ' /  '
	std::string etatsPerso();//recupere le caracs.toString() 
	bool aPA(int pa);
	bool aMana(int man);
	void ajCible(Personnage *mechant);// affecte le pointeur cible

	int aleat(int min, int max); // utiliser rand pour faire un nombre aleat entre min et max https://openclassrooms.com/courses/l-aleatoire-en-c-et-c-se-servir-de-rand-1
};