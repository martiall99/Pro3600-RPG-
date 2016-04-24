#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "action.h"


class TradActions
{
protected:
	std::vector<int> ID;
	std::vector<Action*> act;// oui c'est un pointeur , utiliser -> pour accéder aux méthodes/variables a la place du point usuel !
	Action erreur;
public:
	Personnage *moi;

public:// pour le LIV2 c'est PAS encore un "tableau intelligent" juste quelquechose qui définit et créé des objets
	   //utilisees par initTraducteurs() de Personnage

	TradActions(Personnage *papa);//constructeur qui ne fait que changer "moi"

	bool ajAction(int id_a, Action *ac);//ajoute l id et le pointeur dans chaque tableau avec des push front 
	bool enlAction(int id_a);// utilise rech() puis supprime les deux cases correspondantes
	std::string toString();//utilisé par l'opérateur <<
	int size();
	bool verifStable();
	std::string listeID();
	void viderTrad();

	int rech(int id);//renvoie le numéro de la case du tableau correspondant a l id
	Action* rechID(int id_r);// utilise rech() puis r'envoie le pointeur du deuxième tableau dans la même case 

};

std::ostream& operator<<(std::ostream &flux, TradActions const& trad);//utilise toString()