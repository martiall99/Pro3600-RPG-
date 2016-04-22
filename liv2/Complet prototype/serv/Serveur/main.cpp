#include "ServerC.h"
#include "co_client\debug.h"

#include "Personnage.h"
#include "action_Tradxxx\traducteur.h"


#include <cstdlib>//pour rand
#include <ctime> //pour rand

#include <windows.h> //pour sleep


using namespace std;


Serveur_E s;
//---------------------Initialisation
void init()
{

		s.initS();


	//Variables communes
	
	ID_1 = 1;
	ID_2 = 2;
	

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
	perso1 = { "p1" };
	perso2 = { "p2" };
	j_1_co = false;
	j_2_co = false;
	deb_tour = true;

}
void fin()
{
		s.arret();
}

void decoJeu(int id)
{
	envFin(0);
}


//---------------------Transfert
void Lire_Fichier::transmetS()//transfere le texte du message à decodeTypeMessage()
{
	while (!en_attente.empty())
	{
		string a = en_attente.front();
		en_attente.pop_front();
		debug("Transmis Client  -> Serveur :" + a);
		decodeMess(a);
	}
}
void Lire_Fichier::deco()//appelé lorsqu'un des 2 joueurs se deco PEU importe lequel (dans tous els cas on arrete le combat), lance deco()
{
	debug("Perte d'un des joueurs, on arrete le serveur");
	decoJeu(0);

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
	{
		debug("envoi s->c1 : " + mess);
		s.envoi1(mess);
	}
	else if (id_dest == ID_2)
	{
		debug("envoi s->c2 : " + mess);
		s.envoi2(mess);
	}
	else
		debug("ERREUR, essai d'envoi d'un message \na l'ID : "+to_string(id_dest)+"  inconnue,\n mess = " + mess,true);
}


//-----------------------Aiguillage


//Aiguillage

//utilise par m_j
/* POUR TOUTES CES FONCTIONS D'ENVOI : se référer au LIVRABLE 1 pour avoir la DESCRIPTION de
l'architecture de chaque type de message*/

//celles qui envoient aux 2 grâce à deux appels de envoiMess()
void envEtats()
// T4 Envoie l'état des personnages e à chaque joueur
{

	string e = etatsPersos(ID_1);
	string mess = "4" + to_string(num_coup_attendu) + ";"+ e;
	envoiMess(mess, ID_1);
	e = etatsPersos(ID_2);
	mess = "4" + to_string(num_coup_attendu) + ";" + e;
	envoiMess(mess, ID_2);

	//cout << "Message T4 : " << mess << ", pour joueur d'id : " << ID_1 << endl;
	//cout << "Message T4 : " << mess << ", pour joueur d'id : " << ID_2 << endl;
}

void envDeb()
//T1d
{
	Sleep(200);//nécessaire pour l'ordre des messages ...
	string mess = "10010";
	envoiMess(mess, ID_1);
	envoiMess(mess, ID_2);
	//cout << "Message T1d : " << mess << ", pour joueur d'id : " << ID_1 << endl;
	//cout << "Message T1d : " << mess << ", pour joueur d'id : " << ID_2 << endl;
}

void iT3(std::string mess)
// liv  2 : 3a() pas de séparateur
{
	string mess_int = mess;
	int id_joueur = stoi(coupeChaine(mess_int, ';'));
	int numeroCoupJoue = stoi(coupeChaine(mess_int, ';'));
	string actionEffectuee = mess_int;
	recoitT3A(numeroCoupJoue,id_joueur, actionEffectuee);
}

void iT0(std::string mess)
//pour liv2 ce sera forcement _0c() pas de séparateur
{
	string mess_int = mess;
	mess_int.erase(0, 1);   //Efface le premier caractère qui correspond au booléen type0
	int ID_inutile_1 = stoi(coupeChaine(mess_int, ';'));
	int ID_inutile_2 = stoi(mess_int);
	co(ID_inutile_1);
}

