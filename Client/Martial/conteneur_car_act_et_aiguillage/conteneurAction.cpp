#include "conteneurAction.h"

using namespace std;

// ( + est la concaténation ici) donne titre+sep+type+sep+descr avec sep un pont virgule '  ;  '
string  Cont_action::toString() const
{
    string resultat = "";
    resultat = titre + ";" + type + ";" + descr ;
    return resultat ;

}


ostream& operator<<( ostream &flux, Cont_action const& cont )
{
    flux << cont.toString();
    return flux;
}
