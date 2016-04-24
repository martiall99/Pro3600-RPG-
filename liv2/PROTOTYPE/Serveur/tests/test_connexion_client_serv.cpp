#include <iostream>
#include "chrono.h"

#include "Serveur_E.h"
#include "Client_E.h"
#include "debug.h"

using namespace std;





void testEchanges()
{

	Serveur_E s;
	s.initS();
	debug("debut client");
	Client_E c1(1);
	c1.initC();
	Client_E c2(2);
	c2.initC();

	debug("Verif au prochain appui =>", true);

	debug(c1.verif(), "Client1");
	debug(c2.verif(), "Client2");
	debug(s.verif1(), "S =>Client1");
	debug(s.verif2(), "S =>Client2");


	debug("debut Ecriture au prochain appui===>", true);
	c1.envoiS("la");
	c1.envoiS("la2");
	c1.envoiS("la3");
	s.envoi1("lo");
	c2.envoiS("la5");
	s.envoi2("lolo");
	c2.envoiS("la7");

	debug("ARRET au prochain appui=>", true);
	s.arret();
	c1.arret();
	c2.arret();
}


int main()
{
	cout << "hello" << endl;

	testEchanges();


	system("pause");
	return 0;
}














/*
class Ecrire_Fichier
{
private:
list<string> en_attente;
string nom;
string lock;
unsigned int att_ms;
public:
bool continu;//sert a indiquer si fonctionne
public:
Ecrire_Fichier()
{
en_attente = list<string>();
nom = "";
lock = nom + ".nouv";
att_ms = 200;
continu = false;
}
void ajoutAttente(string mess)
{
en_attente.push_back(mess);
}
void arretUrgence()
{
continu = false;
}
~Ecrire_Fichier()
{
continu = false;
delFich(nom);
delFich(lock);
}
bool demarer(string file)
{
nom = file;
debug("creation " + file);
if (creerVide(nom))
{
debug("ok");
continu = true;
//			timer_start(&ecrit);
return true;
}
debug("Nok");
return false;
}
private:
bool creerVide(string name)
{
ofstream monFlux(name.c_str());
if (!monFlux)
{
cout << "ERREUR: Impossible de créer le fichier: " + name << endl;
return false;
}
monFlux.close();
return true;
}
bool delFich(string name, bool aff = false)
{
int i = remove(name.c_str());
if (i !=0)
{
if (aff)
cout << "ERREUR: Impossible de supprimer le fichier: " + name << endl;
return false;
}
return true;

}
bool fichExist(string fich, bool aff = false)
{
ifstream monFlux(fich.c_str());
if (!monFlux)
{
if (aff)
cout << "ERREUR: Impossible d'ouvrir le fichier: " + fich << endl;
return false;
}
monFlux.close();
return true;
}
bool ecritDans(string mess)
{
ofstream monFlux(nom.c_str());
if (!monFlux)
{
cout << "ERREUR: Impossible d'écrire dans le fichier: " + nom << endl;
return false;
}
monFlux << mess << endl;
monFlux.close();

creerVide(lock);//on signale un nouveau message


return true;
}
void ecrit()
{
while (continu)
{
if (en_attente.size() > 0)
{
if (! fichExist(lock)) // si le fichier a déjà été lu
{
ecritDans(en_attente.front());
en_attente.pop_front();
}
}
}
}
void timer_start(std::function<void(void)> func)
{
std::thread(
[&]() //on capture toutes les varaibles
{
while (continu)//je pense que ca ne marchera pas et qu'il ne s'arretera pas pour autnat mais bon ...
{
func();
std::this_thread::sleep_for(std::chrono::milliseconds(att_ms));
}
}
).detach();
}
};
*/
/*
class Lire_Fichier
{
private:
list<string> en_attente;
string nom;
string lock;
int att_ms;
public:
bool continu;//sert a indiquer si fonctionne
public:
Lire_Fichier()
{
en_attente = list<string>();
nom = "";
lock = nom + ".nouv";
att_ms = 200;
continu = false;
}
void arretUrgence()
{
continu = false;
}
~Lire_Fichier()
{
continu = false;
}
bool demarer(string file)
{
nom = file;
if (fichExist(nom))
{
continu = true;
//			timer_start(Lire_Fichier::lit, att_ms);
return true;
}
return false;
}
void lit()
{
while (continu)
{
if (fichExist(lock)) // si le fichier n a pas déjà été lu
lireFich();
}
}
private:
bool delFich(string name, bool aff = false)
{
int i = remove(name.c_str());
if (i != 0)
{
if (aff)
cout << "ERREUR: Impossible de supprimer le fichier: " + name << endl;
return false;
}
return true;

}
bool fichExist(string fich, bool aff = false)
{
ifstream monFlux(fich.c_str());
if (!monFlux)
{
if (aff)
cout << "ERREUR: Impossible d'ouvrir le fichier: " + fich << endl;
return false;
}
monFlux.close();
return true;
}
bool lireFich()
{
if (!fichExist(nom + ".nouv")) // si le fichier a déjà été lu
{
cout << "ERREUR: pas de nouveau message pour: " + nom << endl;
return false;
}

ifstream monFlux(nom.c_str());
if (!monFlux)
{
cout << "ERREUR: Impossible de lire le fichier: " + nom << endl;
return false;
}
string buffer = "";
getline(monFlux,buffer);//normalement le fichier ne doit jamais contenir plus d'une ligne (donc + d'un message)

//DEBUG:
cout << "on lit dans: " + nom + "la ligne: " + buffer << endl;

en_attente.push_back( buffer);//on ajoute au FIFO
monFlux.close();

delFich(lock,true);//on supprime la "notification" de nouveau message pour laisser l'autre envoyer de nouveau

return true;
}

};

*/