void decodeMess(std::string mess)
//envoie vers iTx avec x entre 0 et 6 inclus
{
	string mess_int = mess;
	int premiere_val = stoi(mess_int.substr(0, 1));
	mess_int.erase(0, 1);

	if (premiere_val == 0)
	{
		iT0(mess_int);
	}
	else if (premiere_val == 3)
	{
		iT3(mess_int);
	}
	else 
	{
		debug("ERREUR, le message recu ne commence ni par 0 ni par 3, mess:\n" + mess);
	}
}

void envFin(int gagnant)
//T1f
{
	string mess = "1011" + to_string(gagnant);
	envoiMess(mess, ID_1);
	envoiMess(mess, ID_2);
	//cout << "Message T1f : " << mess << ", pour joueur d'id : " << ID_1 << endl;
	//cout << "Message T1f : " << mess << ", pour joueur d'id : " << ID_1 << endl;

	fin();
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
	string mess_pour_2 = "00" + to_string(ID_2) + ";" + to_string(ID_1);
	string mess_pour_1 = "00" + to_string(ID_1) + ";" + to_string(ID_2);

	envoiMess(mess_pour_1, ID_1);
	envoiMess(mess_pour_2, ID_2);
	//cout << "Message : " << mess_pour_2 << ", pour joueur d'id : " << ID_2 << endl;
	//cout << "Message : " << mess_pour_1 << ", pour joueur d'id : " << ID_1 << endl;
}


//celle qui n'envoie qu'à la bonne ID
void envActs(int numeroCouAttendu, std::string a, int ID_dest)
//T2a
{
	string mess = "2" + to_string(numeroCouAttendu) + ";" + a ;
	envoiMess(mess, ID_dest);
	//cout << "Message T2a : " << mess << ", destinataire id : " << ID_dest << endl;
}

//------------------------------------Maitre_jeu

string etatsPersos(int id)
{
	if (id==ID_1)
		return(perso1.etatsPerso() + '.' + perso2.etatsPerso());
	else
		return(perso2.etatsPerso() + '.' + perso1.etatsPerso());
}

void initBibli()
{
	string chaine_a_envoyer="";
	chaine_a_envoyer = perso1.attaques.toString() + "." + perso1.magies.toString() + "." + perso1.objets.toString();
	debug("env Bibli", true);
	envBibli(chaine_a_envoyer);
}

void debutJeu()
{
	srand(time(NULL)); // initialisation de rand pour les 2 personnages 


	perso1.initTraducteurs();
	perso2.initTraducteurs();

	debug("\n\nEnvoyer etats persos");
	envEtats();

	debug("\n\nInit bibli");
	initBibli();
	debug("\n\nEnvoyer debut", true);
	envDeb();
	debug("\n\nDebut tour", true);
	debTour();
	
}

int aGagne()
{
	
	if (perso1.caracs.PV <= 0)
		return ID_2;
	else if (perso2.caracs.PV <= 0)
		return ID_1;
		
	return -1;
	
}

void debTour()
{
	perso1.regenPa();
	perso2.regenPa();
	tour();
}

void recoitT3A(int num_coup, int id_j, string ac)
{
	if (id_j == a_qui_jouer && num_coup == num_coup_attendu) 
	{
		debug("message 3 recu : id_j,num/ac" + to_string(id_j) + "," + to_string(num_coup) + "/ " + ac);
		num_coup_attendu++;
		retransmet3(to_string(id_j) + ";" + to_string(num_coup) + ";" + ac);
		if (id_j == ID_1) 
		{
			perso1.Act(ac, perso2);
		}
		else if (id_j == ID_2) 
		{
			perso2.Act(ac,perso1);
		}
	}

}

