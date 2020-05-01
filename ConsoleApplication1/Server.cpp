#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Server.h"
#include <WinSock2.h>
#include <iostream>




//Создаёт сессию
// return 0 -- Success
// return 1 -- Fail

bool SServer::openingSession() {
    if (FAILED(WSAStartup(MAKEWORD(1, 1), &WsData))) {
        std::cout << "Error with WS opening!" << std::endl;
        return 1;
    }
    else {
        std::cout << "Succesfully opened WS" << std::endl;
        std::cout << WsData.iMaxSockets << std::endl;
        return 0;
    };
};



//Задаёт параметры адреса
//Связывает адрес с сокетом
// return 0 -- Success
// return 1 -- Fail

bool SServer::localBind(unsigned int port, const char addr[15]) 
{
    
    sAddr.sin_family = AF_INET;                                                             //Тип адреса (def = TCP/IP)
  
    sAddr.sin_port = htons(port);                                                           //Порт

    sAddr.sin_addr.S_un.S_addr = inet_addr(addr);                                           //Адрес

    LSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);                                    //
    if (LSocket == SOCKET_ERROR) {                                                          // Задание сокета
        std::cout << "Socket not inicialised!" << std::endl;                                //
    }
    else  std::cout << "Socket inicialised!" << std::endl;                                                                                      //

    if (bind(LSocket, (struct sockaddr*) & sAddr, sizeof(sAddr) != SOCKET_ERROR)) {         //Связывание сокета и адреса
        std::cout << "Socket binded!" << std::endl;         
    } else  std::cout << "Socket not binded!" << std::endl;

    if (listen(LSocket, SOMAXCONN) != SOCKET_ERROR) {                                       //Включение слушателя
        std::cout << "Socket listening!" << std::endl;
        return 0;
    }
        return 1;
}



//Создаёт сессию и открывает сокет
// return 0 -- Success
// return 1 -- Fail



bool SServer::open() 
{
    openingSession();                                                                      //Открытие сессии
    localBind(88888, "127.0.0.1");                                                         //Связывание сокета и адреса       
    handler();
    return 0;
};                                                              



//Пока не реализован

bool SServer::close() 
{

    return 0;
};



//Установка соединения с клиентом

bool SServer::handler() 
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
    return 0;
};


