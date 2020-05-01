#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Server.h"
#include <WinSock2.h>
#include <iostream>




//������ ������
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



//����� ��������� ������
//��������� ����� � �������
// return 0 -- Success
// return 1 -- Fail

bool SServer::localBind(unsigned int port, const char addr[15]) 
{
    
    sAddr.sin_family = AF_INET;                                                             //��� ������ (def = TCP/IP)
  
    sAddr.sin_port = htons(port);                                                           //����

    sAddr.sin_addr.S_un.S_addr = inet_addr(addr);                                           //�����

    LSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);                                    //
    if (LSocket == SOCKET_ERROR) {                                                          // ������� ������
        std::cout << "Socket not inicialised!" << std::endl;                                //
    }
    else  std::cout << "Socket inicialised!" << std::endl;                                                                                      //

    if (bind(LSocket, (struct sockaddr*) & sAddr, sizeof(sAddr) != SOCKET_ERROR)) {         //���������� ������ � ������
        std::cout << "Socket binded!" << std::endl;         
    } else  std::cout << "Socket not binded!" << std::endl;

    if (listen(LSocket, SOMAXCONN) != SOCKET_ERROR) {                                       //��������� ���������
        std::cout << "Socket listening!" << std::endl;
        return 0;
    }
        return 1;
}



//������ ������ � ��������� �����
// return 0 -- Success
// return 1 -- Fail



bool SServer::open() 
{
    openingSession();                                                                      //�������� ������
    localBind(88888, "127.0.0.1");                                                         //���������� ������ � ������       
    handler();
    return 0;
};                                                              



//���� �� ����������

bool SServer::close() 
{

    return 0;
};



//��������� ���������� � ��������

bool SServer::handler() 
{

    int sizeCAddr = sizeof(cAddr);

    while (true) 
    {  
                                                                                            //��������� ���������� � ��������
        if ((WSocket = accept(LSocket, (sockaddr*)&cAddr, &sizeCAddr)) == 1) 
        {
            std::cout << "Client connected" << std::endl;
        }

    }
    return 0;
};


