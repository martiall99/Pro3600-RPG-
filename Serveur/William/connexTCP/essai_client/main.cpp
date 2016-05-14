#define _WINSOCK_DEPRECATED_NO_WARNINGS // pour utiliser inet_addr
#define _CRT_SECURE_NO_WARNINGS // pour strcpy
#include "client.h"
#include "co_client\debug.h"


using namespace std;
//fais dormir entre @s -1 et @s secondes (pas tres precis)
void WSleepfor(const int &s)
{
	/*
	string a = "timeout " + to_string(s);
	system(a.c_str());
	*/
	std::this_thread::sleep_for(std::chrono::milliseconds(s*1000));

}

void Client_E::ReportError(int errorCode, const  string &whichFunc, bool arret)
{
	string errorMsg;	// Declare a buffer to hold
	// the generated error message
	// The following line copies the phrase, whichFunc string, and integer errorCode into the buffer 
	errorMsg = "---------------------\nCall to " + whichFunc + " returned error " + to_string(errorCode);

	if (arret)
	{
		debug(errorMsg, true);
		apresFinServ();
		exit(NETWORK_ERROR);
	}
	else
		debug(errorMsg);
}

void Client_E::avantLancerServ()
{
	// MAKEWORD(1,1) for Winsock 1.1, MAKEWORD(2,0) for Winsock 2.0:

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
	{
		ReportError(0, "avantLancerServ", true);
	}
}

void Client_E::apresFinServ()
{
	WSACleanup();
}

void Client_E::storeInfoServ(string add_ip, int talkingPort)
{
	iaHost.s_addr = inet_addr(add_ip.c_str());

	debug("--Rech HostEntry");
	hostEntry = gethostbyaddr((const char *)&iaHost, sizeof(struct in_addr), AF_INET);

	debug("--HostEntry trouvé !");


	if (!hostEntry)
	{
		nret = WSAGetLastError();	// Get a more detailed error 
		ReportError(nret, "storeInfoServ() IP: "+add_ip, true);	// Report the error with our custom function 
	}
	serverInfo.sin_family = AF_INET; // At this point, we've successfully retrieved vital information about the server,
									// including its hostname, aliases, and IP addresses. Wait; how could a single 
									// computer have multiple addresses, and exactly what is the following line doing? 
									// See the explanation below. 
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEntry->h_addr_list);
	serverInfo.sin_port = htons(talkingPort);	// Change to network-byte order and
										// insert into port field 
}

void Client_E::createListeningSocket()
{
	listeningSocket = socket(AF_INET,	// Go over TCP/IP
		SOCK_STREAM, // This is a stream-oriented socket 
		IPPROTO_TCP);	// Use TCP rather than UDP 
	if (listeningSocket == INVALID_SOCKET)
	{
		nret = WSAGetLastError();	// Get a more detailed error 
		ReportError(nret, "createListeningSocket()", true);	// Report the error with our custom function 
	}
}

void Client_E::createTalkingSocket()
{
	toTheServer = socket(AF_INET,	// Go over TCP/IP
		SOCK_STREAM, // This is a stream-oriented socket 
		IPPROTO_TCP);	// Use TCP rather than UDP 
	if (toTheServer == INVALID_SOCKET)
	{
		nret = WSAGetLastError();	// Get a more detailed error 
		ReportError(nret, "createTalkingSocket()", true);	// Report the error with our custom function 
	}
}

void Client_E::bindListeningToPort(int port)
{
	clientInfo.sin_family = AF_INET;
	clientInfo.sin_addr.s_addr = INADDR_ANY;	// Since this socket is listening for connections,
	// any local address will do
	clientInfo.sin_port = htons(port);	// Convert integer 8888 to network-byte order 
	// and insert into the port field 

	// Bind the socket to our local server address 
	nret = ::bind(listeningSocket, (LPSOCKADDR)&clientInfo, sizeof(struct sockaddr)); // les ::bind assure que ce soit le bind de winsock et non pas celui de std !
	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		ReportError(nret, "bindToPort()", true);
	}
}

void Client_E::connectTalkToServ()
{
	// Connect to the server
	nret = connect(toTheServer, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr));
	if (nret == SOCKET_ERROR)
	{ 
		nret = WSAGetLastError();
		if (nret == 10061)//le service du serveur n'a pas encore été lancé
		{
			debug("E->En attente de connexion au serveur ...");//on 'narrete pas le client pour ca , c'est juste que le seveur n'a pas envore été lancé probablement
			WSleepfor(2);
			return connectTalkToServ();
		}
		else
			ReportError(nret, "connectTalkToServ()",true);

	}
}

void Client_E::makeListen(int nombre_att)
{
	nret = listen(listeningSocket, nombre_att);// Up to @nombre_att connections may wait at any
	// time to be accept()'ed
	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		ReportError(nret, "makelisten()", true);
	}
}

