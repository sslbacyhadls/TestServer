#include <iostream>
#include "Client.h"
#include "CConsole.h"
#include "CTextTyping.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    typing("Res/Clogo.txt");
    Console console;
    console.client.cIniciate();
    console.loop();
    system("pause");
}
