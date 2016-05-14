#include <winsock2.h> 
#include <Ws2tcpip.h>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
#include <vector>


#define NETWORK_ERROR -1 
#define NETWORK_OK 0


// A peu pres tout ce code est une traduction en objet (et en c++ par endroits ), avec quelques ajouts du Johny Winsock Tutorial http://johnnie.jerrata.com/winsocktutorial/#creatingalisteningsocket

class Client_E
{
private:
	//----------Partie Winsock
	WORD sockVersion; // version of winsock used
	WSADATA wsaData;//sert a linit de winsock
	SOCKET listeningSocket;//le socket du port a ecouter, on sera oblig� de rajotuer par dessus un socket fromTheServer
	LPHOSTENT hostEntry;//les infos sur le serveur
	SOCKADDR_IN clientInfo; //info sur nous 
	SOCKADDR_IN serverInfo; //info sur le serv 
	SOCKET fromTheServer;// celui qui recoit du serveur
	SOCKET toTheServer;// celui qui lui parle
	int nret;//code de retour des erreurs, est envoy� a ReportError
	in_addr iaHost;//ce qui stockera l'ip du serveur

	//-----------Partie Gestion
	int portRecv = 8888 ;//Port ou l'on recoit les donnees
	int portSend = 80;//port ou l'on envoie
	std::string IP_serv = "127.0.0.1";//IP du serveur , utilis�e uniquement pour l'envoi
	int nombre_att = 10;//nombre att correspond au nombre de personnes a mettre en file d'attente lorsquelles essayent de nous envoyer des mess;
	unsigned int att_m;//attente entre chaque essai d'envoi/reception de message
	bool pret_lancer;//indique si tous les param�tres du client ont bien �t� donn�s grace a la fonction  initialiserClient()
	char charac_fin = ']';// @charac_fin sera la chaine utilis�e en fin de message pour dire que le message est fini (le recepteur ne connait pas a priori la taille du message)
	std::vector<std::string> a_envoyer;// @a_envoyer est un vecteur qui stocke les chaines de message en attente d'�tre envoy�es !


public: //besoin pour le traitement de la boucle qui verifie periodiquemetn
	bool continu_lire;//pour ce qui lance le flux de lecture dans un autre thread puis verifie p�riodiquement la pr�sence de messages
	bool continu_ecrire;//m�me chose pour l'�criture
	bool serveur_OK;//dis si le serveur s'est d�connect� ou pas

private:
	void ReportError(int errorCode, const  std::string &whichFunc, bool arret = false);
	//toutes les fonctions suivantes sont list�es dans leur ordre d'execution normal
	// Initialisation
	void avantLancerServ();
	//Partie reception :
	void createListeningSocket();
	void bindListeningToPort(int port);
	void makeListen(int nombre_att);
	void acceptReceiveFromServer();
	//partie envoi :
	void storeInfoServ(std::string add_ip, int talkingPort);// ATTENTIOn l'ip doit etre en ipv4
	void createTalkingSocket();
	void connectTalkToServ();
	//Fin
	void closeSockets();
	void apresFinServ();
	void lanceTimerLire();
	void lanceTimerEcrire();
	void transmetClient(std::string recu);//cette fonction est inutile, elle permet juste de s�parer tout le traitement de la r�ception, du traitement du message en lui m�me, elle est appel�e par receiveFromServ()

	

	void decoDuServ();//est appel�e lorsqu'il y a une deco de l'autre cot� !
public:


	Client_E();
	void initialiserClient(int portR = 8888, int portS = 80, std::string IP_s = "127.0.0.1", int att = 10, unsigned int attente_boucle = 500);//celle qui rentre tous les param�tres, elle doit �tre lancee AVANT tout essai de connexion
	void closeProperly();//est appelee automatiquement a la destruction, mais si on veut arreter nous m�me ...

	void envoyerAuServeur(std::string mess);//Cette fonction peut �tre utilis�e m�me si le serveur n'a pas �t� initialis� ! , elle remplie @a_envoyer

	void stopSendRcv();// lance stopSend()  et stopRcv()
	void stopSend();//arrete les envois de messages en mettant @continu_ecrire a false
	void stopRcv();//arrete les receptions de messages en mettant @continu_lire a  false (un dernier message sera lu en g�n�ral)
	void resumeSend();// recommence les envois de messages en mettant @continu_ecrire a true
	void resumeRcv();//recommence les receptions de messages en mettant @continu_lire a  true

	void lanceClient();//appelle lanceTimerLire() puis lanceTimerEcrire();




	//--------------------------A ne pas utiliser, elles sont necessairement publiques (ou il faudrait faire une amitie ...) mais elles sont lanc�es automatiquement !
	~Client_E();	
	void lanceConnec();//lance la conenxion au serveur cote ecriture (client-> serveur)      ---------- utilise les  @portSend ,@IP_serv
	void lanceReception();//lance la conenxion au serveur cote lecture  (serveur-> client)  ----------utilise les@portRecv, @nombre_att
	//Envoi et reception:
	bool sendToServ();// envoie les message dans @a_envoyer s'il y en a
	void receiveFromServ();// recoit les message et appelle transmetClient() si il recoit quelquechose
};