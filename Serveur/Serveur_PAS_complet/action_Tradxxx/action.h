#pragma once

#include <string>

class Action
{
protected:
        int a_id;
        std::string a_nom;
        std::string a_descr;
		class Personnage;// Forward declaration de personnage, on peut pas se permettre de l'include , sinon le linker est pas content 
						// car Personnage include les Trad qui include action (donc si action include Personnage ... )
       

public:
		std::string toString();// ( + est la concaténation ici) donne a_id+sep+sep+a_nom+sep+a_descr avec sep un pont virgule '  ;  '
        Action(int id=-1,std::string nom="VIDE", std::string desc="VIDE");
		void eff(Personnage& Cible, Personnage& Lanceur);

};

class AttaqueSimple : public Action{

    public :
		AttaqueSimple(int id = -1, std::string nom = "VIDE", std::string desc = "VIDE");
        void eff(Personnage& Cible, Personnage& Lanceur);
};

class AttaquePuissante : public Action{

    public :
		AttaquePuissante(int id = -1, std::string nom = "VIDE", std::string desc = "VIDE");
        void eff(Personnage& Cible, Personnage& Lanceur);
};

class Bouclier : public Action{

    public :
		Bouclier(int id = -1, std::string nom = "VIDE", std::string desc = "VIDE");
        void eff(Personnage& Cible, Personnage& Lanceur);
};

class PotionVie : public Action{

    public :
		PotionVie(int id = -1, std::string nom = "VIDE", std::string desc = "VIDE", int regeneration=0);
        void eff(Personnage& Cible, Personnage& Lanceur);
    private :
        int a_regeneration;
};

class Magie : public Action{

    public :
		Magie(int id = -1, std::string nom = "VIDE", std::string desc = "VIDE", int regeneration=0, int degats=0, int mana=0, int pa=0);
        void eff(Personnage& Cible, Personnage& Lanceur);
    protected :
        int a_regeneration;
        int a_degats;
        int a_mana;
        int a_pa;
};