void co(int id)
{
	if (j_1_co == false)
	{
		j_1_co = true;
		ID_1 = id;
		debug("joueur 1 identifie :" + to_string(ID_1));
	}
	else if (j_2_co == false)
	{
		j_2_co = true;
		ID_2 = id;
		debug("joueur 2 identifie :" + to_string(ID_2));
		debug("ID pretes a être envoyées");
		envID();
		debug("debut jeu");
		debutJeu();
	}
	else
	{
		debug("3e connexion ignoree");
	}
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
	num_coup_attendu++;
	debug("---Etats des persos\n" + perso1.caracs.toStringExplicit() + "\n\n" + perso2.caracs.toStringExplicit());
	if (aGagne() != -1) 
	{
		debug("Quelqun a gagné ! : " + to_string(aGagne()));
		envFin(aGagne());
	}
	else 
	{

		envEtats();

		if (a_qui_jouer == ID_1)
		{
			debug("au joueur1");
					envActs(num_coup_attendu, perso1.listeActionsPos(), ID_1);
		}
		if (a_qui_jouer == ID_2)
		{
			debug("au joueur2");
			envActs(num_coup_attendu,perso2.listeActionsPos(), ID_2);
		}
	}
}


//Personnage
void Personnage::Act(std::string a, Personnage &adv)// SI l'action ac ="00" => changeAQuiJouer() de maitre_jeu  , SINON utilise rechID() des 4 traducteurs puis effectue la bonne action puis lance tour() 
{
	int ac = stoi(a);
	//debug("\n\naction = " + a + " (bien verifier que c'est qqchose transformable en nombre et qu'il n'y a pas de lettres dedans sinon crash ... )");
	if (stoi(a) == 0)
	{
		debug(nom + " passe son tour ");
		changeAQuiJouer();
		debTour();
		return;
	}
	else
	{			
			Action *Ac;			
			Ac = attaques.rechID(ac);
			if (Ac->a_id==-1)
				Ac = magies.rechID(ac);
			if (Ac->a_id == -1)
				Ac=objets.rechID(ac);
			if (Ac->a_id == -1)
				debug("------------------------\nERREUR on n'a pas trouvé l'action "+a+" dans les traducteurs du joueur "+nom+"\n----------");
			else
			{
				debug(nom +" effectue : \n" + Ac->toString()+"\n");		
				Ac->eff(adv, *this);
				
			}
		
	}
	tour();


}
// TESTS  
void initRand()
{
	srand(time(NULL)); // initialisation de rand pour les 2 personnages 
}
void test_p()
{
	debug("hello world");

	//test recevoir degats
	initRand();//init le rand pour linstant juste
	Personnage lala;
	Personnage lalo;

	lalo.regenPa();
	debug("Lolo\n" + lalo.caracs.toStringExplicit());
	debug("lala \n" + lala.caracs.toStringExplicit(), true);

	lala.recevoirDegatsMagiques(20, 30, lalo);
	lalo.recevoirDegats(0, 20, lala);
	lala.recevoirSoins(0, 2);

	lala.changerArmure(12);
	lalo.regenPa();

	lalo.utiliserPa(25);
	lalo.utiliserPa(2);

	lala.utiliserMana(200);
	lala.utiliserMana(20);
	debug("Lolo\n" + lalo.caracs.toStringExplicit());
	debug("lala \n" + lala.caracs.toStringExplicit());
}

void lire(string &msg)
{
	cin >> msg;
}
void testIntegr()
{

	init();

	//debutJeu();


	/*
	debug("debut tests personnage");


	//test_p();



	perso1 = { "p1" };
	perso2 = { "p2" };
	perso1.initTraducteurs();
	perso2.initTraducteurs();

	perso1.regenPa();
	perso2.regenPa();
	debug("\n\n-----test perso.act()");
	perso1.Act("03", perso2);
	perso1.Act("00",perso2);
	debug("");


	perso2.Act("05", perso1);
	perso2.Act("05", perso1);
	perso2.Act("05", perso1);//doit renvyer une erreur si ca marhce bien !
	perso2.Act("00", perso2);
	*/


}

int main()
{


	debug("hello world");
	init();


	while (true)
		Sleep(100);
	
	/*
	debug("milieu", true);
	

	debug("Fin", true,true);
	*/


	
	/*
	string a = "";
	while (a != "quit")
		lire(a);
	*/
	decoJeu(-1);
	return 0;
}