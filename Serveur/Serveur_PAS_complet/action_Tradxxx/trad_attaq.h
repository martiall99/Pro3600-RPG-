#pragma once

#include "action.h"
#include <string>

class Trad_attaq
{
    public:
        Trad_attaq();
        Action rechID(int id_r);
        std::string listeID();
        std::string toString();
    private:
        AttaqueSimple a_1;
        AttaquePuissante a_2;
        Bouclier a_3;
		Action no_action;
};


