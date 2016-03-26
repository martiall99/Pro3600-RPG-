//
//  affichage.cpp
//  Pro_3600
//
//  Created by Amine Tekni on 26/03/2016.
//  Copyright © 2016 Amine Tekni. All rights reserved.
//
#include "affichage.hpp"

using namespace std;

void afficher (string msg)
{
    cout << msg << endl;
}

void lire (string &msg)
{
    cin >> msg ;
}

string coupeChaine(string &ch, char a)
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

void _Oc(int id_moi, int id_adv)// on sauvegarde les 2 id (on les affiche pour le debug)
{
    id_moi=ID_1;
    id_adv=ID_2;
    cout << id_moi;
    cout << id_adv;
    
}
void _1ds() // serveur dit que partie débute, à priori on fait rien de spécial dans le cas du liv2 , ptetre juste afficher "le combat débute" ou un truc du genre ?
{
    cout << "Début du combat ";
}
void _6a(std::string maj) // envoie juste a mAJ() sans rien faire d'autre
//séparateur: on n'y touche PAS c'est bibl qui s'occupe de tout
{
    //mAJ(maj)
}


Conteneur_carac eta (string etat)
{
Conteneur_carac c = {0,0,0,0,0,0,0,0};
string b=coupeChaine(etat,';');

c.PV=stoi (b) ;
b=coupeChaine(etat,';');

c.Mana=stoi (b);
b=coupeChaine(etat,';');

c.PA=stoi (b) ;
b=coupeChaine(etat,';');

c.DEF=stoi (b);
b=coupeChaine(etat,';');

c.RES=stoi (b) ;
b=coupeChaine(etat,';');

c.CRIT=stoi (b);
b=coupeChaine(etat,';');

c.ESQ=stoi (b) ;
b=coupeChaine(etat,';');

c.RENV=stoi (b);
b=coupeChaine(etat,';');
    return c;
}


void _4a(int id, std::string etat) // rempli un Conteneur_carac et l'affiche	en précédant de "moi" (= la personne qui joue ) ou "adversaire" suivant l'id
//séparateur: '  ;  ' entre chaque carac et '.' entre chaque adversaire

{
    string perso2=coupeChaine(etat, '.');
    
   Conteneur_carac etat1 = eta(etat);
     cout << "Moi" << etat1<< endl;
  
    Conteneur_carac etat2 = eta(perso2);
    cout << "L'adversaire" << etat2<< endl;
    
    
}


void _2a(int num_coup, std::string actions_poss) //  affiche les possibilités dans "l'interface", puis   SI  num_coup= -1 s'arrète là , SINON demande à l'utilisateur d'entrer une action avec ChoixAction () puis
//séparateur: '  ;  '  entre chaque id d'action possible
{
    cout << "Actions possibles";
    if (num_coup!= -1)
    {
        afficher ("Choisissez votre action");
        //ChoixAction(num_coup,actions_poss)
        
    }
}


void _3a(int id, std::string act)// affiche "Je " OU "L'adversaire" + "utilise" + le nom de l'action en question, trouvé grâce à rechAction() dans le champ titre du conteneur renvoyé
{
    
   // int action1 =stoi(act);
    /*
     Cont_action action = rechAction(action1);
    if (id=ID_1)
    {
        cout << "J'utilise" << action.titre << endl;"
    }
    else cout << "L'acversaire utilise" << action.titre << endl;"

*/
    
}




void _1fs(int id_gagnant)// serveur dit que partie est terminée , affiche qui a gagné
{
    cout << "Partie términée";
    cout << "Le gagnat est" << to_String(id_gagnant) <<endl;
    
}



int main ()

{
    string a;
    afficher ("ecrit un truc grosse merde");
    lire (a);
    afficher (a);
    return 0;
}
