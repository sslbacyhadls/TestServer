#include <iostream>
#include "Server.h"
#include "Console.h"
#include "TextTyping.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    typing("Res/Slogo.txt");
    Console console;
    console.loop();
    system("pause");
}

