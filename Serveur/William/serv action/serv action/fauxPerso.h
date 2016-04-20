#pragma once
#include <iostream>
#include <string>


class Personnage
{
	std::string nom;
public:
	Personnage(std::string n="sans nom");
	void recevoirDegats(int min, int max);// utilise aleat() et implemente la formule de degats (qui depend de la DEF de ce perso) qu'on avait mise dans le liv1
	void recevoirDegatsMagiques(int min, int max);// meme chose avec RES 
	void recevoirSoins(int min, int max);
	void changerArmure(int nouv);
	bool aPA(int pa);
	bool aMana(int man);
	bool utiliserMana(int man);
	bool utiliserPa(int coutPa); //renvoie true si le personnage a assez de Pa et les soustrait
};