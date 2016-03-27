#ifndef AIGULLAGE_H_INCLUDED
#define AIGULLAGE_H_INCLUDED
#include <string>
#include <iostream>

//aiguillage

	void iT3a(std::string mess);//remarque ici pas d'iT1, le jeu debute d�s que les 2 clients sont connect�s

//utilise par transfert

	void decodeMess(std::string mess);// appelle les iTx ici uniquement iT3 donc en soit n'est pas n�cessaire mais le sera pour livrable 3

//utilise par m_j
	/* POUR TOUTES CES FONCTIONS D'ENVOI : se r�f�rer au LIVRABLE 1 pour avoir la DESCRIPTION de
	l'architecture de chaque type de message*/

	//celles qui envoient aux 2 gr�ce � deux appels de envoiMess()
	void envEtats(std::string e);//T4
	void envDeb();//T1d
	void envFin(int gagnant);//T1f
	void envBibli(std::string bib);//T6
	void retransmet3(std::string a);//renvoie l'action qui vient d�tre effectuee AUX DEUX clients
	void envID(); // T0c: envoie les 2 ID � la suite 2 fois (une pour chaque destinataire) avec � chaque fois l'ID du destinataire en PREMIER ( ATTENTION !! )

	//celle qui n'envoie qu'� la bonne ID
	void envActs(int numeroCouAttendu,std::string a, int ID_dest); //T2a

//Variables communes
int ID_1 = 1;
int ID_2 = 2;
int id_joueur;
#endif // AIGULLAGE_H_INCLUDED
