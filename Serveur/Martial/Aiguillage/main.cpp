#include <iostream>
#include "aiguillage.h"
#include <sstream>
#include <string>

#include <sstream>

using namespace std;

string to_String(int a)
{
    stringstream ss;
    ss<<a;
    return ss.str();
}
//Aiguillage

//utilise par m_j
	/* POUR TOUTES CES FONCTIONS D'ENVOI : se référer au LIVRABLE 1 pour avoir la DESCRIPTION de
	l'architecture de chaque type de message*/

	//celles qui envoient aux 2 grâce à deux appels de envoiMess()
	void envEtats(std::string e)
	// T4 Envoie l'état des personnages e à chaque joueur
	{
        string mess = "4" + e;
        //envoiMess(mess, ID_1);
        //envoiMess(mess, ID_2);
        cout << "Message T4 : " << mess << ", pour joueur d'id : " << ID_1 << endl;
        cout << "Message T4 : " << mess << ", pour joueur d'id : " << ID_2 << endl;
	}

	void envDeb()
	//T1d
	{
	    string mess = "10010";
	    //envoiMess(mess, ID_1);
        //envoiMess(mess, ID_2);
        cout << "Message T1d : " << mess << ", pour joueur d'id : " << ID_1 << endl;
        cout << "Message T1d : " << mess << ", pour joueur d'id : " << ID_2 << endl;
	}


	void envFin(int gagnant)
	//T1f
    {
        string mess = "1011" + to_String(gagnant);
        //envoiMess(mess, ID_1);
        //envoiMess(mess, ID_2);
        cout << "Message T1f : " << mess << ", pour joueur d'id : " << ID_1 << endl;
        cout << "Message T1f : " << mess << ", pour joueur d'id : " << ID_1 << endl;
    }

	void envBibli(std::string bib)
	//T6
	{
	    string mess = "6" + bib ;
	    //envoiMess(mess, ID_1);
        //envoiMess(mess, ID_2);
        cout << "Message T6 : " << mess << ", pour joueur d'id : " << ID_1 << endl;
        cout << "Message T6 : " << mess << ", pour joueur d'id : " << ID_2 << endl;
 	}

	void retransmet3(std::string a)
	//renvoie l'action qui vient dêtre effectuee AUX DEUX clients
	{
        string mess = "3" + a ;
        //envoiMess(mess, ID_1);
        //envoiMess(mess, ID_2);
        cout << "Message T3a : " << mess << endl;
	}

	void envID()
	/* T0c: envoie les 2 ID à la suite 2 fois (une pour chaque destinataire) avec à
                chaque fois l'ID du destinataire en PREMIER ( ATTENTION !! )*/
    {
        string mess_pour_2 = "0" + to_String(ID_2) + ";" + to_String(ID_1);
        string mess_pour_1 = "0" + to_String(ID_1) + ";" + to_String(ID_2);
        //envoiMess(mess_pour_1, ID_1);
        //envoiMess(mess_pour_2, ID_2);
        cout << "Message : " << mess_pour_2 << ", pour joueur d'id : " << ID_2 <<endl;
        cout << "Message : " << mess_pour_1 << ", pour joueur d'id : " << ID_1 <<endl;
    }


	//celle qui n'envoie qu'à la bonne ID
	void envActs(int numeroCouAttendu, std::string a, int ID_dest)
	//T2a
    {
        string mess = "2" + to_String(numeroCouAttendu) + ";" + a;
        //envoiMess(mess, ID_dest);
        cout << "Message T2a : " << mess << ", destinataire id : " << ID_dest << endl;
    }


int main()
{
    /*
    //Test unitaire
    cout << "---- Test unitaire de envEtats(std::string e), message type T4 ---" << endl;
    envEtats("Vivant.Vivant");
    cout << "---- Test unitaire de envDeb(), message type T1d ---" << endl;
    envDeb();
    cout << "---- Test unitaire de envFin(int gagnant), message type T1f ---" << endl;
    envFin(1);
    cout << "---- Test unitaire de envBibli(std::string bib), message type T6 ---" << endl;
    envBibli("bib");
    cout << "---- Test unitaire de retransmet3(std::string a), renvoie l'action qui vient dêtre effectuee AUX DEUX clients ---" << endl;
    retransmet3("coup_tete");
    cout << "---- Test unitaire de envID(), message type T0c ---" << endl;
    envID();
    cout << "---- Test unitaire de envActs(int numeroCoupAttendu,std::string a, int ID_dest), message type T2a---" << endl;
    envActs(65,"morsu",1);
    */
}
