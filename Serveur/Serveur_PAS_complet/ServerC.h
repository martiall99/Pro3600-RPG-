#ifndef SERVERC
#define SERVERC

#include "co_client\Serveur_E.h"
#include "Conteneurs_carac_action\Conteneur_carac.h"
#include "Conteneurs_carac_action\conteneurAction.h"



// --------------------------------"VRAIS" OBJETS ------------------------------





//Variables communes
// Transfert tr; Aiguillage aig; Maitre_jeu m_j; 
const int ID_1=1;
const int ID_2=2;


//variables de :
//transfert:
/*
std::string IP_1;
std::string IP_2;
const std::string port_s;//un seul port serveur
const std::string port_c;//c'est le même pour les 2 clients aussi
*/


//maitre_jeu
int num_coup_attendu;
int a_qui_jouer;
/*
Personnage perso1;
Personnage perso2;
*/
bool j_1_co;
bool j_2_co;
bool deb_tour;



	//----------------------------------------------------Méthodes de :


	//initialisation de TOUTES les variables de tous les "objets" 
	void init();// c'est LITTERALEMENT un copié collé de ce qui est en dessous :

	//transfert:

	void tCoClient();//(appelé lorsqu'un clietn se connecte) garde l'IP (dans le bon slot ) et appelle direct  co() de maitre_jeu
	void tDecoClient();//(appelé lorsqu'un clietn se deconnecte)appelle directement deco() de maitre_jeu
	void recoitMess(); //appelle direct decodeMess() de aiguillage


	// utilisée par aiguillage
	void envoiMess(std::string mess, int id_dest);//envoie le mess à l'IP_x avec x tel que  id_dest = ID_x (ya que 2 x possible un simple if else if else (erreur)  suffit)
	//util au tout debut/fin
	void ouvrirConnex();// ouvre DEUX connexions à travers  1 port
	void fermerConnex();




	//aiguillage

	//remarque ici pas d'iT1, le jeu debute dès que les 2 clients sont connectés
	void iT3a(std::string mess);

//util par transfert
	void decodeMess(std::string mess);// appelle les iTx ici uniquement iT3 donc en soit n'est pas nécessaire mais le sera pour livrable 3
	//util par m_j
	// POUR TOUTES CES FONCTIONS D'ENVOI : se référer au LIVRABLE 1 pour avoir la DESCRIPTION de l'architecture de chaque type de message
	//celles qui envoient au 2 grâce à deux appels de envoiMess()
	void envEtats(std::string e);//T4
	void envDeb();//T1d
	void envFin(int gagnant);//T1f 
	void envBibli(std::string bib);//T6
	void retransmet3(std::string a);//renvoie l'action qui vient dêtre effectuee AUX DEUX clients 
	void envID();//T0c: envoie les 2 ID à la suite 2 fois (une pour chaque destinataire) avec à chaque fois l'ID du destinataire en PREMIER ( ATTENTION !! )


	//celle qui n'envoie qu'à la bonne ID
	void envActs(std::string a, int ID_dest); //T2a  




	//maitre_jeu


	void initBibli();// on récupère les 3  attaques.toString(), magies.toString(), objets.toString()   puis appelle envBibli()
	void debutJeu();// 1) initTraducteurs() des 2 persos 2) initBibli() , 3)etatsPersos() des 2 puis envEtats()  4)  envDeb() 5) debTour()
	int aGagne();//renvoie l'id du joueur qui a gagné (joueur adverse a PV<=0 ) ou  -1 si 
	void debTour();//applique le  regenPA  de chaque personnage, puis lance tour()



	//util par aiguillage
	void recoitT3A(int num_coup, int id_j, std::string ac);//verifie id et num_coup, puis incremente  num_coup_attendu, puis retransmet3() puis Act() de personnage

	//util par transfert 
	void co(int id);//SI j_1_co==false le met a true        OU           SI j_2_co==false le met a vrai ET et lance envID() ET lance debutJeu()
	void deco(int id);// arrete le jeu avec un envFin() avec en id 0 pour dire que c'est une erreur/pas de gagnant

	//util par perso
	void changeAQuiJouer();// change id puis SI deb_tour==true met deb_tourà false et lance debTour() SINON met deb_tour à true et lance tour();
	void tour();// 0) regarde a_qui_jouer ( PUIS vérifie aGagne() , interromp tout et envFin() si c'est le cas ) puis  1)recupere etatsPersos()  2) envEtats 3)recupere listeActionsPos() du bon joueur  puis 4) envActs() au bon joueur







#endif