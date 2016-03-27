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
        void eff(Personnage& Perso);
};

class AttaquePuissante : public Action{

    public :
        AttaquePuissante(int id,std::string nom, std::string desc);
        void eff(Personnage& Perso);
};

class Bouclier : public Action{

    public :
        Bouclier(int id,std::string nom, std::string desc);
        void eff(Personnage& Perso);
};

class PotionVie : public Action{

    public :
        PotionVie(int id,std::string nom, std::string desc, int efficacite);
        void eff(Personnage& Perso);
    private :
        int a_regeneration;
};
#endif // ACTION_H
