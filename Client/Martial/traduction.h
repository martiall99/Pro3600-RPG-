#ifndef TRADUCTION_H_INCLUDED
#define TRADUCTION_H_INCLUDED

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

//Variables globales
// Transfert tran; biblioth�que bibl; Traduction trad; Client cli;
int ID_1;
int ID_2;


//Trad
bool partie_debutee;

#endif // TRADUCTION_H_INCLUDED
