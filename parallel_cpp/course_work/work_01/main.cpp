#include <iostream>
#include "vector.h"
#include "nlohmann/json.hpp"
#include "fstream"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "struct.h"
#include "optimizator.h"
//#include <tbb/parallel_for.h>

//#define Main_constant 1.602;
//#define alpha 0.01;

//#include "tbb/blocked_range.h"
//#include <tbb/parallel_for.h>

int main(int argc, char * argv[]){
    //read input json 
    
    if(argc <2){
        throw std::logic_error("Error, need two params");
        }


    std::vector<Atom> Field;
    
    nlohmann::json file_read;
    std::ifstream h(argv[1]);
    h>>file_read;

    std::cout<<"File "<<argv[1]<<" was successfully read."<<std::endl;


    
    
    //extract atom data
    double multy = file_read["initial_energy"]["a"];
    int x_arrow = file_read["size"]["x"]; 
    int y_arrow = file_read["size"]["y"];
    int z_arrow = file_read["size"]["z"];
    
    for(int i = 0;i<file_read["edge"]["n"]; ++i){
        Field.push_back(Atom(vector(
            
            multy*double(file_read["edge"][std::to_string(i)]["x"]),
            multy*double(file_read["edge"][std::to_string(i)]["y"]),
            multy*double(file_read["edge"][std::to_string(i)]["z"])
        ),file_read["type"]));
    }
    

    double Min_len = multy/sqrt(2.0);   //r_0 for all types of interaction
    std::string  path_to  = "/home/aquafeet/Рабочий стол/edge.xyz";
    std::vector<Atom> Pool = generate_edge(Field, file_read,path_to);    // edges are inside Field vector

    //std::cout<<Main_constant<<std::endl;
    std::cout<<"Min len :  "<<Min_len<<std::endl;

//initialization of potencial_features.
//need to improve

//#define Main_constant 1.602;

    
    ParamsArray feature {2};

    feature.arr[A][A] = Params(file_read["initial_potencial_features"]["A0"],
        file_read["initial_potencial_features"]["A1"],
        file_read["initial_potencial_features"]["p"],
        file_read["initial_potencial_features"]["q"],
        file_read["initial_potencial_features"]["qsi"]);

    feature.arr[A][B] = Params(file_read["initial_potencial_features"]["A0"],
        file_read["initial_potencial_features"]["A1"],
        file_read["initial_potencial_features"]["p"],
        file_read["initial_potencial_features"]["q"],
        file_read["initial_potencial_features"]["qsi"]);


    /*feature.arr[B][B] = Params(file_read["initial_potencial_features"]["A0"],
        file_read["initial_potencial_features"]["A1"],
        file_read["initial_potencial_features"]["p"],
        file_read["initial_potencial_features"]["q"],
        file_read["initial_potencial_features"]["qsi"]);*/

        //important размерность должна быть нормальной из электронвольт 

    //E_sol task
    //init
    Optimizer objOptimizer (
        file_read["initial_energy"]["E_c"],
        (file_read["initial_energy"]["B"]),
        (file_read["initial_energy"]["C11"]),
        (file_read["initial_energy"]["C12"]),
        (file_read["initial_energy"]["C44"]),
        Pool,
        feature,
        Min_len,
        multy,
        file_read["initial_energy"]["E_sol"],
        x_arrow,
        file_read["optimizer_params"]["step"],
        file_read["optimizer_params"]["epoch"],
        file_read["optimizer_params"]["lambda"],
        file_read["optimizer_params"]["residual"],
        file_read["e_coh_B"], //add atom
        file_read["optimizer_params"]["epsilon"],
        file_read["optimizer_params"]["delta"]);

    
    //objOptimizer.test();


    
    ParamsArray a = objOptimizer.run();

    
    nlohmann::json file_write;
    //file_write["G"] = potential(Field);
    std::ofstream o(argv[2]);
    file_write["A-A"]["A0"] =a.arr[A][A].A0;
    file_write["A-A"]["A1"] = a.arr[A][A].A1;
    file_write["A-A"]["qsi"] = a.arr[A][A].qsi;
    file_write["A-A"]["p"] = a.arr[A][A].p0;
    file_write["A-A"]["q"] = a.arr[A][A].q0;

    file_write["A-B"]["A0"] =a.arr[A][B].A0;
    file_write["A-B"]["A1"] = a.arr[A][B].A1;
    file_write["A-B"]["qsi"] = a.arr[A][B].qsi;
    file_write["A-B"]["p"] = a.arr[A][B].p0;
    file_write["A-B"]["q"] = a.arr[A][B].q0;


    o << file_write; 
    o.close();



}

