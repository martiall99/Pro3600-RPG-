#ifndef TRAD_MAGIE_H
#define TRAD_MAGIE_H

#include "action.h"
#include <string>

class Trad_magie
{
    public:
        Trad_magie();
        Action rechID(int id_r);
        std::string listeID();
        std::string toString();
    private:
        Magie a_1;
        Magie a_2;
};


#endif // TRAD_MAGIE_H
