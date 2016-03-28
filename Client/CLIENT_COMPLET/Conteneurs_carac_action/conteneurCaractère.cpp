#include    "Conteneur_carac.h"

/* ( + est la concaténation ici)
donne PV+sep+Mana+sep+PA+sep+DEF+sep+RES+sep+CRIT+sep+ESQ+sep+RENV
avec sep un pont virgule ' ; ' */

#include <sstream>

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
string Conteneur_carac::toStringExplicit() const
{
	string res = "";
	res = " PV: "+to_String(PV) +"\n Mana: "+ to_String(Mana) + "\n PA: " + to_String(PA) + "\n DEF: " + to_String(DEF);
	res+= "\n RES_Magique: " + to_String(RES) + "\n Crit: " + to_String(CRIT) + "\n ESQ: " + to_String(ESQ) + "\n Renvois: " + to_String(RENV);
	return res;
}
ostream& operator<<( ostream &flux, Conteneur_carac const& cont_car )
{
    flux << cont_car.toString();
    return flux;
}
