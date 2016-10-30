/*
	Planar Tech 1 Networking Library
*/

#include "pt_main.h"
#include "pt_net.h"
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

//Strucure to keep all necessary data in one place
struct PTSocket {
	char* name;
	addrinfo* result;
	addrinfo* ptr;
	addrinfo hints;
	SOCKET socket;
	void (*hook)(char*);

	PTSocket()
	{
		name = "\0";
		result = NULL;
		ptr = NULL;
		hints = addrinfo();
		ZeroMemory( &hints, sizeof(hints) );
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		socket = INVALID_SOCKET;
		hook = nullptr;
	}
};

PTSocket* ptsockets[MAX_CONNECTIONS+1];

unsigned int defsocket = 1; 

//Initializes WinSock 2
void InitNetworkLib() {
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2,2), &wsaData);
	if(result != 0)
		printf("WinSock Init Failure: %i\n",result);
}

//Begins reading the input buffer and proxying data to the socket's attached hook method
void MonitorSocket(void* arg){
	int socket = (int)arg;
	int bufferlen = 1024;
	char* buffer = (char*)malloc(bufferlen);

	int err = 1;
	while(err > 0){
		ZeroMemory(buffer,bufferlen);
		err = recv(ptsockets[socket]->socket,buffer,bufferlen,0);
		if(ptsockets[socket]->hook != nullptr){
			(ptsockets[socket]->hook)(buffer);
		}
	}
	printf("connection closing");
}

//Creates a new socket and returns the index.
unsigned int CreateSocket(char* name){
	unsigned int index = GetSocket(name);
	if(index > 0)
		return index;
	for(unsigned int i = 1; i < MAX_CONNECTIONS+1; i++)
		if(ptsockets[i] == nullptr){
				index = i;
				break;
			}
	PTSocket* pts = new PTSocket();
	pts->name = name;
	ptsockets[index] = pts;
	return index;
}
//returns socket with specified name
unsigned int GetSocket(char* name){
	for(unsigned int i = 1; i < MAX_CONNECTIONS+1; i++)
		if(ptsockets[i] != nullptr)
			if(ptsockets[i]->name == name)
				return i;
	return 0;
}
//connects the socket to the designated ip on the port 'port'
bool ConnectSocket(unsigned int sock, char* ip, char* port){
	PTSocket* pts = ptsockets[sock];

	int iresult = getaddrinfo(ip,port,&pts->hints,&pts->result);
	if(iresult != 0) {
		printf("GetAddrInfo Failure: %i\n",pts->result);
		WSACleanup();
		return false;
	}

	pts->ptr = pts->result;
	pts->socket = socket(pts->ptr->ai_family, pts->ptr->ai_socktype, pts->ptr->ai_protocol);
	if(pts->socket == INVALID_SOCKET){
		printf("Socket Connection Error: %s\n", WSAGetLastError);
		freeaddrinfo(pts->result);
		WSACleanup();
		return false;
	}

	iresult = connect( pts->socket, pts->ptr->ai_addr, (int)pts->ptr->ai_addrlen);
	freeaddrinfo(pts->result);
	if(iresult == SOCKET_ERROR){
		closesocket(pts->socket);
		pts->socket = INVALID_SOCKET;
		printf("Failed to Connect");
		return false;
	}

	_beginthread(MonitorSocket, 0, (void*)sock);

	return true;
}

//Returns the socket set by SetDefSocket
//Intended to be used for the main socket so you don't lose the index
//You can pass 0 as a parameter for any socket index and it will use the default
unsigned int GetDefSocket(){
	return defsocket;
}
//Sets the default socket
void SetDefSocket(unsigned int sock){
	defsocket = sock;
}

//Sends the data through the socket with specifiable length
void SendData(unsigned int sock, char* data, int len){
	send(ptsockets[sock]->socket,data,len,0);
}
void SendData(unsigned int sock, char* data){
	SendData(sock,data,sizeof data);
}

//Hooks a method to a socket so any data sent to it will be proxied to that method
void Net_HookRecFunc(unsigned int sock, void(*hook)(char*)){
	ptsockets[sock]->hook = hook;
}