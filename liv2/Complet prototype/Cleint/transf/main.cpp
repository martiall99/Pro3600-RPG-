#include "ClientC.h"
#include "../co/debug.h"
#include "../co/Client_E.h"
#include <windows.h> //pour sleep
using namespace std;

Client_E c = { 0 };

void debug(string mess, bool stop)
{
	if (true)
		cout << to_string(ID_1)<<": " +mess << endl;
	if (stop)
	{
		system("pause");
		cout << endl;
	}
}



//-----------------------INITIALISATION---------------------(non nécessaire a priori)
void initID(int id1, int id2)
{
	ID_1 = id1;
	ID_2 = id2;
}

void init()
{
	// Variables globales
	// Transfert tran; bibliothèque bibl; Traduction trad; Client cli;
	ID_1 = 0;
	ID_2 = 0;

	// Variable de :
	//bibl :

	int buffer_int = 0;
	buffer_type = "";
	buffer_titre = "";
	buffer_descr = "";

	//Transfert:
	c = Client_E({ 0 });
	/*
	std::string IP_client;
	std::string IP_serveur;
	std::string port_client;
	std::string port_serv;
	*/

	//Trad
	partie_debutee = false;

	//client
	numero_coup = -1;
}

//----------------------Transfert----------------------------


void Lire_Fichier::transmetC()//transfere le texte du message à decodeTypeMessage()
{
	while (!en_attente.empty())
	{
		string a = en_attente.front();
		en_attente.pop_front();
		debug("Transmis Serveur -> Client :" + a);
		decodeTypeMessage(a);
	}
}
void Lire_Fichier::deco()//appelé lorsque le serveur se deco (pb connexion) , lance servPerdu()
{
	debug("Perte du serveur");
	demandeDeco();
}

//utilise par client
void demandeCo(int id, std::string dir)//creer les fichiers textes d'echange
{
	c = Client_E({ id, dir });
	c.initC();
	
	debug(c.verif(), "Connexion Client_serveur ");
	envoieMess("01"+to_string(id)+";0");
}

void demandeDeco()//se deconnecte de l'adresse Ip à laquelle est co, fait rien si l'on est pas co
{
	//if (c.verif())
		c.arret();
}
// utilisé par traduction:
void envoieMess(std::string mess)//envoie la chaine à l'ip du serveur
{
	c.envoiS(mess);
}

//-------------------Bibli------------------------

void ajLigne()
{
	tab_id.push_back(buffer_int);
	tab_type.push_back(buffer_type);
	tab_titre.push_back(buffer_titre);
	tab_descr.push_back(buffer_descr);
}

void modifLigne(int noLigne)
{
	tab_id[noLigne] = buffer_int;
	tab_type[noLigne] = buffer_type;
	tab_titre[noLigne] = buffer_titre;
	tab_descr[noLigne] = buffer_descr;
}


int rechLigne()
{
	int id = buffer_int;
	unsigned int noLigne = 0;
	for (noLigne = 0; noLigne<tab_id.size(); noLigne++) {
		if (id == tab_id[noLigne])
			return(noLigne);
	}
	return(-1);
}

