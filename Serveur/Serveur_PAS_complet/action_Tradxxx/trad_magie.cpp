#include "trad_magie.h"

Trad_magie::Trad_magie()
{
     Magie a_1(1,"Boule de feu","Inflige des degats de feu.",0,30,2,6);
     Magie a_1(2,"Soin","Regenere des PV.",30,0,2,6);
     Action no_action(0,"","");
}

Action Trad_magie::rechID(int id_r)
{
    if(id_r == 1)
        return(a_1);
    if(id_r == 2)
        return(a_1);
    return(no_action);
}

string Trad_magie::listeID()
{
    return("1;2");
}

string Trad_magie::toString()
{
    string sortie;
    sortie = a_1.toString() + ";" + a_2.toString();
    return(sortie);
}
