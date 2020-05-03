#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Server.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <thread>

//ВСЕ BOOL ФУНКЦИИ
// return 1 -- Success
// return 0 -- Fail



SServer::SServer() {
    system("color FC");
}

//Создаёт сессию и открывает сокет



bool SServer::open()
{
    
    std::cout << "Starting server..." << std::endl;
    if (openingSession() == 1 &&                                                                      //Открытие сессии
        localBind("50000", "127.0.0.1") == 1)                                                           //Связывание сокета и адреса
    {
        std::cout << "[SUCCESS] Server opened!" << std::endl;
        std::cout << "Waiting for client to connect..." << std::endl;
        handler();
        return 1;
    }
    else
        std::cout << "[ERROR] with opening server" << std::endl;
    return 0;

};



//Создаёт сессию

bool SServer::openingSession() {
    if (FAILED(WSAStartup(MAKEWORD(1, 1), &WsData))) {
        std::cout << "Error with WS opening!" << std::endl;
        return 0;
    }
    else {
        std::cout << "[SUCCESS] Succesfully opened WS" << std::endl;
        return 1;
    };
};



//Задаёт параметры адреса
//Связывает адрес с сокетом


bool SServer::localBind(const char* port, const char addr[15]) 
{
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    
    int status;


    if (status = getaddrinfo(NULL, port, &hints, &res) != 0)
    {
        std::cout << "[ERROR]: " << WSAGetLastError() << "Get Address Info failed.\n";
    };

    if (status != 0)
    {
        std::cout << "[ERROR]: " << status << " Unable to get address info for Port " << port << "." << std::endl;
        return false;
    }

    LSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);                   //
    if (LSocket == INVALID_SOCKET) {                                                        // Задание сокета
        std::cout << "Socket not inicialised!" << std::endl;                                //
    }                                                                                       //
    else
    {
        std::cout << "[SUCCESS] Socket inicialised!" << std::endl;                          //
    }

    std::cout << "Address" << res->ai_addr->sa_data << std::endl;

    iResult = bind(LSocket, res->ai_addr, (int)res->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("[ERROR] Could not bind socket: ", WSAGetLastError());
        freeaddrinfo(res);
        closesocket(LSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(res);

    listenS();
}

//Функция прослушнки сокета

bool SServer::listenS() {
    if (listen(LSocket, 5) != SOCKET_ERROR)
    {
        isListening = 1;
        std::cout << "[SUCCESS] Socket listening!" << std::endl;                                     //Включение слушателя
        WSocket = LSocket;
        return 1;
    }
    else {
        std::cout << "[ERROR] Listen: " << WSAGetLastError() << std::endl;
        closesocket(LSocket);
        return 0;
    }
}

//Закрываем все сокеты и подключения

bool SServer::close() 
{
    if (WSocket != INVALID_SOCKET && LSocket != INVALID_SOCKET) {
        closesocket(LSocket);
        closesocket(WSocket);
        isListening = 0;
        std::cout << "[SUCCESS] Server stoped" << std::endl;
        return 1;
    }   else 
    {
        std::cout << "[ERROR] Server doesn't stopped" << std::endl << "[INFO] Problem with sockets" << std::endl;
        return 0;
    }

};

//Установка соединения с клиентом

void SServer::handler() 
{
    int sizeCAddr = sizeof(cAddr);
                                                                                   //Установка соединения с клиентом
    if ((WSocket = accept(LSocket, (sockaddr*)&cAddr, &sizeCAddr)) != INVALID_SOCKET)
    {
            std::cout << "Client connected" << std::endl;
    }
};