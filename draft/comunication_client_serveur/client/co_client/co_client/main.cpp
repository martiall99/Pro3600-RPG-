#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

#include <list>


//GESTION du chrono qui demarre les fct ttes les x ms
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

void timer_start(std::function<void(void)> func, unsigned int interval)
{
	std::thread([func, interval]() {
		while (true)
		{
			func();
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
		}
	}).detach();
}


//fonctions generales
string coupeChaine(string &ch, char a)
{
	int p = ch.find(a);
	cout << "init= " + ch + " coupeA= " + a + " length= " + to_string(ch.length()) + " pos= " + to_string(p) << endl;
	if (p == string::npos)
		return "";
	else
	{

		string r = ch.substr(0, p);
		cout << "substr= " + r << endl;
		ch.erase(0, p + 1);
		cout << "coupee= " + ch << endl;
		return r;
	}

}

void debug(string mess, bool stop = false)
{
	if (true)
		cout << mess << endl;
	if (stop)
		system("pause");
}
// classes

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
			timer_start(ecrit);
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
		bool i = remove(name.c_str());
		if (!i)
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
			timer_start(lit);
			return true;
		}
		return false;
	}
private:
	bool delFich(string name, bool aff = false)
	{
		bool i = remove(name.c_str());
		if (!i)
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

	void lit()
	{
		while (continu)
		{
			if (fichExist(lock)) // si le fichier n a pas déjà été lu 
				lireFich();
		}
	}
};


class Serveur
{
	string dir ;
	Ecrire_Fichier St1;
	Ecrire_Fichier St2;
	Lire_Fichier _1tS;
	Lire_Fichier _2tS;

public:
	Serveur()
	{
		dir = "D:/TEST_PRO3600/";
	}
	bool initS()
	{
		debug("demar ST1=>");
		bool a=St1.demarer(dir + "St1.txt");
		if (a=true)
			debug("ok ");
		debug("demar ST2=>");
		a = St2.demarer(dir + "St2.txt");
		if (a = true)
			debug("ok ");
		debug("demar lecture=>",true);
		a = demLecture();
		if (a = true)
			debug("ok ");

		if ((!St1.continu) || (!St2.continu) )
			return false;
		else
			return true;
	}
	bool demLecture()
	{
		_1tS.demarer(dir + "1tS.txt");
		_2tS.demarer(dir + "2tS.txt");
		if ((!_1tS.continu) || (!_2tS.continu))
			return false;
		else
			return true;
	}
	void arret()
	{
		St1.arretUrgence();
		St2.arretUrgence();
		_1tS.arretUrgence();
		_2tS.arretUrgence();
	}	
};
class Client
{
	string dir;
	int id;
	Ecrire_Fichier St1;
	Ecrire_Fichier _1tS;

public:
	Client(int idC)
	{
		dir = "D:/TEST_PRO3600/";
		id = idC;
	}
	bool initC()
	{
		_1tS.demarer(dir + to_string(id)+"tS.txt");
		demLecture();
		if (!_1tS.continu)
			return false;
		else
			return true;
	}
	bool demLecture()
	{		
		St1.demarer(dir + "St" + to_string(id) + ".txt");
		if (!St1.continu)
			return false;
		else
			return true;
	}
	void arret()
	{
		St1.arretUrgence();
		_1tS.arretUrgence();
	}
};
int main()
{
	cout << "hello" << endl;

	Serveur serv;
	serv.initS();
	serv.arret();
	system("pause");
	return 0;
}





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