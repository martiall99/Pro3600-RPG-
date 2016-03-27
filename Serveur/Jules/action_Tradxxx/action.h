#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <sstream>
#include "Personnage.h"

class Action
{
    private:
        int a_id;
        std::string a_nom;
        std::string a_descr;
        std::string toString();// ( + est la concaténation ici) donne a_id+sep+sep+a_nom+sep+a_descr avec sep un pont virgule '  ;  '

    public:
        Action(int id,std::string nom, std::string desc);

};

class AttaqueSimple : public Action{

    public :
        AttaqueSimple(int id,std::string nom, std::string desc);
        void eff(Personnage& Cible, Personnage& Lanceur);
};

class AttaquePuissante : public Action{

    public :
        AttaquePuissante(int id,std::string nom, std::string desc);
        void eff(Personnage& Cible, Personnage& Lanceur);
};

class Bouclier : public Action{

    public :
        Bouclier(int id,std::string nom, std::string desc);
        void eff(Personnage& Cible, Personnage& Lanceur);
};

class PotionVie : public Action{

    public :
        PotionVie(int id,std::string nom, std::string desc, int regeneration);
        void eff(Personnage& Cible, Personnage& Lanceur);
    private :
        int a_regeneration;
};

class Magie : public Action{

    public :
        Magie(int id,std::string nom, std::string desc, int regeneration, int degats, int mana, int pa);
        void eff(Personnage& Cible, Personnage& Lanceur);
    private :
        int a_regeneration;
        int a_degats;
        int a_mana;
        int a_pa;
};
#endif // ACTION_H
