#pragma once
#include <string>
#include "Client.h"
#include <thread>

class Console {
public:
	void loop(void);
	char* read_line(void);
	char** split_line(char*);
	bool launch(char**);
	Client client;
private:
	unsigned short COMMANDS_LENGTH = 3;
	unsigned short COMMANDS_HEIGHT = 4;
	char* line;
	char** args;
	int stat;
};