#include "bibl.h"

using namespace std;

bibl::bibl()
{
    vector <int> tab_id(0);
    vector <string> tab_type(0);
    vector <string> tab_titre(0);
    vector <string> tab_descr(0);

    int buffer_int = 0;
    string buffer_type = "";
    string buffer_titre = "";
    string buffer_descr = "";
}

string bibl::coupeChaine(string &ch, char a)
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

void bibl::ajLigne()
{
    tab_id.push_back(buffer_int);
    tab_type.push_back(buffer_type);
    tab_titre.push_back(buffer_titre);
    tab_descr.push_back(buffer_descr);
}

void bibl::modifLigne(int noLigne)
{
    tab_id[noLigne] = buffer_int;
    tab_type[noLigne] = buffer_type;
    tab_titre[noLigne] = buffer_titre;
    tab_descr[noLigne] = buffer_descr;
}

int bibl::rechLigne()
{
	int id = buffer_int;
	unsigned int noLigne = 0;
	for (noLigne = 0; noLigne<tab_id.size(); noLigne++) {
		if (id == tab_id[noLigne])
			return(noLigne);
	}
	return(-1);
}

void bibl::interpreterLigne(string Ligne)
{
	string ligne = Ligne;
	string mot;
	char separateur = ';';
	mot = coupeChaine(ligne, separateur);
	buffer_int = std::atoi( mot.c_str() );
	mot = coupeChaine(ligne, separateur);
	buffer_titre = mot;
	buffer_descr = ligne;

	int noLigne = rechLigne();
	if (noLigne == -1)
		ajLigne();
	else {
		modifLigne(noLigne);
	}
}

void bibl::mAJ(string MAJ)
{
    string lignes_type;
    string lignes;

    buffer_type = "Attaques";
    //MAJ contient tous les types separes par des .
    lignes_type = coupeChaine(MAJ, '.');
    //lignes_type contient a present toutes les lignes d'un type separees par des /
    bool boucle = true;
    lignes = coupeChaine(lignes_type, '/');
    while(lignes != "") {
        interpreterLigne(lignes); //On interprete chaque ligne d'un type donne
        lignes = coupeChaine(lignes_type, '/');
    }
    interpreterLigne(lignes_type);

    buffer_type = "Magies";
    //MAJ contient tous les types separes par des .
    lignes_type = coupeChaine(MAJ, '.');
    //lignes_type contient a present toutes les lignes d'un type separees par des /
    boucle = true;
    lignes = coupeChaine(lignes_type, '/');
    while(lignes != "") {
        interpreterLigne(lignes); //On interprete chaque ligne d'un type donne
        lignes = coupeChaine(lignes_type, '/');
    }
    interpreterLigne(lignes_type);

    buffer_type = "Objets";
    //Maj ne contient plus que les objets
    boucle = true;
    lignes = coupeChaine(MAJ, '/');
    while(lignes != "") {
        interpreterLigne(lignes); //On interprete chaque ligne d'un type donne
        lignes = coupeChaine(MAJ, '/');
    }
    interpreterLigne(MAJ);
}

void bibl::testBibl()
{
    for(int i = 0 ; i<tab_id.size() ; i++)
    {
        cout << tab_id[i] << "||" << tab_type[i] << "||"  << tab_titre[i] << "||"  << tab_descr[i] <<endl;
    }
}
