#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <sstream>

class Personnage;
class TradActions;

class Action
{
	public:
		TradActions *parent;
    protected:
        std::string a_nom;
        std::string a_descr;


    public:
		int a_id;
        Action(int id=-1,std::string nom="Erreur", std::string desc="Utilisation du constructeur par defaut de Action");
		void ajParent(TradActions *papa);// "rempli" le pointeur parent avec le tradaction dans lequel l'action est
		bool virtual eff();//virtual sert a indiquer que c'est un polymorphisme
		bool virtual peutEff();
		std::string toString();// ( + est la concaténation ici) donne a_id+sep+sep+a_nom+sep+a_descr avec sep un pont virgule '  ;  '
		bool stableEtCible();
		bool stableSansCible();
};


class AttaqueGenerique: public Action
{
protected:
	int coutPa;
	int minD;
	int maxD;
public:
	AttaqueGenerique(int id = -1, std::string nom = "Erreur2", std::string desc = "Utilisation du constructeur par defaut de AttaqueGenerique", int coutP=0, int dMin=0, int dMax=0);
	bool eff();
	bool peutEff();
};


class MagieGenerique : public Action
{
protected:
	int coutPa;
	int coutMana;
	bool enleverPAMana();
public:
	MagieGenerique(int id = -1, std::string nom = "Erreur3", std::string desc = "Utilisation du constructeur par defaut de MagieGenerique", int coutP = 0, int coutM=0);
	bool peutEff();
};

class MagieAttaqueGenerique : public MagieGenerique
{
protected:
	int minD;
	int maxD;
public:
	MagieAttaqueGenerique(int id = -1, std::string nom = "Erreur4", std::string desc = "Utilisation du constructeur par defaut de MagieAttaqueGenerique", int coutP = 0, int coutM = 0, int dMin = 0, int dMax = 0);
	bool eff();
};


class PotionGenerique : public Action // ATTENTION le nbr de potion est stocké par l'action potion et ne depend pas du personnage => il faut en faire Une instance par personnage (avec 2 id != )
{
protected:
	int nbr;
	int nbrInit;

protected:
	bool enlever1potion();
public:
	int nbrRestant();
	PotionGenerique(int id = -1, std::string nom = "Erreur5", std::string desc = "Utilisation du constructeur par defaut de PotionGenerique",int n=0);
	bool peutEff();
};

class PotionSoinGenerique : public PotionGenerique
{
	int healMin;
	int healMax;
public:
	PotionSoinGenerique(int id = -1, std::string nom = "Erreur6", std::string desc = "Utilisation du constructeur par defaut de PotionSoinGenerique", int n = 0, int soinm=0, int soinM=0);
	bool eff();
};


#endif // ACTION_H
