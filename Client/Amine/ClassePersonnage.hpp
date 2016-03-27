//
//  ClassePersonnage.hpp
//  projet3600
//
//  Created by Amine Tekni on 27/03/2016.
//  Copyright © 2016 Amine Tekni. All rights reserved.
//

//#ifndef ClassePersonnage_hpp
#define ClassePersonnage_hpp
#include <iostream>
#include <stdio.h>
#include <string>

class Personnage
{
public:
    
    Personnage(); //Constructeur
    void recevoirDegats(int nbDegats);
    void attaquer(Personnage &cible);
    void boirePotionDeVie(int quantitePotion);
    void changerArme(std::string nomNouvelleArme, int degatsNouvelleArme);
    bool estVivant();
    
    
private:
    
    int m_vie;
    int m_mana;
    std::string m_nomArme;
    int m_degatsArme;
};
