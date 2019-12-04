#include <iostream>
#include "vector.h"
#include "nlohmann/json.hpp"
#include "fstream"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <tbb/parallel_for.h>


struct Config{

    vector vec;
    double A;
    double eps;
    double p;
    double q;
    Config(vector _vec, double _A, double _eps, double _q, double _p) :vec(_vec),A(_A), eps(_eps), q(_q), p(_p) {}

    
};


double distance(const vector& lv,const vector& rv, const double & length, const double * matrix){
    //double cur_len = sqrt(pow(lv.x-rv.x,2)+pow(lv.y-rv.y,2)+pow(lv.z-rv.z,2));
    double x_r, y_r,z_r;
    double x_dif = lv.x-rv.x;
    double y_dif = lv.y - rv.y;
    double z_dif = lv.z - rv.z; 
    if(x_dif>length/2){
        x_r =  (x_dif)-length;
    }
    else if(x_dif<-length/2){
        x_r = length+x_dif;
    }
    else{
        x_r = x_dif;
    }

    if(y_dif>length/2){
        y_r =  (y_dif)-length;
    }
    else if(y_dif<-length/2){
        y_r = length+y_dif;
    }
    else{
        y_r = y_dif;
    }

    if(z_dif>length/2){
        z_r =  (z_dif) - length ;
    }
    else if(z_dif<-length/2){
        z_r = length+z_dif;
    }
    else{
        z_r = z_dif;
    }
    
    return sqrt(x_r*x_r*matrix[0]*matrix[0]+y_r*y_r*matrix[1]*matrix[1]+z_r*z_r*matrix[2]*matrix[2]);
    
}


bool operator == ( const Config & left, const Config & right ){
        return  (left.vec == right.vec &&  left.A == right.A && left.eps == right.eps && left.p == right.p && left.q == right.q);

    }


double E_b(
    Config const  &elem,
    std::vector <Config> const &field,
    double const &min_len,
    const double & multy,
    const double* matrix){

    double energy = 0;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{

            energy+= pow(i.eps,2)*exp(-2*i.q*(distance( i.vec,elem.vec, multy, matrix)/min_len-1));
           // std::cout<<energy<<std::endl;

        }
         
    }
    //std::cout<<"E_b "<<-pow(energy,0.5)<<std::endl;
    return -pow(energy,0.5);
}

double E_r(
    Config const & elem,
    std::vector <Config> const  &field,
    double const  &min_len,
    const double& multy,
    const double * matrix){

    double energy = 0;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{

            energy+= i.A*exp(-1*i.p*(distance(i.vec, elem.vec,  multy, matrix)/min_len-1));

        }
         
    }
    //std::cout<<"E_r "<<energy<<std::endl;

    return energy;
}


double E_c(
    std::vector <Config> const &field,
    double const &min_len,
    const double & multy,
    const double *matrix){

    double Result_energy = 0;
    
    for(auto i: field){
        Result_energy += E_b(i,field,min_len, multy,matrix) + E_r(i,field,min_len, multy,matrix);
    }

    return Result_energy;


}


