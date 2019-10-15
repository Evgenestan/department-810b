//
// Created by vasil on 10/8/19.
//

#include "SystemConfiguration.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "vector.cpp"


std::vector<std::string> parseBySpace(const std::string & inputString)
{
    std::vector<std::string> parsedString;

    std::stringstream stringStream{};
    stringStream << inputString;

    std::string buffer;

    while (stringStream >> buffer)
    {
        parsedString.push_back(std::move(buffer));
    }

    return parsedString;
}

void SystemConfiguration::readFromFile(const char * fileName)
{
    std::ifstream inputFile(fileName);

    if(inputFile.is_open())
    {
        std::string buffer;
        std::getline(inputFile,buffer);

        this->size = std::atoi(buffer.c_str());

        while (std::getline(inputFile, buffer))
        {
            std::vector<std::string> data = parseBySpace(buffer);

            this->x.push_back(std::stod(data[0]));
            this->y.push_back(std::stod(data[1]));
            this->z.push_back(std::stod(data[2]));

            this->m.push_back(std::stod(data[3]));
        }

        inputFile.close();
    }
}

void SystemConfiguration::calculateEnergy()
{
    double enegry = 0;

    for (int i = 0; i < this -> size; ++i)
    {
        for (int j = 0; j < this -> size; ++j)
        {
            if(i!=j)
            {
                vector iVector(x[i],y[i],z[i]);
                vector jVector(x[j],y[j],z[j]);

                double r_ij = distance(iVector,jVector);

                enegry+= -G * (m[i] * m[j]) / r_ij;
            }
        }
    }

    this -> potentialEnergy = enegry;
}

void SystemConfiguration::saveToFile(const char * fileName)
{
    std::ofstream outputFile(fileName);

    if(outputFile.is_open())
    {
        outputFile << "E = " << this -> potentialEnergy;

        outputFile.close();
    }

}


void SystemConfiguration::printSystem()
{
    for (int i = 0; i < this->size; ++i)
    {
        std::cout << x[i] << " ";
        std::cout << y[i] << " ";
        std::cout << z[i] << " ";
        std::cout << m[i] << " \n";
    }
}