#pragma once
#include <string>
#include "Server.h"

class Console {

public:
	void loop(void);
	char* read_line(void);
	char** split_line(char*);
	bool launch(char**);
	SServer server;
private:
	unsigned short COMMANDS_LENGTH = 3;
	unsigned short COMMANDS_HEIGHT = 4;
	char* line;
	char** args;
	int stat;
	
};