#ifndef CLIENT_C
#define CLIENT_C

#include "Conteneurs_carac_action/Conteneur_carac.h"
#include "Conteneurs_carac_action/conteneurAction.h"

#include <vector>
#include <string>
#include <cstdlib>



// Variables globales
// Transfert tran; biblioth�que bibl; Traduction trad; Client cli;
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


//bibl:// principe du fonctionnement : mAJ() (ouioui l'�criture est fait expr�s) coupe la chaine envoy�e avec coupeChaine(), remplie std::string buffer_type et envoie a interpreterLigne()
// celui ci recoupe et rempli chaque type de buffer (int buffer_int;std::string buffer_titre;std::string buffer_descr; ) avec la bonne partie de la chaine initiale
//celui l� regarde s'il y a d�ja une ligne correspondant au m�me sort puis la modifie si c'est le cas ou en cr�� une nouvelle sinon


	void ajLigne();//cr�er la ligne dont les caract�ristiques sont dans les buffers
	void modifLigne(int ligne);// remplace la ligne a modifier (dont les nouvelles caract�ristiques sont dans les buffers)
	int rechLigne();// renvoie le NUMERO de la LIGNE ( ATTENTION != ID du sort) dont l'ID est stock�e dans buffer( ATTENTION il est en g�n�ral diff�rent de l'ID de l'action), renvoie -1 si l'id n'est pas stock�e
	void interpreterLigne(std::string Ligne); // s�pare chaque champ, remplit chaque buffer, appelle rechLigne(), si il y a une correspondance appelle modifLigne(), sinon ajLigne()
	//s�parateur: '  ;  '  entre chaque "composante" (ID, titre, description) d'une action possible

	Cont_action rechAction(int id);// rechLigne() puis renvoie un cont_action contenant le contenu de la ligne, si aucune correspondance renvoie des champs vides ""
	void mAJ(std::string MAJ);// s�pare � ' / ' et appelle 	interpreterLigne() sur chaque, en remplacant au pr�alable le buffer_type avec le bon mot ( dans l'ordre : attaques, magie, objets, buffs) 
	//s�parateur: '  /  '  entre chaque action possible   et ' . ' entre chaque type d'actions ( dans l'ordre : attaques, magie, objets) 

//transfert:
 //utilise par client
	void demandeCo(int id, std::string dir="D:/TEST_PRO3600/");//se connecte � l'adresse ip fournie
	void demandeDeco();//se deconnecte de l'adresse Ip � laquelle est co, fait rien si l'on est pas co
	// utilis� par traduction:
	void envoieMess(std::string mess);//envoie la chaine � l'ip du serveur

//Traduction:
// ces fonctions d�codents les messages de type Tx, elles sont appel�es par decode
	//pour le liv2 en  g�n�ral il n'y a pas de choix pour la fonction qui sera appel�e suivant le type de message (elle est marqu�e � chaque ligne apr�s " liv  2 : ..."
	//en revanche il faut transformer la chaine de caract�res en types de variables ad�quats en enlevant CERTAINS s�parateurs (pas forc�ment tous)

	// se REFERER au livrable 1 pour avoir l'ARCHITECTURE de chaque type de message, ATTENTION cette architecture dit que certaines parties du message sont des INT par exemple, 
	//mais le message est transmis sour forme d'un STRING UNIQUE, au codeur de regarder comment d�couper son message et convertir les string en int par exemple pour retrouver les bons types



	//UTILISER la fonction coupeChaine() (voir plus haut) pour s�parer selon un separateur


	void iT0(std::string mess); //pour liv2 ce sera forcement 0c()
	//pas de s�parateur
	void iT1(std::string mess); // liv  2 : renvoie vers  1ds() ou 1fs() suivant les bits du message (voir l'architecture)
	//pas de s�parateur
	void iT2(std::string mess); // liv  2 : 2a() 
	//on ne touche PAS au s�parateur
	void iT3(std::string mess); // liv  2 : 3a() pas de s�parateur
	void iT4(std::string mess); // liv  2 : on appelle 4a() DEUX FOIS (une pour chaque perso en s�parant suivant ' . ' )
	//s�parateur: ' . ', on ne touche PAS aux ' ; '
	void iT6(std::string mess); // liv  2 : 6a() 
	//on ne touche PAS aux s�parateurs

	//utilis�e par transfert
	void decodeTypeMessage(std::string mess);//envoie vers iTx avec x entre 0 et 6 inclus

	//utilis�e par client
	void envAct(int num_coup, int act); //T3 envoie l'action choisie au serveur , avec le num_coup qui a �t� demand� par le serveur plus tot,
	//  en utilisant l'ID_1 et en convertissant le tout sous forme d'un unique string


	//Client


	void ChoixAction();// on lance un  promt avec une description demandant d'entrer l'action � utiliser,
	// (il faut trouver une mani�re facile � traiter d'entrer �a et l'afficher dans la descri^ption des actions)
	// PUIS reconnait ce qui est entr� et utilise envAct() avec le bon num_coup et le bon id_action

	//utilis� par traduction (normalement ~=  dans l'ordre de r�ception)


	//UTILISER la fonction coupeChaine() (voir plus haut) pour s�parer selon un separateur si besoin est


	void Oc(int id_moi, int id_adv);// on sauvegarde les 2 id (on les affiche pour le debug)
	void _1ds(); // serveur dit que partie d�bute, � priori on fait rien de sp�cial dans le cas du liv2 , ptetre juste afficher "le combat d�bute" ou un truc du genre ?
	void _6a(std::string maj); // envoie juste a mAJ() sans rien faire d'autre									
	//s�parateur: on n'y touche PAS c'est bibl qui s'occupe de tout
	void _4a(int id, std::string etat); // rempli un Conteneur_carac et l'affiche	en pr�c�dant de "moi" (= la personne qui joue ) ou "adversaire" suivant l'id
	//s�parateur: '  ;  ' entre chaque carac
	void _2a(int num_coup, std::string actions_poss); //  affiche les possibilit�s dans "l'interface", puis   SI  num_coup= -1 s'arr�te l� , SINON demande � l'utilisateur d'entrer une action avec ChoixAction () puis 
	//s�parateur: '  ;  '  entre chaque id d'action possible
	void _3a(int id, std::string act);// affiche "Je " OU "L'adversaire" + "utilise" + le nom de l'action en question, trouv� gr�ce � rechAction() dans le champ titre du conteneur renvoy�
	void _1fs(int id_gagnant);// serveur dit que partie est termin�e , affiche qui a gagn� 


	//utilise par transfert
	void servPerdu();// ecrit que le serveur s'est d�connect� puis arr�te tout

	//Fin




#endif