void Client_E::acceptReceiveFromServer()
{
	fromTheServer = accept(listeningSocket,
		NULL,	// Optionally, address of a SOCKADDR_IN struct
		NULL);	// Optionally, address of variable containing 
	// sizeof ( struct SOCKADDR_IN )
	if (fromTheServer == INVALID_SOCKET)
	{
		nret = WSAGetLastError();
		ReportError(nret, "acceptReceiveFromServer()", true);
	}
}

void Client_E::closeSockets()
{
	closesocket(fromTheServer);
	closesocket(toTheServer);
	closesocket(listeningSocket);
}

void Client_E::closeProperly()
{
	stopSendRcv();

	WSleepfor(1);


	closeSockets();
	// Shutdown Winsock
	apresFinServ();
}

bool Client_E::sendToServ()
{
	if (a_envoyer.size() > 0)
	{
		string data = a_envoyer.front();//on ne le pop() pas au cas ou on ne reussisse pas a envoyer le message



		int taille_buff = data.size() + 2;//+1 pour le carac_fin et au cas ou +1 pour \0 (qu'on pourrait peut etre utilsier directement a la place de carac_fin, mais bon ...)
		char *buffer = new char[taille_buff];	// créé un buffer sur le heap
		ZeroMemory(buffer, taille_buff);
		string reunion = data + charac_fin;
		strcpy(buffer, reunion.c_str());


		nret = send(toTheServer, buffer,
			strlen(buffer),	// Note that this specifies the length of the string; not 
			// the size of the entire buffer 
			0);	// Most often is zero, but see MSDN for other options 
		delete[] buffer;	// If and only if the heap declaration was used 
		if (nret == SOCKET_ERROR)
		{
			// Get a specific code 
			// Handle accordingly 
			return false;
		}
		else
		{
			// nret contains the number of bytes sent 
			debug("voulait envoyer : " + data + "\nbytes send: " + to_string(nret) + ", bytes wanted: " + to_string(taille_buff-1));
			if (nret == taille_buff-1)
			{
				debug("----------------->\nenvoi ok");
				a_envoyer.pop_back();
				return true;
			}
			else
			{
				debug("----------------->\nERREUR: envoi pas ok \nbytes send: " + to_string(nret) + ", bytes wanted: " + to_string(taille_buff - 1), true);
				return false;
			}
		}
	}
	return true;// n'a pas envoyé mais tout est ok
}

void Client_E::receiveFromServ()
{
	char buffer = '\0'; 	// or on the heap
	int bytes_received = -1;
	string r = "";//c'est pas forcement la meilleure idée du monde niveau optimisation de la memoire mais bon ...
	
	while (true)
	{
		bytes_received = recv(fromTheServer,
			&buffer,
			1,	// Complete size to receive
			0);
		if (bytes_received <= 0)
		{
			// Get a specific code 
			// Handle accordingly 
			debug("Erreur dans la reception des donnees arret inexplique apres:" + r);
			serveur_OK = false;
			decoDuServ();
			return;
		}
		else if (buffer == charac_fin)
		{
			transmetClient(r);
			return;
		}
		else
		{
			r.push_back(buffer);
		}
	}
}


void Client_E::lanceConnec()
{
	if (!pret_lancer)//si les paramètres de lancement n'ont pas été remplis
	{
		debug(" ERREUR : les parametres necessaires au lancement du client n'ont pas été remplis avec initialiserClient() ");
		return;
	}	
	//---------------------partie envoi
	storeInfoServ(IP_serv, portSend);
	debug("-->E:storeInfoServ ok");
	connectTalkToServ();// Successfully connected! 
	debug("-->E:connectTalkToServ ok");
}
void Client_E::lanceReception()
{
	if (!pret_lancer)//si les paramètres de lancement n'ont pas été remplis
	{
		debug(" ERREUR : les parametres necessaires au lancement du client n'ont pas été remplis avec initialiserClient() ");
		return;
	}
	//------------------partie reception
	bindListeningToPort(portRecv);
	// Make the socket listen 
	makeListen(nombre_att);
	// Wait for a client 
	debug("-->R:makeListen ok");
	acceptReceiveFromServer();
	debug("-->R:acceptReceiveFromServer ok");
	serveur_OK = true;

}
Client_E::Client_E()
{
	portRecv = -1;//Port ou l'on recoit les donnees
	portSend = -1;//port ou l'on envoie
	IP_serv = "ERREUR: initialiserClient() n'a pas ete lancee";//IP du serveur , utilisée uniquement pour l'envoi
	nombre_att = -1;//nombre att correspond au nombre de personnes a mettre en file d'attente lorsquelles essayent de nous envoyer des mess;
	att_m = 0;//attente entre chaque essai d'envoi/reception de message
	pret_lancer = false;
	continu_lire = false;
	continu_ecrire = false;
	serveur_OK = false;
	charac_fin = ']';

	avantLancerServ();//init	

	/* ---------- Cette Partie ne necessite pas que les infos necessaires aux connexion aient été données*/
	//------------------partie reception
	// create the listening socket 
	createListeningSocket();
	//---------------------partie envoi
	createTalkingSocket();


	// Send/receive next !

}

