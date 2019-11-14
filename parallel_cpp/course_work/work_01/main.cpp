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


double E_b(Config const  &elem ,std::vector <Config> const &field,double const &min_len){

    double energy = 0;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{

            energy+= pow(i.eps,2)*exp(-2*i.q*(distance(elem.vec, i.vec)/min_len-1));
           // std::cout<<energy<<std::endl;

        }
         
    }
    //std::cout<<"E_b "<<-pow(energy,0.5)<<std::endl;
    return -pow(energy,0.5);
}

double E_r(Config const & elem  ,std::vector <Config> const  &field,double const  &min_len){


    double energy = 0;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{

            energy+= i.A*exp(-1*i.p*(distance(elem.vec, i.vec)/min_len-1));

        }
         
    }
    //std::cout<<"E_r "<<energy<<std::endl;

    return energy;
}


double E_c(std::vector <Config> const &field,double const &min_len){

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


void generate_edge(std::vector<Config>  &Field,const nlohmann::json &file_read, std::string const & path_to){

    std::vector<vector> Pool;
    double a = file_read["a"]; 
    int x_ar =file_read["size"]["x"];
    int y_ar = file_read["size"]["y"];
    int z_ar = file_read["size"]["z"];

    for(auto i: Field){    // OY
        for(int j = 1; j<=y_ar; ++j){
            if(i.vec.y+a*j<=y_ar*a){
            Field.push_back(Config(vector(i.vec.x, i.vec.y+a*j, i.vec.z),
            file_read["A"],
            file_read["eps"],
            file_read["p"],
            file_read["q"]));
            }
            else{
                continue;
            }
        }
    }

    for(auto i: Field){    // OX
        for(int j = 1; j<=x_ar; ++j){
            if(i.vec.x+a*j<=x_ar*a){
            Field.push_back(Config(vector(i.vec.x+a*j, i.vec.y, i.vec.z),
            file_read["A"],
            file_read["eps"],
            file_read["p"],
            file_read["q"]));
            }
            else{
                continue;
            }
        }
    }

    for(auto i: Field){    // OZ
        for(int j = 1; j<=z_ar; ++j){
            if(i.vec.z+a*j<=z_ar*a){
            Field.push_back(Config(vector(i.vec.x, i.vec.y, i.vec.z+a*j),
            file_read["A"],
            file_read["eps"],
            file_read["p"],
            file_read["q"]));
            }
            else{
                continue;
            }
        }
    }


    std::cout<<"Nodes amount: "<<Field.size()<<std::endl<<std::endl;


    //Write to file

    for(auto i : Field){

        std::cout<<"  x:"<<i.vec[0]<<"  y:"<<i.vec[1]<<"  z:"<<i.vec[2]<<std::endl;
        

    }

    std::ofstream fout(path_to,std::ios_base::out);

    fout<<Field.size()<<std::endl<<std::endl;
    for(auto i:Field){
        fout<<"V "<<i.vec[0]<<" "<<i.vec[1]<<" "<<i.vec[2]<<std::endl;
    }
    fout.close();
    






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
    
    double multy = file_read["a"];
    int x_arrow = file_read["size"]["x"]; 
    int y_arrow = file_read["size"]["y"];
    int z_arrow = file_read["size"]["z"];
    
    for(int i = 0;i<file_read["edge"]["n"]; ++i){
        Field.push_back(Config(vector(
            vector(
            multy*double(file_read["edge"][std::to_string(i)]["x"]),//*0.000000001,
            multy*double(file_read["edge"][std::to_string(i)]["y"]),//0.000000001,
            multy*double(file_read["edge"][std::to_string(i)]["z"])//0.000000001
        )),file_read["A"],
        file_read["eps"],
        file_read["p"],
        file_read["q"]));
    }

    
    double Min_len = multy/pow(2.0,0.5);
    std::string  path_to  = "/home/aquafeet/Рабочий стол/edge.xyz";
    generate_edge(Field, file_read,path_to);    // edges are inside Field vector

    std::cout<<"Min len :  "<<Min_len<<std::endl;
    
    nlohmann::json file_write;
    //file_write["G"] = potential(Field);
    std::ofstream o(argv[2]);
    //std::cout<<"check: "<<Field.size()<<std::endl;
    file_write["E_c"] = E_c(Field, Min_len);
    o << file_write; 
    std::cout<<"Data was written to file "<<argv[2]<<std::endl;
    std::cout<<"E_c = "<<E_c(Field,Min_len)/Field.size()<<std::endl;
    
    return 0;
}


//-2.48131








