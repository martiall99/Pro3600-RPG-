#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <sstream>

class Personnage;

class Action
{
    protected:
        int a_id;
        std::string a_nom;
        std::string a_descr;
    public:
        Action(int id=-1,std::string nom="Erreur", std::string desc="Utilisation du constructeur par defaut de Action");
		void eff(Personnage &adv, Personnage &moi);
		bool peutEff(Personnage &adv, Personnage &moi);
		std::string toString();// ( + est la concaténation ici) donne a_id+sep+sep+a_nom+sep+a_descr avec sep un pont virgule '  ;  '
};

class AttaqueGenerique: public Action
{
protected:
	int coutPa;
	int minD;
	int maxD;
public:
	AttaqueGenerique(int id = -1, std::string nom = "Erreur2", std::string desc = "Utilisation du constructeur par defaut de AttaqueGenerique", int coutP=0, int dMin=0, int dMax=0);
	bool eff(Personnage &adv, Personnage &moi);
	bool peutEff(Personnage &adv, Personnage &moi);
};

class MagieAttaqueGenerique : public Action
{
protected:
	int coutPa;
	int coutMana;
	int minD;
	int maxD;
public:
	MagieAttaqueGenerique(int id = -1, std::string nom = "Erreur2", std::string desc = "Utilisation du constructeur par defaut de MagieAttaqueGenerique", int coutP = 0, int coutM=0, int dMin = 0, int dMax = 0);
	bool eff(Personnage &adv, Personnage &moi);
	bool peutEff(Personnage &adv, Personnage &moi);
};


#endif // ACTION_H
