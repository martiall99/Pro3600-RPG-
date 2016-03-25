#include    "Conteneur_carac.h"
using namespace std;

/* ( + est la concaténation ici)
donne PV+sep+Mana+sep+PA+sep+DEF+sep+RES+sep+CRIT+sep+ESQ+sep+RENV
avec sep un pont virgule ' ; ' */

string Conteneur_carac::toString() const

{
    string resultat_1 = "";
    resultat_1 = std::string("PV") + ";" + std::string("Mana") + ";" + std::string("PA") + ";" + std::string("DEF") +
    ";" + std::string("RES") + ";" + std::string("CRIT") + ";" + std::string("ESQ") + ";" + std::string("RENV");
    return resultat_1;
}

ostream& operator<<( ostream &flux, Conteneur_carac const& cont_car )
{
    flux << cont_car.toString();
    return flux;
}
