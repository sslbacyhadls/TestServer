#pragma once
#include <WinSock2.h>
#include "ws2def.h"
#include <thread>




class SServer {
private:
	WSAData WsData;
	SOCKET LSocket;
	SOCKET WSocket;
//	SOCKET dummySocket;
	sockaddr_in sAddr;
	sockaddr_in cAddr;
	struct addrinfo hints = { 0 }; 
	struct addrinfo* res = NULL;
	bool openingSession();
	bool localBind(const char*, const char[15]);
	std::thread handlerThread;

public:
	SServer();
	bool listenS();
	bool listenStop();
	bool open();
	bool close();
	void handler();
	bool handlerInit();
	unsigned short port;
	bool isListening;
};