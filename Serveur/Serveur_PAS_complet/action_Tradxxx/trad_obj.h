#ifndef TRAD_OBJ_H
#define TRAD_OBJ_H

#include "action.h"
#include <string>

class Trad_obj
{
    public:
        Trad_obj();
        Action rechID(int id_r);
        std::string listeID();
        std::string toString();
    private:
        PotionVie a_1;
        PotionVie a_2;
};


#endif // TRAD_OBJ_H
