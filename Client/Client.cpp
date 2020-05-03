#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Client.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

bool Client::cIniciate(){
    iResult = WSAStartup(MAKEWORD(1, 1), &wsaData);
    if (iResult != 0) {
        std::cout << "[ERROR] Couldnt start test client" << iResult << std::endl;
        return 0;
    }
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        CSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (CSocket == INVALID_SOCKET) {
            std::cout << "[ERROR] Couldnt start socket at client" << iResult << std::endl;
            WSACleanup();
            closesocket(CSocket);
            return 0;
        }
    }
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    return 1;
}

bool Client::Cconnect(char* addr, char* port) {

    // Resolve the server address and port
    iResult = getaddrinfo(addr, port, &hints, &result);
    if (iResult != 0) {
        std::cout << "[ERROR] Couldnt get ip or port" << iResult << std::endl;
        WSACleanup();
    }

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        CSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (CSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(CSocket, (const sockaddr*)ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(CSocket);
            CSocket = INVALID_SOCKET;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

bool Client::sendData(char* data) {

    sendbuf = "data";

    // Send an initial buffer
    iResult = send(CSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR) {
       std::cout << "Send failed with error:" << WSAGetLastError() << std::endl;
        closesocket(CSocket);
        WSACleanup();
        return 0;
    }
    std::cout << "Sended: " << iResult << " bytes" << std::endl;
    return 1;
};