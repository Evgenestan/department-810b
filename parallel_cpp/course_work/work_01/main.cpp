#include <iostream>
#include "vector.h"
#include "nlohmann/json.hpp"
#include "fstream"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Config{
    double m;
    vector vec;
    double a;
    double eps;
    double p;
    double q;
    Config(vector _vec, double _a, double _eps, double _q, double _p) :vec(_vec),a(_a), eps(_eps), q(_q), p(_p) {}

    
};

bool operator == ( const Config & left, const Config & right ){
        if (left.vec == right.vec &&  left.a == right.a && left.eps == right.eps && left.p == right.p && left.q == right.q)
            return true;
        else return false;
    }


double E_b(Config & elem ,std::vector <Config> &field,double &min_len){

    double energy = 0;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{

            energy+= i.eps*exp(-2*i.q*(distance(elem.vec, i.vec)/min_len-1));

        }
         
    }

    return -pow(energy,0.5);
}

double E_r(Config & elem  ,std::vector <Config> &field,double &min_len){


    double energy = 0;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{

            energy+= i.a*exp(-2*i.p*(distance(elem.vec, i.vec)/min_len-1));

        }
         
    }

    return energy,0.5;
}


double E_c(std::vector <Config> &field,double &min_len){

    double Result_energy = 0;
    for(auto i: field){
        Result_energy = E_b(i,field,min_len) + E_r(i,field,min_len);
    }

    return Result_energy;


}

double potential(std::vector <Config> &field){

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

    std::cout<<"Start"<<std::endl;
    std::vector<Config> Field;
    
    nlohmann::json file_read;
   
    //Read file
    //std::cin >> file_read;
    std::ifstream h(argv[1]);
    //std::cout<<argv[1]<<std::endl;

    h>>file_read;
    std::cout<<file_read["n"]<<std::endl;
    for(int i = 0;i<file_read["n"]; ++i){
        Field.push_back(Config(vector(
            vector(
            file_read[std::to_string(i)]["x"],
            file_read[std::to_string(i)]["y"],
            file_read[std::to_string(i)]["z"]
        )),file_read[std::to_string(i)]["a"],2,3,4));
    }


    //max_len find

    double Min_len = LONG_MAX;

    for(int i = 0; i<Field.size();++i){
        for (int j = i+1; j< Field.size();++j){
            double len = distance(Field[i].vec, Field[j].vec);
            if(Min_len>len && i!=j){
                Min_len =len; 
                
                std::cout<<"Find:"<<len<<std::endl;
            }
            else{
                continue;
            }
        }
    }

    std::cout<<"Min len :  "<<Min_len<<std::endl;
    
    nlohmann::json file_write;
    file_write["G"] = potential(Field);
    std::ofstream o(argv[2]);
    o << file_write; 
    std::cout<<"Well done"<<std::endl;
    std::cout<<E_c(Field,Min_len)<<std::endl;
    
    return 0;
}








