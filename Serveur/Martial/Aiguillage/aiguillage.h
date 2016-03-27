#ifndef AIGULLAGE_H_INCLUDED
#define AIGULLAGE_H_INCLUDED
#include <string>
#include <iostream>

//aiguillage

	void iT3a(std::string mess);//remarque ici pas d'iT1, le jeu debute dès que les 2 clients sont connectés

//utilise par transfert

	void decodeMess(std::string mess);// appelle les iTx ici uniquement iT3 donc en soit n'est pas nécessaire mais le sera pour livrable 3

//utilise par m_j
	/* POUR TOUTES CES FONCTIONS D'ENVOI : se référer au LIVRABLE 1 pour avoir la DESCRIPTION de
	l'architecture de chaque type de message*/

	//celles qui envoient aux 2 grâce à deux appels de envoiMess()
	void envEtats(std::string e);//T4
	void envDeb();//T1d
	void envFin(int gagnant);//T1f
	void envBibli(std::string bib);//T6
	void retransmet3(std::string a);//renvoie l'action qui vient dêtre effectuee AUX DEUX clients
	void envID(); // T0c: envoie les 2 ID à la suite 2 fois (une pour chaque destinataire) avec à chaque fois l'ID du destinataire en PREMIER ( ATTENTION !! )

	//celle qui n'envoie qu'à la bonne ID
	void envActs(int numeroCouAttendu,std::string a, int ID_dest); //T2a

//Variables communes
int ID_1 = 1;
int ID_2 = 2;
int id_joueur;
#endif // AIGULLAGE_H_INCLUDED
