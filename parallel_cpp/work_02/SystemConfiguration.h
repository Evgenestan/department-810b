//
// Created by vasil on 10/8/19.
//

#ifndef TASK_02_SYSTEMCONFIGURATION_H
#define TASK_02_SYSTEMCONFIGURATION_H


#include <vector>
#include <ostream>

class SystemConfiguration
{
private:
    int size;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> z;
    std::vector<double> m;
    double potentialEnergy;

    const double G=6.67e-11;

public:
    void readFromFile(const char *);
    void saveToFile(const char *);
    void calculateEnergy();
    void printSystem();
};


#endif //TASK_02_SYSTEMCONFIGURATION_H
