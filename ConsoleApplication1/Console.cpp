#define _CRT_SECURE_NO_WARNINGS
#define BUFSIZE 1024
#include "Console.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include "Server.h"
#include "TextTyping.h"


//Цикл чтения

void Console::loop(void)
{
	do 
	{
		if (server.isListening) std::cout << "[LISTENING] ";				 //Добавление тега к строке при включённой прослушке сокета
		std::cout << "> ";
		line = read_line();													 //Чтение строки
		args = split_line(line);											 //Чтение строки с аргументами
		launch(args);														 //Выполнение комманды с аргументами

		//std::cout << "line: " << line << std::endl;
		//std::cout << "command:" << launch(args) << std::endl;
		//std::cout << "args: " << *args << std::endl;
		free(line);
		free(args);
	} while (1);
}

//Чтение строки, возвращает массив символов строки

char* Console::read_line(void) 
{
	int position = 0;														//Позиция символа  
	char* buffer = (char*)std::malloc(sizeof(char) * BUFSIZE);				//Выделение памяти под строку
	int c;																	//Временная переменная для символа

	if (!buffer)	
	{
		std::cout << "Memory allocate error: line" << std::endl;							//Проверка выделения памяти
		exit(EXIT_FAILURE);
	}

	while (true)															//Цикл захвата символа
	{
		c = getchar();

		if (c == EOF || c == '\n') {										//Проверка символа. Если не является символом или перенос строки, помечается нулл-символом и 
			buffer[position] = '\0';										//возвращается то, что было написано до этого действия
			return buffer;													//
		}
		else {
			buffer[position] = c;											//По дефолту всё записывается в буффер
		}
		position++;
	}

	if (!buffer) {
		std::cout << "Memory allocated error:line" << std::endl;
	}
}

//Выделение аргументов из строки, возвращает массив аргументов

char** Console::split_line(char* line) 
{
	char a[2] = { 'b', 'g' };
	int position = 0;														//Позиция символа
	char** tokens = (char**)malloc(BUFSIZE * sizeof(char*));				//Выделение памяти под аргументы
	char* token;															//Объявление одного символа аргумента

	if (!tokens) 
	{
		std::cout << "Memory allocate error: args" << std::endl;			//Проверка выделения памяти
		exit(EXIT_FAILURE);
	};

	token = strtok(line, " ");										//Выделение базовой функции без аргументов

	while (token != NULL)													//Цикл выделения аргументов
	{
		tokens[position] = token;											
		position++;
		token = strtok(NULL, " ");									//Выделение аргументов в массив tokens
	}

	if (!tokens) {
		std::cout << "Memory allocate error: args" << std::endl;
	}
	tokens[position] = NULL;												//Сброс позиции после завершения цикла
	return tokens;															//Возвращение массива аргументов
}

bool Console::launch(char** args) {
	std::string command = args[0];					//Помещение первого элемента строки в переменную

	std::string arg1 = "0";                         //
	std::string arg2 = "0";							//Подготовка переменных к аргументам

	if (args[1] != 0) {								//
		arg1 = args[1];								//
		if (args[2] != 0)							//Проверка аргументов на пустоту и присваиваем аргументы переменным
			arg2 = args[2];							//
	}												//



	//Реализация проверки текста с аргументами (очень кривая)

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