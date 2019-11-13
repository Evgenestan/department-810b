#include <iostream>
#include "vector.h"
#include "nlohmann/json.hpp"
#include "fstream"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Config{

    vector vec;
    double A;
    double eps;
    double p;
    double q;
    Config(vector _vec, double _A, double _eps, double _q, double _p) :vec(_vec),A(_A), eps(_eps), q(_q), p(_p) {}

    
};

bool operator == ( const Config & left, const Config & right ){
        if (left.vec == right.vec &&  left.A == right.A && left.eps == right.eps && left.p == right.p && left.q == right.q)
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

            energy+= i.A*exp(-2*i.p*(distance(elem.vec, i.vec)/min_len-1));

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

/*double potential(std::vector <Config> &field){

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

}*/


void generate_edge(std::vector<Config> &Field,const nlohmann::json &file_read){

     std::vector<vector> Pool;
     double a = file_read["a"]; 
     for(int i = 0; i<file_read["size"]["x"]; ++i){
         for(int j = 0; j<file_read["size"]["y"];++j){
             for(int k = 0; k<file_read["size"]["z"];++k){
                 std::vector<double> temp;
                 Pool.push_back((Field[0].vec*(i+j+k+1)*a));
                 Pool.push_back((Field[1].vec*(i+j+k+1)*a));
                 Pool.push_back((Field[2].vec*(i+j+k+1)*a));
                 Pool.push_back((Field[3].vec*(i+j+k+1)*a));
                // Pool.push_back((Field[1].vec*(k)+Field[1].vec*(j)+Field[1].vec*(i))*a);
                 //Pool.push_back((Field[2].vec*(k)+Field[2].vec*(j)+Field[2].vec*(i))*a);
                 //Pool.push_back((Field[3].vec*(k)+Field[3].vec*(j)+Field[3].vec*(i))*a);

             }
         }
     }

    std::cout<<"len "<<Pool.size()<<std::endl;
    for(auto i : Pool)
        //for(int j = 0; j <3; j++)
    std::cout<<"  x:"<<i[0]<<"  y:"<<i[1]<<"  z:"<<i[2]<<std::endl;


}

int main(int argc, char * argv[]){

	if(argc <2){
        throw std::logic_error("Error, need two params");
        }


    std::vector<Config> Field;
    
    nlohmann::json file_read;
    std::ifstream h(argv[1]);

    std::cout<<"File "<<argv[1]<<" was successfully read."<<std::endl;


    h>>file_read;
    
    int multy = file_read["a"];
    int x_arrow = file_read["size"]["x"]; 
    int y_arrow = file_read["size"]["y"];
    int z_arrow = file_read["size"]["z"];
    
    for(int i = 0;i<file_read["edge"]["n"]; ++i){
        Field.push_back(Config(vector(
            vector(
            file_read["edge"][std::to_string(i)]["x"],
            file_read["edge"][std::to_string(i)]["y"],
            file_read["edge"][std::to_string(i)]["z"]
        )),file_read["A"],
        file_read["eps"],
        file_read["p"],
        file_read["q"]));
    }

    double Min_len = double(multy)/2;

    generate_edge(Field, file_read);    // edges are inside Field vector




    /*for(int i = 0; i<Field.size();++i){
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
    }*/

    std::cout<<"Min len :  "<<Min_len<<std::endl;
    
    nlohmann::json file_write;
    //file_write["G"] = potential(Field);
    std::ofstream o(argv[2]);
    file_write["E_c"] = E_c(Field, Min_len);
    o << file_write; 
    std::cout<<"Data was written to file "<<argv[2]<<std::endl;
    std::cout<<E_c(Field,Min_len)<<std::endl;
    
    return 0;
}








