#include <windows.h> 
#include <winsock.h> 


#include <iostream>
#include <string> 
using namespace std;


#define NETWORK_ERROR -1 
#define NETWORK_OK 0 




void ReportError(int, const char *);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmd, int nShow)
{
	WORD sockVersion;
	WSADATA wsaData;
	int nret;
	sockVersion = MAKEWORD(1, 1);	// We'd like Winsock version 1.1 

	// We begin by initializing 	Winsock 
	WSAStartup(sockVersion, &wsaData);

	// Next, create the listening socket
	SOCKET listeningSocket;
	listeningSocket = socket(AF_INET,	// Go over TCP/IP 
		SOCK_STREAM, // This is a stream-oriented socket 
		IPPROTO_TCP);	// Use TCP rather than UDP 
	if (listeningSocket == INVALID_SOCKET)
	{
		nret = WSAGetLastError();	// Get a more detailed error 
		ReportError(nret, "socket()");	// Report the error with our custom function 
		WSACleanup();	// Shutdown Winsock 
		return NETWORK_ERROR;	// Return an error value
	} // Use a SOCKADDR_IN struct to fill in address information 

	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;	// Since this socket is listening for connections, 
	// any local address will do 
	serverInfo.sin_port = htons(8888);	// Convert integer 8888 to network-byte order 
	// and insert into the port field 

	// Bind the socket to our local server address 
	nret = bind(listeningSocket, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr));

	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		ReportError(nret, "bind()");
		WSACleanup();
		return NETWORK_ERROR;
	}

	// Make the socket listen 
	nret = listen(listeningSocket, 10);	// Up to 10 connections may wait at any 
	// one time to be accept()'ed 


	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		ReportError(nret, "listen()");
		WSACleanup();
		return NETWORK_ERROR;
	}

	// Wait for a client 
	SOCKET theClient;
	theClient = accept(listeningSocket, NULL,	// Optionally, address of a SOCKADDR_IN struct 
		NULL);	// Optionally, address of variable containing
	// sizeof ( struct SOCKADDR_IN ) 
	if (theClient == INVALID_SOCKET)
	{
		nret = WSAGetLastError();
		ReportError(nret, "accept()");
		WSACleanup();
		return NETWORK_ERROR;
	}

	// Send and receive from the client, and finally, 

	closesocket(theClient);
	closesocket(listeningSocket);

	// Shutdown Winsock 

	WSACleanup();
	return NETWORK_OK;
}

void ReportError(int errorCode, const string whichFunc)
{
	char errorMsg[92];	// Declare a buffer to hold 
	// the generated error message 
	ZeroMemory(errorMsg, 92); // Automatically NULL-terminate the string 

	cout << "Call to " << whichFunc << " returned error " << to_string(errorCode);

	MessageBox(NULL, errorMsg, "socketIndication", MB_OK);
}