#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Server.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

SServer::SServer() {
    system("color FC");
}

//Создаёт сессию и открывает сокет
// return 1 -- Success
// return 0 -- Fail


bool SServer::open()
{
    std::cout << "Starting server..." << std::endl;
    if (openingSession() == 1 &&                                                                      //Открытие сессии
        localBind("50000", "127.0.0.1") == 1)                                                           //Связывание сокета и адреса
    {
        handlerInit();
        std::cout << "[SUCCESS] Server opened!" << std::endl;
        return 1;
    }
    else
        std::cout << "[ERROR] with opening server" << std::endl;
    return 0;

};



//Создаёт сессию
// return 1 -- Success
// return 0 -- Fail

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
// return 1 -- Success
// return 0 -- Fail

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
        std::cout << "[SUCCESS] Socket inicialised!" << std::endl;                                  //
    }


    if (bind(LSocket, res->ai_addr, res->ai_addrlen != SOCKET_ERROR)) {         //Связывание сокета и адреса
        std::cout << "[SUCCESS] Socket binded!" << std::endl;         
    } else  std::cout << "Socket not binded!" << std::endl;

    freeaddrinfo(res);


}


bool SServer::listenS() {
    if (listen(LSocket, 5) != SOCKET_ERROR)
    {
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

bool SServer::listenStop() {
    listen(LSocket, 0);
    return 1;
}


//Закрываем все сокеты и подключения

bool SServer::close() 
{
    if (isListening != 1) {
        if (WSocket != INVALID_SOCKET)
        {
            std::cout << "Closing server...";
            closesocket(WSocket);
        }
        if (LSocket != INVALID_SOCKET)
        {
            closesocket(LSocket);
        }
        return 1;
    }
    else
    {
        std::cout << "[ERROR] Socket is listening";
        return 0;
    };
};

//Установка соединения с клиентом

void SServer::handler() 
{
    int sizeCAddr = sizeof(cAddr);

    while (true) 
    {  
                                                                                            //Установка соединения с клиентом
        if ((WSocket = accept(LSocket, (sockaddr*)&cAddr, &sizeCAddr)) == 1) 
        {
            std::cout << "Client connected" << std::endl;
        }

    }
};

//Инициализация потока соединения с клиентом

bool SServer::handlerInit()
{
    handlerThread = std::thread(&SServer::handler, this);
    std::cout << "Handler thread created" << std::endl << "Thread ID: " << handlerThread.get_id() << std::endl;
    return 1;
}