/*int main(int argc, char * argv[]){


    
    //paramsArray.arr[A][B];

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
    auto e_c = E_c(Pool, Min_len, multy*x_arrow,matrix_E_0,3)/Pool.size();
    file_write["E_c"] =e_c;
    //
    //delete matrix_E_0;

    //constants

    auto const Main_constant = 1.602;    //important размерность должна быть нормальной из электронвольт 
    auto const alpha_p2 = alpha*alpha;
    auto const V_0 = multy*multy*multy/4;

    //C11 and C12
    double matrix_c_11_plus[]= {1+alpha,1+alpha,1.0};
    double matrix_c_11_minus[]= {1-alpha,1-alpha,1.0};

    auto e_c_11_plus = E_c(Pool, Min_len, multy*x_arrow,matrix_c_11_plus,3)/Pool.size();
    auto e_c_11_minus = E_c(Pool, Min_len, multy*x_arrow,matrix_c_11_minus,3)/Pool.size();

    double matrix_c_12_plus[]= {1+alpha,1-alpha,1.0};
    double matrix_c_12_minus[]= {1-alpha,1+alpha,1.0};


    auto e_c_12_plus = E_c(Pool, Min_len, multy*x_arrow,matrix_c_12_plus,3)/Pool.size();
    auto e_c_12_minus = E_c(Pool, Min_len, multy*x_arrow,matrix_c_12_minus,3)/Pool.size();
    //delete matrix_c_12;

    auto der11 =  (e_c_11_plus - 2*e_c + e_c_11_minus)/(alpha_p2);
    auto der12 = (e_c_12_plus-2*e_c+e_c_12_minus)/(alpha_p2);
    auto C_11 = 1.0/(4.0*V_0)*(der11+der12)*Main_constant;

    auto C_12 = 1.0/(4.0*V_0)*(der11-der12)*Main_constant;
    file_write["C_11"] =C_11;
    file_write["C_12"] =C_12;
    //auto B = (C_11+C_12)/3;

    double B_plus[]= {1+alpha,1+alpha,1+alpha};
    double B_minus[] = {1-alpha,1-alpha,1-alpha};

    auto B_plus_energy = E_c(Pool, Min_len, multy*x_arrow,B_plus,3)/Pool.size();
    auto B_minus_energy = E_c(Pool, Min_len, multy*x_arrow,B_minus,3)/Pool.size();


    auto B = 1.0/(9.0*V_0)*(B_plus_energy-2*e_c+B_minus_energy)/(alpha_p2)*Main_constant;



    file_write["B"] = B;

    //C44



    double matrix_c_44_plus[]= {1.0,alpha,alpha,1.0,1.0/(1-alpha_p2)};
    double matrix_c_44_minus[]= {1.0,-alpha,-alpha,1.0,1.0/(1+alpha_p2)};
    std::cout<<"Matrix size:     "<<sizeof(matrix_c_44_plus)/sizeof(matrix_c_44_plus[0])<<std::endl;
    auto e_c_44_plus = E_c(Pool, Min_len, multy*x_arrow,matrix_c_44_plus,5)/Pool.size();
    auto e_c_44_minus = E_c(Pool, Min_len, multy*x_arrow,matrix_c_44_minus,5)/Pool.size();
    //delete matrix_c_44;
    auto C_44 = 1.0/(4*V_0)*(e_c_44_plus - 2*e_c + e_c_44_minus)/(alpha_p2)*Main_constant;
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
} */










