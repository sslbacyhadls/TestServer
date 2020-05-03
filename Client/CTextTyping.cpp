#include <fstream>
#include <string>
#include <iostream>
#include "CTextTyping.h"

std::string getFileContents(std::ifstream& File)
{
    std::string Lines = "";        //All lines

    if (File)                      //Check if everything is good
    {
        while (File.good())
        {
            std::string TempLine;                  //Temp line
            std::getline(File, TempLine);        //Get temp line
            TempLine += "\n";                      //Add newline character

            Lines += TempLine;                     //Add newline
        }
        return Lines;
    }
    else                           //Return error
    {
        return "ERROR File does not exist.";
    }
}

void typing(std::string file) {

    std::ifstream Reader(file);             //Open file

    std::string Art = getFileContents(Reader);       //Get file

    std::cout << Art << std::endl;               //Print it to the screen

    Reader.close();                           //Close file
}