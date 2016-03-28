#include "ServerC.h"
#include "co_client\debug.h"


#include "action_Tradxxx\trad_attaq.h"

using namespace std;


Serveur_E s;
//---------------------Initialisation
void init()
{

	//Variables communes
	/*
	ID_1 = 1;
	ID_2 = 2;
	*/

	//transfert:
	/*
	IP_1 = "";
	IP_2 = "";
	port_s = "";// A CHANGER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	port_c = "";// A CHANGER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	*/

	//aiguillage:


	//maitre_jeu
	num_coup_attendu = 0;
	a_qui_jouer = ID_1;
	//perso1(); //on rappelle les constructeurs au cas ou
	//perso2();
	j_1_co = false;
	j_2_co = false;
	deb_tour = true;

}



//---------------------Transfert
void Lire_Fichier::transmetS()//transfere le texte du message à decodeTypeMessage()
{
	while (!en_attente.empty())
	{
		string a = en_attente.front();
		en_attente.pop_front();
		//decodeMess(a);
		//debug("Transmis Client  -> Serveur :" + a);
	}
}
void Lire_Fichier::deco()//appelé lorsqu'un des 2 joueurs se deco PEU importe lequel (dans tous els cas on arrete le combat), lance servPerdu()
{
	//servPerdu();
	debug("Perte du serveur");

}

//utilise par client
void demandeCo( std::string dir)//creer les fichiers textes d'echange
{
	s = Serveur_E({  dir });
	s.initS();

	debug(s.verif1(), "Connexion serveur <-> Cli1 ");
	debug(s.verif2(), "Connexion serveur <-> Cli2 ");
}

// utilisé par traduction:
void envoiMess(std::string mess, int id_dest)
{
	if (id_dest == ID_1)
		s.envoi1(mess);
	else if (id_dest == ID_2)
		s.envoi2(mess);
	else
		debug("ERREUR, essai d'envoi d'un message \na l'ID : "+to_string(id_dest)+"  inconnue,\n mess = " + mess,true);
}


//-----------------------Aiguillage


//Aiguillage

//utilise par m_j
/* POUR TOUTES CES FONCTIONS D'ENVOI : se référer au LIVRABLE 1 pour avoir la DESCRIPTION de
l'architecture de chaque type de message*/

//celles qui envoient aux 2 grâce à deux appels de envoiMess()
void envEtats(std::string e)
// T4 Envoie l'état des personnages e à chaque joueur
{
	string mess = "4" + e;
	envoiMess(mess, ID_1);
	envoiMess(mess, ID_2);

	//cout << "Message T4 : " << mess << ", pour joueur d'id : " << ID_1 << endl;
	//cout << "Message T4 : " << mess << ", pour joueur d'id : " << ID_2 << endl;
}

void envDeb()
//T1d
{
	string mess = "10010";
	envoiMess(mess, ID_1);
	envoiMess(mess, ID_2);
	//cout << "Message T1d : " << mess << ", pour joueur d'id : " << ID_1 << endl;
	//cout << "Message T1d : " << mess << ", pour joueur d'id : " << ID_2 << endl;
}


void envFin(int gagnant)
//T1f
{
	string mess = "1011" + to_string(gagnant);
	envoiMess(mess, ID_1);
	envoiMess(mess, ID_2);
	//cout << "Message T1f : " << mess << ", pour joueur d'id : " << ID_1 << endl;
	//cout << "Message T1f : " << mess << ", pour joueur d'id : " << ID_1 << endl;
}

void envBibli(std::string bib)
//T6
{
	string mess = "6" + bib;
	envoiMess(mess, ID_1);
	envoiMess(mess, ID_2);
	//cout << "Message T6 : " << mess << ", pour joueur d'id : " << ID_1 << endl;
	//cout << "Message T6 : " << mess << ", pour joueur d'id : " << ID_2 << endl;
}

void retransmet3(std::string a)
//renvoie l'action qui vient dêtre effectuee AUX DEUX clients
{
	string mess = "3" + a;
	envoiMess(mess, ID_1);
	envoiMess(mess, ID_2);
	cout << "Message T3a : " << mess << endl;
}

void envID()
/* T0c: envoie les 2 ID à la suite 2 fois (une pour chaque destinataire) avec à
chaque fois l'ID du destinataire en PREMIER ( ATTENTION !! )*/
{
	string mess_pour_2 = "0" + to_string(ID_2) + ";" + to_string(ID_1);
	string mess_pour_1 = "0" + to_string(ID_1) + ";" + to_string(ID_2);
	envoiMess(mess_pour_1, ID_1);
	envoiMess(mess_pour_2, ID_2);
	//cout << "Message : " << mess_pour_2 << ", pour joueur d'id : " << ID_2 << endl;
	//cout << "Message : " << mess_pour_1 << ", pour joueur d'id : " << ID_1 << endl;
}


//celle qui n'envoie qu'à la bonne ID
void envActs(int numeroCouAttendu, std::string a, int ID_dest)
//T2a
{
	string mess = "2" + to_string(numeroCouAttendu) + ";" + a + ";";
	envoiMess(mess, ID_dest);
	//cout << "Message T2a : " << mess << ", destinataire id : " << ID_dest << endl;
}

//------------------------------------Maitre_jeu


void initBibli()
{
	string chaine_a_envoyer;
	//chaine_a_envoyer = perso1.attaques.toString() + "." + perso1.magies.toString() + "." + perso1.objets.toString();
	envBibli(chaine_a_envoyer);
}

void debutJeu()
{
	/*
	perso1.initTraducteurs();
	perso2.initTraducteurs();

	envEtats(perso1.etatsPerso);
	envEtats(perso2.etatsPerso);

	envDeb();

	debTour();
	*/
}

int aGagne()
{
	/*
	if (perso1.PV <= 0)
		return ID_2;
	else if (perso2.PV <= 0)
		return ID_1;
		*/
	return -1;
	
}

void debTour()
{
	//perso1.regenPA();
	//perso2.regenPA();
	tour();
}

void recoitT3A(int num_coup, int id_j, string ac)
{
	if (id_j == a_qui_jouer && num_coup == num_coup_attendu) {
		num_coup_attendu++;
		retransmet3(to_string(id_j) + ";"+ac);
		if (id_j == ID_1) 
		{
			//perso1.Act(ac);
		}
		else if (id_j == ID_2) 
		{
			//perso2.Act(ac);
		}
	}

}

void co(int id)
{
	if (j_1_co == false)
		j_1_co = true;
	else if (j_2_co == false)
	{
		j_2_co = true;
		envID();
		debutJeu();
	}
}

void deco(int id)
{
	envFin(0);
}

void changeAQuiJouer()
{
	if (a_qui_jouer == ID_1)
		a_qui_jouer = ID_2;
	else if (a_qui_jouer == ID_2)
		a_qui_jouer = ID_1;
}

void tour()
{
	if (aGagne() != -1) 
	{
		envFin(aGagne());
	}
	else 
	{

		//envEtats(perso1.etatsPerso()+"."perso2.etatsPerso());

		if (a_qui_jouer == ID_1)
		{
			//		envActs(perso1.listeActionsPos, ID_1);
		}
		if (a_qui_jouer == ID_2)
		{
			//		envActs(perso2.listeActionsPos, ID_2);
		}
	}
}




int main()
{
	debug("hello world");
	init();
	s.initS();
	debug("debut tests",true);


	debug("Fin du serveur apres => ", true);
	s.arret();


	return 0;
}