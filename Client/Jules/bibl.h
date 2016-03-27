#ifndef BIBL_H
#define BIBL_H

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

std::string coupeChaine(std::string &ch, char a);
// Cont_action rechAction(int id);// rechLigne() puis renvoie un cont_action contenant le contenu de la ligne, si aucune correspondance renvoie des champs vides ""
void mAJ(std::string MAJ);// sépare à ' / ' et appelle 	interpreterLigne() sur chaque, en remplacant au préalable le buffer_type avec le bon mot ( dans l'ordre : attaques, magie, objets, buffs) //séparateur: '  /  '  entre chaque action possible   et ' . ' entre chaque type d'actions ( dans l'ordre : attaques, magie, objets)
void testBibl();

std::vector <int> tab_id;
std::vector <std::string> tab_type;
std::vector <std::string> tab_titre;
std::vector <std::string> tab_descr;

int buffer_int;
std::string buffer_type;
std::string buffer_titre;
std::string buffer_descr;

void ajLigne();//créer la ligne dont les caractéristiques sont dans les buffers
void modifLigne(int noLigne);// remplace la ligne a modifier (dont les nouvelles caractéristiques sont dans les buffers)
int rechLigne();// renvoie le NUMERO de la LIGNE ( ATTENTION != ID du sort) dont l'ID est stockée dans buffer( ATTENTION il est en général différent de l'ID de l'action), renvoie -1 si l'id n'est pas stockée
void interpreterLigne(std::string Ligne); // sépare chaque champ, remplit chaque buffer, appelle rechLigne(), si il y a une correspondance appelle modifLigne(), sinon ajLigne() //séparateur: '  ;  '  entre chaque "composante" (ID, titre, description) d'une action possible

#endif // BIBL_H
