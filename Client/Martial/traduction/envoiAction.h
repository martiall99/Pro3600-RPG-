#ifndef ENVOIACTION_H_INCLUDED
#define ENVOIACTION_H_INCLUDED


//utilisée par client
void envAct( int num_coup, int act);
/*T3 envoie l'action choisie au serveur , avec le num_coup qui a été demandé par le serveur plus tot,
en utilisant l'ID_1 et en convertissant le tout sous forme d'un unique string*/

void decodeTypeMessage(std::string mess);
//envoie vers iTx avec x entre 0 et 6 inclus

// Variables globales
// Transfert tran; bibliothèque bibl; Traduction trad; Client cli;

int ID_1 = 1;

#endif // ENVOIACTION_H_INCLUDED