void interpreterLigne(string Ligne)
{
	string ligne = Ligne;
	string mot;
	char separateur = ';';
	mot = coupeChaine(ligne, separateur);
	buffer_int = std::atoi(mot.c_str());
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

void testBibl()
{
	for (int i = 0; i<tab_id.size(); i++)
	{
		debug(tab_id[i] + "||" + tab_type[i] + "||" + tab_titre[i] + "||" + tab_descr[i]);
	}
}

void mAJ(string MAJ)
{
	string lignes_type;
	string lignes;

	buffer_type = "Attaques";
	//MAJ contient tous les types separes par des .
	lignes_type = coupeChaine(MAJ, '.');
	//lignes_type contient a present toutes les lignes d'un type separees par des /
	bool boucle = true;
	lignes = coupeChaine(lignes_type, '/');
	while (lignes != "") {
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
	while (lignes != "") {
		interpreterLigne(lignes); //On interprete chaque ligne d'un type donne
		lignes = coupeChaine(lignes_type, '/');
	}
	interpreterLigne(lignes_type);

	buffer_type = "Objets";
	//Maj ne contient plus que les objets
	boucle = true;
	lignes = coupeChaine(MAJ, '/');
	while (lignes != "") {
		interpreterLigne(lignes); //On interprete chaque ligne d'un type donne
		lignes = coupeChaine(MAJ, '/');
	}
	interpreterLigne(MAJ);
	testBibl();
}


Cont_action rechAction(int id)
{
	int noLigne;
	buffer_int = id;

	noLigne = rechLigne();
	if (noLigne == -1) {
		buffer_type = "";
		buffer_titre = "";
		buffer_descr = "";
	}
	else {
		buffer_type = tab_type[noLigne];
		buffer_titre = tab_titre[noLigne];
		buffer_descr = tab_descr[noLigne];
	}

	return(Cont_action({ buffer_titre,buffer_type, buffer_descr }));
}

//------------------------------------Client

void afficher(string msg)
{
	cout << msg << endl;
}

void lire(string &msg)
{
	cin >> msg;
}


void _0c(int id_moi, int id_adv)// on sauvegarde les 2 id (on les affiche pour le debug)
{
	 ID_1= id_moi ;
	 ID_2= id_adv ;
	afficher("mon id = "+to_string(ID_1));
	afficher("id adversaire= "+to_string(ID_2));
}
void _1ds() // serveur dit que partie débute, à priori on fait rien de spécial dans le cas du liv2 , ptetre juste afficher "le combat débute" ou un truc du genre ?
{
	afficher("Debut du combat");
	//cout << "Début du combat" <<endl;
}
void _6a(std::string maj) // envoie juste a mAJ() sans rien faire d'autre
						  //séparateur: on n'y touche PAS c'est bibl qui s'occupe de tout
{
	mAJ(maj);
}
Conteneur_carac eta(string etat)
{
	Conteneur_carac c = { 0,0,0,0,0,0,0,0 };
	string b = coupeChaine(etat, ';');
	//debug("etat= " + etat + " b=" + b, true);
	c.PV = stoi(b);
	b = coupeChaine(etat, ';');
	c.Mana = stoi(b);
	b = coupeChaine(etat, ';');
	c.PA = stoi(b);
	b = coupeChaine(etat, ';');
	c.DEF = stoi(b);
	b = coupeChaine(etat, ';');
	c.RES = stoi(b);
	b = coupeChaine(etat, ';');
	c.CRIT = stoi(b);
	b = coupeChaine(etat, ';');
	c.ESQ = stoi(b);
	b = coupeChaine(etat, ';');
	c.RENV = stoi(etat);
	return c;
}
// rempli un Conteneur_carac et l'affiche	en précédant de "moi" (= la personne qui joue ) ou "adversaire" suivant l'id
//séparateur: '  ;  ' entre chaque carac et '.' entre chaque adversaire
void _4a(int id_coup, std::string etat) 
{
	//debug("ETAT= " + etat);
	string perso1 = coupeChaine(etat, '.');
	Conteneur_carac etat1 = eta(perso1);
	Conteneur_carac etat2 = eta(etat);

	afficher("Moi :");
	afficher(etat1.toStringExplicit());
	afficher("\n");


	afficher("L'adversaire :");
	afficher(etat2.toStringExplicit());
	afficher("\n");
}

void Proposer_act(string act, bool dem=true)
{
	string cop = act;
	string deb = coupeChaine(cop, ';');
	if (dem)
		afficher("Tapez : 0 pour  Passer le tour \n");

	while (deb != "")
	{
		int a = stoi(deb);
		Cont_action c= rechAction(a);
		if(dem)
			afficher("\nTapez : " + to_string(a) + " pour ");
		afficher (" Nom: " + c.titre + "\n Description : " + c.descr);
		deb = coupeChaine(cop, ';');
	}
}
void ChoixAction(int num, string choix, string act_pos)
{
	string cop = act_pos;
	string deb = coupeChaine(cop, ';');
	while (deb != "")
	{
		if (choix == deb || choix == "0")
		{
			envAct(num, stoi(choix));
			return;
		}
		deb = coupeChaine(cop, ';');
	}
	afficher("Veuiller rentrer une des possibilités");
	lire(choix);// si on a pas trouve c'est qu'il y a eu un pb
	ChoixAction(num, choix, act_pos);
}
void _2a(int num_coup, std::string actions_poss) //  affiche les possibilités dans "l'interface", puis   SI  num_coup= -1 s'arrète là , SINON demande à l'utilisateur d'entrer une action avec ChoixAction () puis
												 //séparateur: '  ;  '  entre chaque id d'action possible
{
	if ((num_coup == -1))
	{
		afficher("Actions possibles:");
		Proposer_act(actions_poss, false);
	}
	if (num_coup != -1)
	{
		afficher("Choisissez votre action");
		Proposer_act(actions_poss, true);
		string a;
		lire(a);
		ChoixAction(num_coup, a, actions_poss);
	}
}
void _3a(int id, std::string act)// affiche "Je " OU "L'adversaire" + "utilise" + le nom de l'action en question, trouvé grâce à rechAction() dans le champ titre du conteneur renvoyé
{

	 int action1 =stoi(act);
	
	Cont_action action = rechAction(action1);
	if (id==ID_1)
	{
		if (action1 == 0)
			afficher("Je passe mon tour");
		else
			afficher( "J'utilise " + action.titre +"\n");
	}
	else
	{
		if (action1 == 0)
			afficher("Je passe mon tour");
		else
			afficher("L'Adversaire utilise " + action.titre + "\n");
	}
	
}
void _1fs(int id_gagnant)// serveur dit que partie est terminée , affiche qui a gagné
{
	afficher("Partie terminee");
	cout << "Le gagnant est " << to_string(id_gagnant) << endl;
}

void servPerdu()
{
	demandeDeco();
}

//------------------------------Traduction
void iT0(std::string mess)
//pour liv2 ce sera forcement _0c() pas de séparateur
{
	string mess_int = mess;
	mess_int.erase(0, 1);   //Efface le premier caractère qui est correspond au booléen type0
	int ID_inutile_1 = stoi(coupeChaine(mess_int, ';'));
	int ID_inutile_2 = stoi(mess_int);
	_0c(ID_inutile_1,ID_inutile_2);
}

void iT1(std::string mess)
/* liv  2 : renvoie vers  1ds() ou 1fs() suivant les bits du message (voir l'architecture) pas de séparateur */
{
	string mess_int = mess;
	int type_1 = stoi(mess_int.substr(0, 1)); // on reccupère le 1er caractère de mess
	int type_2 = stoi(mess_int.substr(1, 1)); // on reccupère le 2ème caractère de mess
	mess_int.erase(0, 2);

	if ((type_1 == 0) && (type_2 == 0))
	{
		_1ds();
		//debug("Debut de la partie, on vire les // et on lance _1ds()");
	}

	else if ((type_1 == 0) && (type_2 == 1))
	{
		mess_int.erase(0, 1); // on supprime le bit coresspondant à l'information/la demande
		int id_gagnant = stoi(mess_int.substr(0));
		_1fs(id_gagnant);
		//debug( "Partie terminee, On vire // et lance _1fs(int id_gagnant)" );
	}

	else if ((type_1 == 1) && (type_2 == 0))
	{
		//debug ("utile pour liv3, pas pour le liv2" );
	}

	else if ((type_1 == 1) && (type_2 == 1))
	{
		//debug ("utile pour liv3, pas pour le liv2" );
	}

}

void iT2(std::string mess)
// liv  2 : 2a(), on ne touche PAS au séparateur
{
	string mess_int = mess;
	int numeroCoupAttendu = stoi(coupeChaine(mess_int, ';'));
	string listeActionsPossibles = mess_int;
	_2a(numeroCoupAttendu, listeActionsPossibles);

}


void iT3(std::string mess)
// liv  2 : 3a() pas de séparateur
{
	string mess_int = mess;
	int id_joueur = stoi(coupeChaine(mess_int, ';'));
	int numeroCoupJoue = stoi(coupeChaine(mess_int, ';')); // on l'utilise pas ici
	string actionEffectuee = mess_int;
	 _3a(id_joueur, actionEffectuee );
}

void iT4(std::string mess)
/* liv  2 : on appelle 4a() DEUX FOIS (une pour chaque perso en séparant
suivant ' . ' ) ,séparateur: ' . ', on ne touche PAS aux ' ; '*/
{
	string mess_int = mess;
	int numeroCoupJoue = stoi(coupeChaine(mess_int, ';'));
	_4a(numeroCoupJoue,mess_int);
}

void iT6(std::string mess)
// liv  2 : 6a(), on ne touche PAS aux séparateurs
{
	 _6a(mess);
}


void decodeTypeMessage(std::string mess)
//envoie vers iTx avec x entre 0 et 6 inclus
{
	string mess_int = mess;
	int premiere_val = stoi(mess_int.substr(0, 1));
	mess_int.erase(0, 1);

	if (premiere_val == 0)
	{
		iT0(mess_int);
	}

	else if (premiere_val == 1)
	{
		iT1(mess_int);
	}

	else if (premiere_val == 2)
	{
		iT2(mess_int);
	}

	else if (premiere_val == 3)
	{
		iT3(mess_int);
	}

	else if (premiere_val == 4)
	{
		iT4(mess_int);
	}

	else if (premiere_val == 5)
	{
		//iT5(mess_int);
		//cout << "Message : " << mess_int << ", envoye vers iT5" << endl;
	}

	else if (premiere_val == 6)
	{
		iT6(mess_int);
	}
}
void envAct(int num_coup, int act)
{
	string mess = "3" + to_string(ID_1) + ";" + to_string(num_coup) + ";" + to_string(act);
	envoieMess(mess);
}

void testC()
{
	string nouvelleLigne = "1;charge;inflige des degats normaux/2;lechouille;speciale martiale : fait fuir l'adversaire.3;flammeche;petites flammes/4;saut jusquau ciel;yolo tmtc.5;ceci est un objet; objet objet";
	mAJ(nouvelleLigne);
	//testBibl();

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
	string test_1 = "00156";
	string test_2 = "01156";
	string test_3 = "10156";
	iT1(test_1);
	iT1(test_2);
	iT1(test_3);
	*/

	/*
	cout << "---Test unitaire pour iT2---" << endl;
	string test = "215;1;2;3;";
	iT2(test);
	*/

	/*
	cout << "---Test unitaire pour iT3---" << endl;
	string test = "2;265;3";
	iT3(test);
	*/

	/*
	cout << "---Test unitaire pour iT4---" << endl;
	string test = "1;1;2;3;5;6;7;9;0.1;3;56;2;298;7;6;8";
	iT4(test);
	*/

	// iT5 n'est pas utile pour le livrable 2.

	/*
	cout << "---Test unitaire pour iT6---" << endl;
	string test = "15;1;charge;inflige des degats normaux/2;lechouille;speciale martiale : fait fuir l'adversaire.3;flammeche;petites flammes/4;saut jusquau ciel;yolo tmtc.5;ceci est un objet; objet objet";
	iT6(test);
	*/

	/*
	cout << "---- Test unitaire pour envAct(int num_coup, int act), message de type T3 ---" << endl;
	envAct( 235, 25 );
	*/

	debug("tests unitaires decode", true);
	//cout << "---- Test unitaire pour decodeTypeMessage(std::string mess), envoye vers iTx avec x entre 0 et 6 inclus ---\n" << endl;
	decodeTypeMessage("002122;6523");
	debug("----------------------------------------");
	decodeTypeMessage("100156");
	debug("----------------------------------------");
	decodeTypeMessage("101156");
	debug("----------------------------------------");
	decodeTypeMessage("2215;1;2;3;");
	debug("----------------------------------------");
	decodeTypeMessage("41; 1; 2; 3; 5; 6; 7; 9; 0.1; 3; 56; 2; 298; 7; 6; 8");
	debug("----------------------------------------");
	decodeTypeMessage("32;265;3");
	debug("----------------------------------------");
	decodeTypeMessage("615;1;charge;inflige des degats normaux/2;lechouille;speciale martiale : fait fuir l'adversaire.3;flammeche;petites flammes/4;saut jusquau ciel;yolo tmtc.5;ceci est un objet; objet objet");




	debug("FIN au prochain appui", true);
}

int main()
{
	debug("hlo word");
	init();

	string id = "";
	afficher("veuillez entrer votre ID joueur");
	lire(id);
	ID_1=stoi(id);
	
	demandeCo(ID_1,"D:/TEST_PRO3600/");


	while (true)
		Sleep(100);


	debug("FIN au prochain appui",true);
	demandeDeco();

}