void Client_E::initialiserClient(int portR, int portS, std::string IP_s, int att, unsigned int attente_boucle)
{
	portRecv = portR;//Port ou l'on recoit les donnees
	portSend = portS;//port ou l'on envoie
	IP_serv = IP_s;//IP du serveur , utilisée uniquement pour l'envoi
	nombre_att = att;//nombre att correspond au nombre de personnes a mettre en file d'attente lorsquelles essayent de nous envoyer des mess;
	att_m = attente_boucle;//attente entre chaque essai d'envoi/reception de message
	pret_lancer = true;
}

Client_E::~Client_E()
{
	closeProperly();
}

void Client_E::lanceTimerLire()
{
	Client_E *moi = this;
	std::thread(
		[moi]() //le pointeur
	{
		if (moi->continu_lire && !moi->serveur_OK)// ceci sera vrai si la conenxion serveur client n'a PAS été établie et si l'on veut bien lire (et pas se deconnecter)
		{
			debug("essai de connexion en lecture , (ou reconnexion) au serveur\n");
			moi->lanceReception();
		}

		while (!moi->serveur_OK)//on attend que la connexion soit etablie
		{
			debug("on attend la conenxion pour Recevior");
			std::this_thread::sleep_for(std::chrono::milliseconds(moi->att_m));
		}

		while (moi->continu_lire && moi->serveur_OK)// ceci sera vrai si la conenxion serveur client a été établie et si l'on veut bien lire (et pas se deconnecter)
		{
			debug("fct recevoir du serveur lancee");
			moi->receiveFromServ();
			std::this_thread::sleep_for(std::chrono::milliseconds(moi->att_m));
		}

	}
	).detach();
}

void Client_E::lanceTimerEcrire()
{
	Client_E *moi = this;
	std::thread(
		[moi]() //le pointeur
	{
		if (moi->continu_ecrire && !moi->serveur_OK)// ceci sera vrai si la conenxion serveur client n'a PAS été établie et si l'on veut bien ecrire (et pas se deconnecter)
		{
			debug("essai de connexion en ecriture , (ou reconnexion) au serveur");
			moi->lanceConnec();
		}
		while (!moi->serveur_OK)//on attend que la connexion soit etablie
		{			std::this_thread::sleep_for(std::chrono::milliseconds(moi->att_m));		}

		while (moi->continu_ecrire && moi->serveur_OK)// ceci sera vrai si la conenxion serveur client a été établie et si l'on veut bien ecrier (et pas se deconnecter)
		{
			//debug("fct envoyer du serveur lancee");
			moi->sendToServ();
			std::this_thread::sleep_for(std::chrono::milliseconds(moi->att_m));
		}

	}
	).detach();
}


void Client_E::stopSend()
{
	continu_ecrire = false;
}
void Client_E::stopRcv()
{
	continu_lire = false;
}
void Client_E::resumeSend()
{
	continu_ecrire = true;
}
void Client_E::resumeRcv()
{
	continu_lire = true;
}
void Client_E::stopSendRcv()
{
	stopSend();
	stopRcv();
}

void Client_E::lanceClient()//appelle lanceTimerLire() puis lanceTimerEcrire();
{
	if (!pret_lancer)//si les paramètres de lancement n'ont pas été remplis
	{
		debug(" ERREUR : les parametres necessaires au lancement du client n'ont pas été remplis avec initialiserClient() ");
		return;
	}

	resumeSend();
	resumeRcv();
	lanceTimerLire();

	//WSleepfor(1);

	lanceTimerEcrire();
}

void Client_E::envoyerAuServeur(std::string mess)
{
	a_envoyer.push_back(mess);
}

void Client_E::transmetClient(std::string recu)
{
	debug("\nmessage recu Serveur-> Client : " + recu);

	// -----------------A compléter ...

}

void Client_E::decoDuServ()
{
	debug("ERREUR: La connexion au serveur a ete perdue, arret de la connexion -->");
	closeProperly();
}



string demander(const string &requete)
{
	debug(requete);
	string r = "";
	cin >> r ;
	return r;
}

int main()
{
	debug("hello world");

	Client_E client;
	string a = demander("1 ou 2");
	if (a == "1")
	{
		client.initialiserClient(29070, 29071);
		client.lanceClient();
		client.envoyerAuServeur("lala 1");
	}
	else if (a == "2")
	{
		client.initialiserClient(29071, 29070);
		client.lanceClient();
		//client.envoyerAuServeur("lala 2");
	}
	else
	{
		debug("Erreur, FIN", true);
		return 0;

	}

	while (!client.serveur_OK)//on attend que la conenxion soit etablie 
	{}
	
	while (client.serveur_OK)//on attend qu'il y ait une deconnexion 
	{ }

	
	debug("Fin", true);
	return 0;
}
