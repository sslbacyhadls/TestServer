#define _CRT_SECURE_NO_WARNINGS
#define BUFSIZE 1024
#include "Console.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include "Server.h"


//���� ������

void Console::loop(void)
{
	do 
	{
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

	if (args[0] == 0)
		return 1;

	std::string command = args[0];


	if (command == "ServerStart") {
		std::cout << "Starting server..." << std::endl;
		server.open();
		return 1;
	}
	else if (command == "exit" || command == "Exit" || command == "Quit")
	{
		exit(1);
	}
	else if (command == "pass" || command == "Pass")
	{
		return 1;
	}
	else if (command == "Clear" || command == "cls")
	{
		system("cls");
	}
}