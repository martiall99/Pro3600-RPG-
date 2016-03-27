Codé pour Windows (testé sous Seven avec visual studio 2015)
1° Inclure dans le projet
2° A modifier pour utiliser

======================================1° Inclure dans le projet
-------------Sous Visual Studio
Headers:
	transf/ClienC.h
	co/chrono.h
	co/Client_E.h
	co/debug.h
	co/Ecr.h
	co/Lire.h
	co/Serveur_E.h


Objets:
	transf/main.cpp
	co/Chrono.cpp
	co/Client_E.cpp
	co/debug.cpp
	co/Ecr.cpp
	co/Lire.cpp
	co/Serveur_E.cpp


------------------Sous code:blocks 
 ( ATTENTION : NON testé, Ceci ne COMPILERA peut etre PAS avec CodeBlocks sous windows avec MINGW )
Inclure dans le projet:
Headers:
	transf/ClienC.h
	co/chrono.h
	co/Client_E.h
	co/debug.h
	co/Ecr.h
	co/Lire.h
	co/Serveur_E.h

	co/toString.h

Objets:
	transf/main.cpp
	co/Chrono.cpp
	co/Client_E.cpp
	co/debug.cpp
	co/Ecr.cpp
	co/Lire.cpp
	co/Serveur_E.cpp

	co/To_stringcpp.cpp

======================================2° A modifier pour utiliser

Dans le transf/main.cpp, fonction main() , modifier la ligne :
	demandeCo(1,"D:/TEST_PRO3600/");
en remplacant par l'endroit ou le client et le serveur echangeront leur messages (sous forme de fichier texte)
Pour l'instant il n'y a QUE le Client (le serveur nous donne encore des erreurs)
ATTENTION, il faut que le dossier en question laisse les DROITS en ECRITURE 
 (click droit sur le dossier /propriété/ decocher lecture seule)