std::vector<Config> generate_edge( std::vector<Config>  &Field,const nlohmann::json &file_read, std::string const & path_to){

    std::vector<Config> Pool = Field;
    double a = file_read["a"]; 
    int x_ar =file_read["size"]["x"];
    int y_ar = file_read["size"]["y"];
    int z_ar = file_read["size"]["z"];

    for(auto i: Field){    // OY
        for(int j = 1; j<y_ar; ++j){
            //if(i.vec.y+a*j<=y_ar*a){
            Pool.push_back(Config(vector(i.vec.x, i.vec.y+a*j, i.vec.z),
            file_read["A"],
            file_read["eps"],
            file_read["q"],
            file_read["p"]));
            //}
           
        }
    }

    Field = Pool;
    for(auto i: Field){    // OX
        for(int j = 1; j<x_ar; ++j){
            //if(i.vec.x+a*j<=x_ar*a){
            Pool.push_back(Config(vector(i.vec.x+a*j, i.vec.y, i.vec.z),
            file_read["A"],
            file_read["eps"],
            file_read["q"],
            file_read["p"]));
            //}
            
        }
    }
    Field = Pool;
    for(auto i: Field){    // OZ
        for(int j = 1; j<z_ar; ++j){
           // if(i.vec.z+a*j<=z_ar*a){
            Pool.push_back(Config(vector(i.vec.x, i.vec.y, i.vec.z+a*j),
            file_read["A"],
            file_read["eps"],
            file_read["q"],
            file_read["p"]));
            //}
            
        }
    }


    std::cout<<"Nodes amount: "<<Pool.size()<<std::endl<<std::endl;


    //Write to file

    for(auto i : Pool){

        std::cout<<"  x:"<<i.vec[0]<<"  y:"<<i.vec[1]<<"  z:"<<i.vec[2]<<std::endl;
        

    }

    std::ofstream fout(path_to,std::ios_base::out);

    fout<<Pool.size()<<std::endl<<std::endl;
    for(auto i:Pool){
        fout<<"V "<<i.vec[0]<<" "<<i.vec[1]<<" "<<i.vec[2]<<std::endl;
    }
    fout.close();
    return Pool;
    






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
            
            multy*double(file_read["edge"][std::to_string(i)]["x"]),//*0.000000001,
            multy*double(file_read["edge"][std::to_string(i)]["y"]),//0.000000001,
            multy*double(file_read["edge"][std::to_string(i)]["z"])//0.000000001
        ),file_read["A"],
        file_read["eps"],
        file_read["q"],
        file_read["p"]));
    }

    
    double Min_len = multy/sqrt(2.0);
    std::string  path_to  = "/home/aquafeet/Рабочий стол/edge.xyz";
    std::vector<Config> Pool = generate_edge(Field, file_read,path_to);    // edges are inside Field vector
    std::cout<<"Min len :  "<<Min_len<<std::endl;
    
    nlohmann::json file_write;
    //file_write["G"] = potential(Field);
    std::ofstream o(argv[2]);
    //std::cout<<"check: "<<Field.size()<<std::endl;

    double alpha = 0.01;
    //E_0
    double matrix_E_0[]= {1.0,1.0,1.0};
    auto e_c = E_c(Pool, Min_len, multy*x_arrow,matrix_E_0)/Pool.size();
    file_write["E_c"] =e_c;
    //
    //delete matrix_E_0;



    //C11 and C12
    double matrix_c_11[]= {1+alpha,1+alpha,1.0};
    auto e_c_11 = E_c(Pool, Min_len, multy*x_arrow,matrix_c_11)/Pool.size();
    //delete matrix_c_11;

    double matrix_c_12[]= {1+alpha,1-alpha,1.0};
    auto e_c_12 = E_c(Pool, Min_len, multy*x_arrow,matrix_c_12)/Pool.size();
    //delete matrix_c_12;

    auto delta_1 = (e_c_11 -e_c)/(multy*multy*multy*alpha*alpha); 
    auto delta_2 = (e_c_12 - e_c)/(multy*multy*multy*alpha*alpha);
    auto C_11 = (delta_1+delta_2)/2;
    auto C_12 = C_11 - delta_1;
    auto B = (C_11+C_12)/3;

    file_write["C_11"] =C_11;
    file_write["C_12"] =C_12;
    file_write["B"] = B;

    //C44


    double matrix_c_44[]= {1.0,1.0,1/(1-alpha*alpha)};
    auto e_c_44 = E_c(Pool, Min_len, multy*x_arrow,matrix_c_44)/Pool.size();
    //delete matrix_c_44;
    auto C_44 = (e_c_44 - e_c)/(2*multy*multy*multy*alpha*alpha);
    file_write["C_44"] = C_44;



    std::cout<<"Data was written to file "<<argv[2]<<std::endl;
    
    std::cout<<"E_c = "<<e_c<<std::endl;
    std::cout<<"B = "<<B<<std::endl;
    std::cout<<"C_11 = "<<C_11<<std::endl;
    std::cout<<"C_12 = "<<C_12<<std::endl;
    std::cout<<"C_44 = "<<C_44<<std::endl;
    

    o << file_write; 
    o.close();

    return 0;
}










