#pragma once
#include <winsock2.h>
#include "ws2def.h"

#define RBUFFERELEN 512

class Client {
private:
	WSADATA wsaData;
	SOCKET CSocket;
	struct addrinfo* result = NULL, * ptr = NULL;
	struct addrinfo hints;
	const char* sendbuf = "Testing";
	int iResult;
	int rBufferLen = RBUFFERELEN;
	char recvbuf[RBUFFERELEN];
public:
	bool cIniciate();
	bool Cconnect(char* addr, char* port);
	bool sendData(char* data);
};