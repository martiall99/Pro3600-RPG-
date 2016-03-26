//
//  affichage.hpp
//  Pro_3600
//
//  Created by Amine Tekni on 26/03/2016.
//  Copyright © 2016 Amine Tekni. All rights reserved.
//

#ifndef affichage_hpp
#define affichage_hpp
#include <iostream>
#include "conteneurAction.h"
#include "Conteneur_carac.h"
#include <vector>
#include <string> 



// Variables globales
// Transfert tran; bibliothèque bibl; Traduction trad; Client cli;
int ID_1;
int ID_2;


// Variable de :
//bibl :
std::vector <int> tab_id;
std::vector <std::string> tab_titre;
std::vector <std::string> tab_descr;
int buffer_int;
std::string buffer_type;
std::string buffer_titre;
std::string buffer_descr;

//Transfert:
std::string IP_client;
std::string IP_serveur;
std::string port_client;
std::string port_serv;

//Trad
bool partie_debutee;

//client
int numero_coup;

void _Oc(int id_moi, int id_adv);// on sauvegarde les 2 id (on les affiche pour le debug)
void _1ds(); // serveur dit que partie débute, à priori on fait rien de spécial dans le cas du liv2 , ptetre juste afficher "le combat débute" ou un truc du genre ?
void _6a(std::string maj); // envoie juste a mAJ() sans rien faire d'autre
//séparateur: on n'y touche PAS c'est bibl qui s'occupe de tout
void _4a(int id, std::string etat); // rempli un Conteneur_carac et l'affiche	en précédant de "moi" (= la personne qui joue ) ou "adversaire" suivant l'id
//séparateur: '  ;  ' entre chaque carac
void _2a(int num_coup, std::string actions_poss); //  affiche les possibilités dans "l'interface", puis   SI  num_coup= -1 s'arrète là , SINON demande à l'utilisateur d'entrer une action avec ChoixAction () puis
//séparateur: '  ;  '  entre chaque id d'action possible
void _3a(int id, std::string act);// affiche "Je " OU "L'adversaire" + "utilise" + le nom de l'action en question, trouvé grâce à rechAction() dans le champ titre du conteneur renvoyé
void _1fs(int id_gagnant);// serveur dit que partie est terminée , affiche qui a gagné


#endif /* affichage_hpp */
