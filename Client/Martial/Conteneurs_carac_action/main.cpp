#include <iostream>
#include "conteneurAction.h"
#include "Conteneur_carac.h"
#include "traduction.h"

//Je commence mes bidouilles
#include <string>

using namespace std;

string coupeChaine(string &ch, char a)
//Sépare les chaines de caractères.
{
	int p = ch.find(a);
	//cout << "init= " + ch + " coupeA= " + a + " length= "+to_string(ch.length())+" pos= "+to_string(p) << endl;
	if (p == string::npos)
		return "";
	else
	{
		string r = ch.substr(0,p);
		//cout << "substr= " + r << endl;
		ch.erase(0, p+1);
		//cout << "coupee= " + ch<<endl;
		return r;
	}
}

    void iT0(std::string mess)
    //pour liv2 ce sera forcement _0c() pas de séparateur
    {
        string mess_int = mess ;
        mess_int.erase(0,1);   //Efface le premier caractère
        int ID_inutile_1 = stoi(coupeChaine(mess_int, ';'));
        int ID_inutile_2 = stoi(mess_int);
        //_0c(ID_inutile_1,ID_inutile_2);
    }

	void iT1(std::string mess)
	/* liv  2 : renvoie vers  1ds() ou 1fs() suivant les bits du message
	(voir l'architecture) pas de séparateur*/
	{
	    string mess_int = mess;
	    int type_1 = stoi(mess.substr(0,1)); // on garde le 1er caractère de mess
	    int type_2 = stoi(mess.substr(1,1)); // on garde le 2ème caractère de mess
        mess_int.erase(0,2);

        if ((type_1 == 0)&& (type_2 == 0))
        {
            //_1ds();
            cout << "lance 1ds" << endl;
        }

        else if ((type_1 == 0)&& (type_2 == 1))
        {
            mess_int.erase(0,1); // on supprime le bit d'information
            int id_gagnant = stoi(mess_int.substr(0,1));
            //_1fs(int id_gagnant);
            cout << "On vire // et lance 1fs(int id_gagnant)" << endl;
        }

        else if ((type_1 == 1 )&& (type_2 == 0))
        {
            cout << "utile pour liv3" << endl;
        }

        else if ((type_1 == 1 )&& (type_2 == 1))
        {
            cout << "utile pour liv3" << endl;
        }

    }

	void iT2(std::string mess);
	// liv  2 : 2a(), on ne touche PAS au séparateur

	void iT3(std::string mess);
	// liv  2 : 3a() pas de séparateur

	void iT4(std::string mess);
	/* liv  2 : on appelle 4a() DEUX FOIS (une pour chaque perso en séparant
    suivant ' . ' ) ,séparateur: ' . ', on ne touche PAS aux ' ; '*/

	void iT6(std::string mess);
	// liv  2 : 6a(), on ne touche PAS aux séparateurs

int main()
{
    /*
    cout << "Test unitaire pour conteneur action et caractère " << endl;

    Cont_action conteneur = {"Titre","type","descr"};
    cout << conteneur.toString() << endl;

    Conteneur_carac conteneur1 = {1,2,3,4,5,6,7,8};
    cout << conteneur1.toString() << endl;
    */

    /*
    cout << "---Test unitaire pour iT0---" << endl;
    string test = "x2122;6523";
    iT0(test, ";");
    */

    /*
    cout << "---Test unitaire pour iT0---" << endl;
    string test_1 = "0056";
    string test_2 = "0156";
    string test_3 = "1056";
    iT1(test_1);
    iT1(test_2);
    iT1(test_3);
    */

    return 0;

}
