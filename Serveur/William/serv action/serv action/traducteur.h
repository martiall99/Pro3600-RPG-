#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "action.h"


class TradActions
{
	AttaqueGenerique AttaqueSimple;
	AttaqueGenerique AttaquePuissante;
	MagieAttaqueGenerique BouleFeu;
public:// pour le LIV2 c'est PAS encore un "tableau intelligent" juste quelquechose qui définit et créé des objets
		   //utilisees par initTraducteurs() de Personnage

		TradActions();//constructeur qui créé en son sein (construit)  attaque simple, attaque puissante, bouclier


		Action rechID(int id_r);// c'est la "principale" de cette classe, elle return() un des objets de type Action construit par le constructeur Trad_action() en focntion de l'id

		std::string listeID();//liste juste les ID séparéess par '   ;   ' , 
		std::string toString();//utilisé par l'opérateur <<,  lance le toString() de chaque action et les liste, séparéess par un '/'

	};

std::ostream& operator<<(std::ostream &flux, TradActions const& trad);//utilise toString()