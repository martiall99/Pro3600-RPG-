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
		std::string toString();// ( + est la concat�nation ici) donne a_id+sep+sep+a_nom+sep+a_descr avec sep un pont virgule '  ;  '
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


class MagieGenerique : public Action
{
protected:
	int coutPa;
	int coutMana;
	bool enleverPAMana(Personnage &adv, Personnage &moi);
public:
	MagieGenerique(int id = -1, std::string nom = "Erreur3", std::string desc = "Utilisation du constructeur par defaut de MagieGenerique", int coutP = 0, int coutM=0);
	bool peutEff(Personnage &adv, Personnage &moi);
};

class MagieAttaqueGenerique : public MagieGenerique
{
protected:
	int minD;
	int maxD;
public:
	MagieAttaqueGenerique(int id = -1, std::string nom = "Erreur4", std::string desc = "Utilisation du constructeur par defaut de MagieAttaqueGenerique", int coutP = 0, int coutM = 0, int dMin = 0, int dMax = 0);
	bool eff(Personnage &adv, Personnage &moi);
	bool peutEff(Personnage &adv, Personnage &moi);
};


class PotionGenerique : public Action
{
protected:
	int nbr;

protected:
	void enlever1potion();
public:
	PotionGenerique(int id = -1, std::string nom = "Erreur5", std::string desc = "Utilisation du constructeur par defaut de PotionGenerique",int n=0);
	bool peutEff(Personnage &adv, Personnage &moi);
};

class PotionSoinGenerique : public PotionGenerique
{
	int heal;
public:
	PotionSoinGenerique(int id = -1, std::string nom = "Erreur6", std::string desc = "Utilisation du constructeur par defaut de PotionSoinGenerique", int n = 0, int soin=0);
	bool eff(Personnage &adv, Personnage &moi);
};


#endif // ACTION_H