/*
bool delFich(string nom, bool aff = false)
{
bool i = remove(nom.c_str());
if (!i)
{
if (aff)
cout << "ERREUR: Impossible de supprimer le fichier: " + nom << endl;
return false;
}
return true;

}
bool fichExist(string nom, bool aff = false)
{
ifstream monFlux(nom.c_str());
if (!monFlux)
{
if (aff)
cout << "ERREUR: Impossible d'ouvrir le fichier: " + nom << endl;
return false;
}
monFlux.close();
return true;
}
*/


















/*

#include <windows.h>;
#include <winsock.h>;



#define NETWORK_ERROR -1

#define NETWORK_OK     0


void ReportError(int, const char *);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmd, int nShow)

{

WORD sockVersion;

WSADATA wsaData;

int nret;



sockVersion = MAKEWORD(1, 1);





// Initialize Winsock as before

WSAStartup(sockVersion, &wsaData);





// Store information about the server

LPHOSTENT hostEntry;



hostEntry = gethostbyname("www.yahoo.com");	// Specifying the server by its name;

// another option: gethostbyaddr()



if (!hostEntry)

{

nret = WSAGetLastError();

ReportError(nret, "gethostbyname()");	// Report the error as before



WSACleanup();

return NETWORK_ERROR;

}





// Create the socket

SOCKET theSocket;



theSocket = socket(AF_INET,			// Go over TCP/IP

SOCK_STREAM,			// This is a stream-oriented socket

IPPROTO_TCP);		// Use TCP rather than UDP



if (theSocket == INVALID_SOCKET)

{

nret = WSAGetLastError();

ReportError(nret, "socket()");



WSACleanup();

return NETWORK_ERROR;

}





// Fill a SOCKADDR_IN struct with address information

SOCKADDR_IN serverInfo;



serverInfo.sin_family = AF_INET;



// At this point, we've successfully retrieved vital information about the server,

// including its hostname, aliases, and IP addresses.  Wait; how could a single

// computer have multiple addresses, and exactly what is the following line doing?

// See the explanation below.



serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);



serverInfo.sin_port = htons(80);		// Change to network-byte order and

// insert into port field





// Connect to the server

nret = connect(theSocket,

(LPSOCKADDR)&serverInfo,

sizeof(struct sockaddr));



if (nret == SOCKET_ERROR)

{

nret = WSAGetLastError();

ReportError(nret, "connect()");



WSACleanup();

return NETWORK_ERROR;

}





// Successfully connected!





// Send/receive, then cleanup:

closesocket(theSocket);

WSACleanup();

}





void ReportError(int errorCode, const string whichFunc)
{
char errorMsg[92];	// Declare a buffer to hold
// the generated error message
ZeroMemory(errorMsg, 92); // Automatically NULL-terminate the string

cout << "Call to " << whichFunc << " returned error " << to_string(errorCode);

MessageBox(NULL, errorMsg, "socketIndication", MB_OK);
}

*/