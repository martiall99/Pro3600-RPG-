#include <iostream>
#include "conteneurAction.h"
#include "ConteneurCaractere.h"
#include "traduction.h"
#include <string>

using namespace std;

string coupeChaine(string &ch, char a)
//Separe la chaine de caractere ch selon le seperateur a.
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
    //pour liv2 ce sera forcement _0c() pas de s�parateur
    {
        string mess_int = mess ;
        mess_int.erase(0,1);   //Efface le premier caract�re qui est correspond au bool�en type0
        int ID_inutile_1 = stoi(coupeChaine(mess_int, ';'));
        int ID_inutile_2 = stoi(mess_int);
        //_0c(ID_inutile_1,ID_inutile_2);

        // Cette partie est utile pour le test unitaire de iT0
        cout << ID_inutile_1 << endl;
        cout << ID_inutile_2 << endl;
    }

	void iT1(std::string mess)
	/* liv  2 : renvoie vers  1ds() ou 1fs() suivant les bits du message
	(voir l'architecture) pas de s�parateur */
	{
	    string mess_int = mess;
	    int type_1 = stoi(mess_int.substr(0,1)); // on reccup�re le 1er caract�re de mess
	    int type_2 = stoi(mess_int.substr(1,1)); // on reccup�re le 2�me caract�re de mess
        mess_int.erase(0,2);

        if ((type_1 == 0)&& (type_2 == 0))
        {
            //_1ds();
            cout << "Debut de la partie, on vire les // et on lance _1ds()" << endl;
        }

        else if ((type_1 == 0)&& (type_2 == 1))
        {
            mess_int.erase(0,1); // on supprime le bit coresspondant � l'information/la demande
            int id_gagnant = stoi(mess_int.substr(0,1));
            //_1fs(int id_gagnant);
            cout << "Partie terminee, On vire // et lance _1fs(int id_gagnant)" << endl;
        }

        else if ((type_1 == 1 )&& (type_2 == 0))
        {
            cout << "utile pour liv3, pas pour le liv2" << endl;
        }

        else if ((type_1 == 1 )&& (type_2 == 1))
        {
            cout << "utile pour liv3, pas pour le liv2" << endl;
        }

    }

	void iT2(std::string mess)
	// liv  2 : 2a(), on ne touche PAS au s�parateur
	{
	    string mess_int = mess;
	    int numeroCoupAttendu = stoi(coupeChaine(mess_int, ';'));
	    string listeActionsPossibles = mess_int;
	    //_2a(numeroCoup, listeActionsPossibles);

        // Cette partie est utile pour le test unitaire de iT2
        cout << "Message recu= " << mess << endl;
	    cout << "Numero du coup attendu =" << numeroCoupAttendu << ", liste des possibilites :["
                    << listeActionsPossibles << "]" <<  endl;
	}


	void iT3(std::string mess)
	// liv  2 : 3a() pas de s�parateur
    {
        string mess_int = mess;
        int id_joueur = stoi(coupeChaine(mess_int,';'));
        int numeroCoupJoue = stoi(coupeChaine(mess_int,';')); // on l'utilise pas ici
        string actionEffectuee = mess_int;
        // _3a(id_joueur, actionEffectuee );

        // Cette partie est utile pour le test unitaire de iT3
        cout << "id_joueur = " << id_joueur << ", Action effectuee = " << actionEffectuee
                << ", Numero du coup =" << numeroCoupJoue << ";" << endl;
    }

	void iT4(std::string mess)
	/* liv  2 : on appelle 4a() DEUX FOIS (une pour chaque perso en s�parant
    suivant ' . ' ) ,s�parateur: ' . ', on ne touche PAS aux ' ; '*/
    {
        string mess_int = mess ;
        int numeroCoupJoue = stoi(coupeChaine(mess_int, ';'));
        string etatPerso1 = coupeChaine(mess_int, '.');
        string etatPerso2 = mess_int;
        //_4a(etatPerso1);
        //_4a(etatPerso2);


        // Cette partie est utile pour le test unitaire iT4
        cout << "Etat du personnage 1: " << etatPerso1 << ", Etat du personnage 2: "
                << etatPerso2 << "." << endl;


    }

	void iT6(std::string mess)
	// liv  2 : 6a(), on ne touche PAS aux s�parateurs
	{
	    cout << "message recu : " << mess << endl;
	    // _6a();
	}

int main()
{
    /*
    cout <<"---Test unitaire pour conteneur action--" << endl;
    Cont_action conteneur = {"Titre","type","descr"};
    cout << conteneur.toString() << endl;
    */

    /*
    cout <<"---Test unitaire pour conteneur caractere --" << endl;
    Conteneur_carac conteneur1 = {1,2,3,4,5,6,7,8};
    cout << conteneur1.toString() << endl;
    */

    /*
    cout << "---Test unitaire pour iT0---" << endl;
    string test = "02122;6523";
    iT0(test);
    */

    /*
    cout << "---Test unitaire pour iT1---" << endl;
    string test_1 = "0056";
    string test_2 = "0156";
    string test_3 = "1056";
    iT1(test_1);
    iT1(test_2);
    iT1(test_3);
    */

    /*
    cout << "---Test unitaire pour iT2---" << endl;
    string test = "215;coup_pied,coup_tete,morsu,pleurs";
    iT2(test);
    */

    /*
    cout << "---Test unitaire pour iT3---" << endl;
    string test = "15;265;morsu";
    iT3(test);
    */

    /*
    cout << "---Test unitaire pour iT4---" << endl;
    string test = "15;vivant.vivant";
    iT4(test);
    */

    // iT5 n'est pas utile pour le livrable 2.

    /*
    cout << "---Test unitaire pour iT6---" << endl;
    string test = "15;vivant.vivant";
    iT6(test);
    */

    return 0;

}
