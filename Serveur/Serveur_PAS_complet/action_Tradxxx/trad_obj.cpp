#include "trad_obj.h"

Trad_obj::Trad_obj()
{
    PotionVie a_1(1,"Petite potion de vie", "Rend peu de PV.", 10);
    PotionVie a_2(2,"Grande potion de vie", "Rend beaucoup de PV.", 30);
    Action no_action(0,"","");
}

Action Trad_obj::rechID(int id_r)
{
    if(id_r == 1)
        return(a_1);
    if(id_r == 2)
        return(a_2);
    return(no_action);
}

string Trad_obj::listeID()
{
    return("1;2");
}

string Trad_obj::toString()
{
    string sortie;
    sortie = a_1.toString() + "/" + a_2.toString();
    return(sortie);
}
