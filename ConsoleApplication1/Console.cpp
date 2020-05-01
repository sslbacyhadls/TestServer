#define _CRT_SECURE_NO_WARNINGS
#define BUFSIZE 1024
#include "Console.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include "Server.h"


//Цикл чтения

void Console::loop(void)
{
	do 
	{
		std::cout << "> ";
		line = read_line();													 //Чтение строки
		args = split_line(line);											 //Чтение строки с аргументами
		launch(args);														 //Выполнение комманды с аргументами

		std::cout << "line: " << line << std::endl;
		std::cout << "command:" << launch(args) << std::endl;
		std::cout << "args: " << *args << std::endl;
		free(line);
		free(args);
	} while (stat);
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
	char* command = args[1];
	if (command == "ServerStart")
		std::cout << "Starting server..." << std::endl;
		server.open();
	return 1;
}