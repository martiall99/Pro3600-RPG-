#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "action.h"

class Personnage;

class TradActions
{
public:
	AttaqueGenerique attaqueSimple;
	AttaqueGenerique attaquePuissante;
	MagieAttaqueGenerique bouleFeu;
	PotionSoinGenerique potionFaible;
	PotionSoinGenerique potionForte;
	Action erreur;
	Personnage *moi;
	Personnage *adv;
public:// pour le LIV2 c'est PAS encore un "tableau intelligent" juste quelquechose qui d�finit et cr�� des objets
		   //utilisees par initTraducteurs() de Personnage

		TradActions();//constructeur qui cr�� en son sein (construit)  attaque simple, attaque puissante, bouclier


		Action* rechID(int id_r);
		std::string listeID();//liste juste les ID s�par�ess par '   ;   ' , 
		std::string toString();//utilis� par l'op�rateur <<,  lance le toString() de chaque action et les liste, s�par�ess par un '/'

	};

std::ostream& operator<<(std::ostream &flux, TradActions const& trad);//utilise toString()