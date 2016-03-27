#include    "ConteneurCaractere.h"
#include <sstream>
/* ( + est la concaténation ici)
donne PV+sep+Mana+sep+PA+sep+DEF+sep+RES+sep+CRIT+sep+ESQ+sep+RENV
avec sep un pont virgule ' ; ' */

using namespace std;

string to_String(int a)
{
    stringstream ss;
    ss<<a;
    return ss.str();
}

string Conteneur_carac::toString() const

{
    string resultat_1 = "";
    resultat_1 = to_String(PV) + ";" + to_String(Mana) + ";" + to_String(PA) + ";" + to_String(DEF) +
                 ";" + to_String(RES) + ";" + to_String(CRIT) + ";" + to_String(ESQ) + ";" + to_String(RENV);
    return resultat_1;
}

ostream& operator<<( ostream &flux, Conteneur_carac const& cont_car )
{
    flux << cont_car.toString();
    return flux;
}
