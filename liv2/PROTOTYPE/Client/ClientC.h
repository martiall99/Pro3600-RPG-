#ifndef CLIENT_C
#define CLIENT_C

#include "Conteneurs_carac_action/Conteneur_carac.h"
#include "Conteneurs_carac_action/conteneurAction.h"

#include <vector>
#include <string>
#include <cstdlib>



// Variables globales
// Transfert tran; bibliothèque bibl; Traduction trad; Client cli;
int ID_1;
int ID_2;


// Variable de :
//bibl :
std::vector <int> tab_id;
std::vector <std::string> tab_titre;
std::vector <std::string> tab_type;
std::vector <std::string> tab_descr;
int buffer_int;
std::string buffer_type;
std::string buffer_titre;
std::string buffer_descr;

//Transfert:
/*
std::string IP_client;
std::string IP_serveur;
std::string port_client;
std::string port_serv;
*/

//Trad
bool partie_debutee;

//client
int numero_coup;


//methode de:


//bibl:// principe du fonctionnement : mAJ() (ouioui l'écriture est fait exprès) coupe la chaine envoyée avec coupeChaine(), remplie std::string buffer_type et envoie a interpreterLigne()
// celui ci recoupe et rempli chaque type de buffer (int buffer_int;std::string buffer_titre;std::string buffer_descr; ) avec la bonne partie de la chaine initiale
//celui là regarde s'il y a déja une ligne correspondant au même sort puis la modifie si c'est le cas ou en créé une nouvelle sinon


	void ajLigne();//créer la ligne dont les caractéristiques sont dans les buffers
	void modifLigne(int ligne);// remplace la ligne a modifier (dont les nouvelles caractéristiques sont dans les buffers)
	int rechLigne();// renvoie le NUMERO de la LIGNE ( ATTENTION != ID du sort) dont l'ID est stockée dans buffer( ATTENTION il est en général différent de l'ID de l'action), renvoie -1 si l'id n'est pas stockée
	void interpreterLigne(std::string Ligne); // sépare chaque champ, remplit chaque buffer, appelle rechLigne(), si il y a une correspondance appelle modifLigne(), sinon ajLigne()
	//séparateur: '  ;  '  entre chaque "composante" (ID, titre, description) d'une action possible

	Cont_action rechAction(int id);// rechLigne() puis renvoie un cont_action contenant le contenu de la ligne, si aucune correspondance renvoie des champs vides ""
	void mAJ(std::string MAJ);// sépare à ' / ' et appelle 	interpreterLigne() sur chaque, en remplacant au préalable le buffer_type avec le bon mot ( dans l'ordre : attaques, magie, objets, buffs) 
	//séparateur: '  /  '  entre chaque action possible   et ' . ' entre chaque type d'actions ( dans l'ordre : attaques, magie, objets) 

//transfert:
 //utilise par client
	void demandeCo(int id, std::string dir="D:/TEST_PRO3600/");//se connecte à l'adresse ip fournie
	void demandeDeco();//se deconnecte de l'adresse Ip à laquelle est co, fait rien si l'on est pas co
	// utilisé par traduction:
	void envoieMess(std::string mess);//envoie la chaine à l'ip du serveur

//Traduction:
// ces fonctions décodents les messages de type Tx, elles sont appelées par decode
	//pour le liv2 en  général il n'y a pas de choix pour la fonction qui sera appelée suivant le type de message (elle est marquée à chaque ligne après " liv  2 : ..."
	//en revanche il faut transformer la chaine de caractères en types de variables adéquats en enlevant CERTAINS séparateurs (pas forcément tous)

	// se REFERER au livrable 1 pour avoir l'ARCHITECTURE de chaque type de message, ATTENTION cette architecture dit que certaines parties du message sont des INT par exemple, 
	//mais le message est transmis sour forme d'un STRING UNIQUE, au codeur de regarder comment découper son message et convertir les string en int par exemple pour retrouver les bons types



	//UTILISER la fonction coupeChaine() (voir plus haut) pour séparer selon un separateur


	void iT0(std::string mess); //pour liv2 ce sera forcement 0c()
	//pas de séparateur
	void iT1(std::string mess); // liv  2 : renvoie vers  1ds() ou 1fs() suivant les bits du message (voir l'architecture)
	//pas de séparateur
	void iT2(std::string mess); // liv  2 : 2a() 
	//on ne touche PAS au séparateur
	void iT3(std::string mess); // liv  2 : 3a() pas de séparateur
	void iT4(std::string mess); // liv  2 : on appelle 4a() DEUX FOIS (une pour chaque perso en séparant suivant ' . ' )
	//séparateur: ' . ', on ne touche PAS aux ' ; '
	void iT6(std::string mess); // liv  2 : 6a() 
	//on ne touche PAS aux séparateurs

	//utilisée par transfert
	void decodeTypeMessage(std::string mess);//envoie vers iTx avec x entre 0 et 6 inclus

	//utilisée par client
	void envAct(int num_coup, int act); //T3 envoie l'action choisie au serveur , avec le num_coup qui a été demandé par le serveur plus tot,
	//  en utilisant l'ID_1 et en convertissant le tout sous forme d'un unique string


	//Client


	void ChoixAction();// on lance un  promt avec une description demandant d'entrer l'action à utiliser,
	// (il faut trouver une manière facile à traiter d'entrer ça et l'afficher dans la descri^ption des actions)
	// PUIS reconnait ce qui est entré et utilise envAct() avec le bon num_coup et le bon id_action

	//utilisé par traduction (normalement ~=  dans l'ordre de réception)


	//UTILISER la fonction coupeChaine() (voir plus haut) pour séparer selon un separateur si besoin est


	void Oc(int id_moi, int id_adv);// on sauvegarde les 2 id (on les affiche pour le debug)
	void _1ds(); // serveur dit que partie débute, à priori on fait rien de spécial dans le cas du liv2 , ptetre juste afficher "le combat débute" ou un truc du genre ?
	void _6a(std::string maj); // envoie juste a mAJ() sans rien faire d'autre									
	//séparateur: on n'y touche PAS c'est bibl qui s'occupe de tout
	void _4a(int id, std::string etat); // rempli un Conteneur_carac et l'affiche	en précédant de "moi" (= la personne qui joue ) ou "adversaire" suivant l'id
	//séparateur: '  ;  ' entre chaque carac
	void _2a(int num_coup, std::string actions_poss); //  affiche les possibilités dans "l'interface", puis   SI  num_coup= -1 s'arrète là , SINON demande à l'utilisateur d'entrer une action avec ChoixAction () puis 
	//séparateur: '  ;  '  entre chaque id d'action possible
	void _3a(int id, std::string act);// affiche "Je " OU "L'adversaire" + "utilise" + le nom de l'action en question, trouvé grâce à rechAction() dans le champ titre du conteneur renvoyé
	void _1fs(int id_gagnant);// serveur dit que partie est terminée , affiche qui a gagné 


	//utilise par transfert
	void servPerdu();// ecrit que le serveur s'est déconnecté puis arrète tout

	//Fin




#endif