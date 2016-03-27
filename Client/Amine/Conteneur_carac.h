#ifndef CONTENEUR_CARAC_H_INCLUDED
#define CONTENEUR_CARAC_H_INCLUDED
#include <iostream>
#include <string>

// Conteneur_carac
typedef struct Conteneur_carac Conteneur_carac;
struct Conteneur_carac
{

//Je n'arrivais pas à compiler à
// de la conversion char en int ou
// un autre dans ce genre

public:
    int PV;
	int Mana;
	int PA;
	int DEF;// defence pour les ATTAQUES
	int RES;//resistance MAGIQUE
	int CRIT;// EN %*100
	int ESQ;// EN %*100
	int RENV;//renvoi des dommages


public:
	std::string toString() const;// PAS sur qu'on ait le droit comme c'est une struct, mais je crois que ça marchera et sinon au pire tout mettre dans le operator<<
						   // ( + est la concaténation ici) donne PV+sep+Mana+sep+PA+sep+DEF+sep+RES+sep+CRIT+sep+ESQ+sep+RENV avec sep un pont virgule '  ;  '
};
std::ostream& operator<<( std::ostream &flux, Conteneur_carac const& cont_car );// REMPLIR LA PARENTHESE ICI avec un Conteneur_carac  et ce qu'il faut




#endif // CONTENEUR_CARAC_H_INCLUD
