#include "bibl.h"

using namespace std;

int main()
{
    string nouvelleLigne = "1;charge;inflige des degats normaux/2;lechouille;speciale martiale : fait fuir l'adversaire.3;flammeche;petites flammes/4;saut jusquau ciel;yolo tmtc.5;ceci est un objet; objet objet";
    mAJ(nouvelleLigne);
    testBibl();
    return 0;
}
