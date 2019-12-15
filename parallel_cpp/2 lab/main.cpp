#include <iostream>
#include "vector.h"
#include "nlohmann/json.hpp"
#include "fstream"

#include <stdio.h>
#include <stdlib.h>

struct Config{
    vector vec;
    double m;
    Config(vector _vec, double _m):vec(_vec),m(_m){}
};

double potential(std::vector <Config> field){

    const double G = 6.67430e-11;

    double E[field.size()][field.size()];
    for(int i = 0;i < field.size(); ++i){
        for(int j = 0; j < field.size(); ++j){
            E[i][j] = -G*(field[i].m*field[j].m)/distance(field[i].vec,field[j].vec);
        }
    }

    double RezE = 0;
    for(int i = 0;i < field.size(); ++i){
        for(int j = 0; j < field.size(); ++j){
            if(i == j){
                continue;
            }
            else{
                RezE += E[i][j];
            }
        }
    }

    return RezE;

}

int main(int argc, char * argv[]){

	if(argc <2){
        throw std::logic_error("Error, need two params");
        }


    std::vector<Config> Field;

    nlohmann::json file_read;

    //Read file
    std::cin >> file_read;
    
    for(int i = 0;i<3; ++i){
        Field.push_back(Config(vector(
            vector(
            file_read[std::to_string(i)]["x"],
            file_read[std::to_string(i)]["y"],
            file_read[std::to_string(i)]["z"]
        )),file_read[std::to_string(i)]["m"]));

    }
    
    nlohmann::json file_write;
    file_write["G"] = potential(Field);
    //std::cout<< potential(Field)<< std::endl;
    std::ofstream o(argv[1]);
    o << file_write; 
    return 1;
}








