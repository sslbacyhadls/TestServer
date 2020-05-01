#pragma once
#include <WinSock2.h>
#include "ws2def.h"
class SServer {
private:
	WSAData WsData;
	SOCKET LSocket = INVALID_SOCKET;
	SOCKET WSocket;
	sockaddr_in sAddr;
	sockaddr_in cAddr;
	bool openingSession();
	bool localBind(unsigned int, const char[15]);
	
public:
	bool open();
	bool close();
	bool handler();
	unsigned short port;
};