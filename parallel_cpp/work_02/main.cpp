#define CMD_ARG_ERROR 1

#include <iostream>
#include "SystemConfiguration.h"

int main(int argc,char * argv[])
{
    if(argc < 2)
    {
        std::cerr<< "Не хватает аргументов командной строки\n";
        return CMD_ARG_ERROR;
    }

    SystemConfiguration systemConfiguration;

    systemConfiguration.readFromFile(argv[1]);
    systemConfiguration.printSystem();
    systemConfiguration.calculateEnergy();
    systemConfiguration.saveToFile(argv[2]);




    return 0;
}