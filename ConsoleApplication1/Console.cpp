#define _CRT_SECURE_NO_WARNINGS
#define BUFSIZE 1024
#include "Console.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include "Server.h"
#include "TextTyping.h"


//���� ������

void Console::loop(void)
{
	do 
	{
		if (server.isListening) std::cout << "[LISTENING] ";				 //���������� ���� � ������ ��� ���������� ��������� ������
		std::cout << "> ";
		line = read_line();													 //������ ������
		args = split_line(line);											 //������ ������ � �����������
		launch(args);														 //���������� �������� � �����������

		//std::cout << "line: " << line << std::endl;
		//std::cout << "command:" << launch(args) << std::endl;
		//std::cout << "args: " << *args << std::endl;
		free(line);
		free(args);
	} while (1);
}

//������ ������, ���������� ������ �������� ������

char* Console::read_line(void) 
{
	int position = 0;														//������� �������  
	char* buffer = (char*)std::malloc(sizeof(char) * BUFSIZE);				//��������� ������ ��� ������
	int c;																	//��������� ���������� ��� �������

	if (!buffer)	
	{
		std::cout << "Memory allocate error: line" << std::endl;							//�������� ��������� ������
		exit(EXIT_FAILURE);
	}

	while (true)															//���� ������� �������
	{
		c = getchar();

		if (c == EOF || c == '\n') {										//�������� �������. ���� �� �������� �������� ��� ������� ������, ���������� ����-�������� � 
			buffer[position] = '\0';										//������������ ��, ��� ���� �������� �� ����� ��������
			return buffer;													//
		}
		else {
			buffer[position] = c;											//�� ������� �� ������������ � ������
		}
		position++;
	}

	if (!buffer) {
		std::cout << "Memory allocated error:line" << std::endl;
	}
}

//��������� ���������� �� ������, ���������� ������ ����������

char** Console::split_line(char* line) 
{
	char a[2] = { 'b', 'g' };
	int position = 0;														//������� �������
	char** tokens = (char**)malloc(BUFSIZE * sizeof(char*));				//��������� ������ ��� ���������
	char* token;															//���������� ������ ������� ���������

	if (!tokens) 
	{
		std::cout << "Memory allocate error: args" << std::endl;			//�������� ��������� ������
		exit(EXIT_FAILURE);
	};

	token = strtok(line, " ");										//��������� ������� ������� ��� ����������

	while (token != NULL)													//���� ��������� ����������
	{
		tokens[position] = token;											
		position++;
		token = strtok(NULL, " ");									//��������� ���������� � ������ tokens
	}

	if (!tokens) {
		std::cout << "Memory allocate error: args" << std::endl;
	}
	tokens[position] = NULL;												//����� ������� ����� ���������� �����
	return tokens;															//����������� ������� ����������
}

bool Console::launch(char** args) {
	std::string command = args[0];					//��������� ������� �������� ������ � ����������

	std::string arg1 = "0";                         //
	std::string arg2 = "0";							//���������� ���������� � ����������

	if (args[1] != 0) {								//
		arg1 = args[1];								//
		if (args[2] != 0)							//�������� ���������� �� ������� � ����������� ��������� ����������
			arg2 = args[2];							//
	}												//



	//���������� �������� ������ � ����������� (����� ������)

	if (command == "Server" || command == "server") {
		if (arg1 == "start") {
			server.open();
			return 1;
		}
		if (arg2 == "stop") {
			server.close();
		}
	}
	else if (command == "exit" || command == "Exit" || command == "Quit")
	{
		exit(1);
	}
	else if (command == "Clear" || command == "cls")
	{
		system("cls");
		return 1;
	}
	else if (command == "Listener" || command == "listener") {
		if (arg1 == "start")
		{
			if (server.listenS())
			{
				server.isListening = 1;
				return 1;
			}
			else
			{
				return 1;
			}
		} 
		if (arg2 == "stop")
		{

		}
	}
	else if (command == "?" || command == "help") {
		typing("man.txt");
	}
}