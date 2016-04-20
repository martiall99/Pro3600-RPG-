#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "action.h"

class Personnage;

class TradActions
{
	AttaqueGenerique attaqueSimple;
	AttaqueGenerique attaquePuissante;
	MagieAttaqueGenerique bouleFeu;
	PotionSoinGenerique potionFaible;
	PotionSoinGenerique potionForte;
public:// pour le LIV2 c'est PAS encore un "tableau intelligent" juste quelquechose qui d�finit et cr�� des objets
		   //utilisees par initTraducteurs() de Personnage

		TradActions();//constructeur qui cr�� en son sein (construit)  attaque simple, attaque puissante, bouclier


		bool utiliseID(int id_r, Personnage &adv, Personnage &moi);// c'est la "principale" de cette classe, elle return() un des objets de type Action construit par le constructeur Trad_action() en focntion de l'id
		Action* rechID(int id_r);
		std::string listeID();//liste juste les ID s�par�ess par '   ;   ' , 
		std::string toString();//utilis� par l'op�rateur <<,  lance le toString() de chaque action et les liste, s�par�ess par un '/'

	};

std::ostream& operator<<(std::ostream &flux, TradActions const& trad);//utilise toString()