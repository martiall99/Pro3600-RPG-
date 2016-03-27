#ifndef CONTENEURACTION_H_INCLUDED
#define CONTENEURACTION_H_INCLUDED
#include <string>
#include <iostream>

// Cont_action :
typedef struct Cont_action Cont_action;
struct Cont_action
{
public:
	std::string titre;//nom de l'action
	std::string type;// attaque, magie, objet buff
	std::string descr;//description
public:
	void modif( std::string ti, std::string ty, std::string des );// change les 3 compos
	std::string toString() const ;// PAS sur qu'on ait le droit comme c'est une struct, mais je crois que ça marchera et sinon au pire tout mettre dans le operator<<
						   // ( + est la concaténation ici) donne titre+sep+type+sep+descr avec sep un pont virgule '  ;  '
};
std::ostream& operator<<( std::ostream &flux, Cont_action const& cont );// REMPLIR LA PARENTHESE ICI avec un Cont_action  et ce qu'il faut

#endif // CONTENEURACTION_H_INCLUDED
