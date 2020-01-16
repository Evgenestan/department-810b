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
#include <cstdlib>
//#include <tbb/parallel_for.h>

//#define Main_constant 1.602;
//#define alpha 0.01;

//#include "tbb/blocked_range.h"
//#include <tbb/parallel_for.h>

int main(int argc, char * argv[]){
    //read input json 
    
    if(argc < 4){
        throw std::logic_error("Error, need three params");
        }

    //std::cout<<argc<<std::endl;
    std::vector<Atom> Field;
    
    nlohmann::json file_read;
    std::ifstream h(argv[1]);
    h>>file_read;

    std::cout<<"File "<<argv[1]<<" was successfully read."<<std::endl;

    //std::cout<<"arg3 :"<<"   "<<argv[3]<<std::endl;
    
    
    //extract atom data
    double multy = file_read["a"];
    int x_arrow = file_read["size"]["x"]; 
    int y_arrow = file_read["size"]["y"];
    int z_arrow = file_read["size"]["z"];

    std::cout<<(argv[3])<<std::endl;


    //std::cout<<"SizeL: z="<<z_arrow<<" x = "<<x_arrow<<std::endl;
    
    for(int i = 0;i<file_read["edge"]["n"]; ++i){
        Field.push_back(Atom(vector(
            
            multy*double(file_read["edge"][std::to_string(i)]["x"]),
            multy*double(file_read["edge"][std::to_string(i)]["y"]),
            multy*double(file_read["edge"][std::to_string(i)]["z"])
        ),atom_kernel::A));
    }
    

    double Min_len = multy/sqrt(2.0);   //r_0 for all types of interaction
    std::string  path_to  = "/home/aquafeet/Рабочий стол/edge.xyz";
    std::vector<Atom> Pool = generate_edge(Field,
     file_read,
     path_to,
     multy,
     x_arrow,
     y_arrow,
     z_arrow);    // edges are inside Field vector

    //std::cout<<Main_constant<<std::endl;
    //std::cout<<"Min len :  "<<Min_len<<std::endl;
    //std::cout<<"Pool: "<<std::endl;
    //--show Pool
    /*int numb = 0;
    for(auto i: Pool){
        std::cout<<"Atom "<<numb<<" "<<i.vec.x/multy<<" "<<i.vec.y/multy<<" "<<i.vec.z/multy<<std::endl;
        ++numb;
    }*/


    ParamsArray feature;
    feature.size = 3;
    /*if(atoi(argv[3]) == 3 || atoi(argv[3]) == 2){
        feature.size = 3;
    }
    else
        feature.size = 2;*/



    feature.arr[A][A] = Params(file_read["initial_potential_features"]["A0"],
        file_read["initial_potential_features"]["A1"],
        file_read["initial_potential_features"]["p"],
        file_read["initial_potential_features"]["q"],
        file_read["initial_potential_features"]["qsi"]);

    feature.arr[A][B] = Params(file_read["initial_potential_features"]["A0"],
        file_read["initial_potential_features"]["A1"],
        file_read["initial_potential_features"]["p"],
        file_read["initial_potential_features"]["q"],
        file_read["initial_potential_features"]["qsi"]);

    feature.arr[B][B] = Params(file_read["initial_potential_features"]["A0"],
        file_read["initial_potential_features"]["A1"],
        file_read["initial_potential_features"]["p"],
        file_read["initial_potential_features"]["q"],
        file_read["initial_potential_features"]["qsi"]);




        //important размерность должна быть нормальной из электронвольт 








    double p1_x_2=0.0;
    double p1_y_2=0.0;
    double p1_z_2=0.0;
    double p2_x_2=0.0;
    double p2_y_2=0.0;
    double p2_z_2=0.0;

    double p1_x_3=0.0;
    double p1_y_3=0.0;
    double p1_z_3=0.0;
    double p2_x_3=0.0;
    double p2_y_3=0.0;
    double p2_z_3=0.0;

    //if(atoi(argv[3]) == 2){
       p1_x_2 = multy*double(file_read["place_atoms"]["2"]["1_atom"]["x"]);
       p1_y_2 = multy*double(file_read["place_atoms"]["2"]["1_atom"]["y"]);
       p1_z_2 = multy*double(file_read["place_atoms"]["2"]["1_atom"]["z"]);
       p2_x_2 = multy*double(file_read["place_atoms"]["2"]["2_atom"]["x"]);
       p2_y_2 = multy*double(file_read["place_atoms"]["2"]["2_atom"]["y"]);
       p2_z_2 = multy*double(file_read["place_atoms"]["2"]["2_atom"]["z"]);
    //}


    //}

    p1_x_3 = multy*double(file_read["place_atoms"]["3"]["1_atom"]["x"]);
    p1_y_3 = multy*double(file_read["place_atoms"]["3"]["1_atom"]["y"]);
    p1_z_3 = multy*double(file_read["place_atoms"]["3"]["1_atom"]["z"]);
    p2_x_3 = multy*double(file_read["place_atoms"]["3"]["2_atom"]["x"]);
    p2_y_3 = multy*double(file_read["place_atoms"]["3"]["2_atom"]["y"]);
    p2_z_3 = multy*double(file_read["place_atoms"]["3"]["2_atom"]["z"]);



    std::string vacuum = file_read["direction_vacuum"];
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
        file_read["initial_energy"]["e_sol"],
        file_read["initial_energy"]["e_in_dim"],
        file_read["initial_energy"]["e_on_dim"],
        x_arrow,
        y_arrow,
        z_arrow,
        file_read["optimizer_params"]["step"],
        file_read["optimizer_params"]["epoch"],
        file_read["optimizer_params"]["lambda"],
        file_read["optimizer_params"]["residual"],
        file_read["e_coh_B"], //add atom
        file_read["optimizer_params"]["epsilon"],
        file_read["optimizer_params"]["delta"],
        p1_x_2,
        p1_y_2,
        p1_z_2,
        p2_x_2,
        p2_y_2,
        p2_z_2,
        p1_x_3,
        p1_y_3,
        p1_z_3,
        p2_x_3,
        p2_y_3,
        p2_z_3,
        vacuum[0],
        file_read["optimizer_params"]["l_b_multy"],
        file_read["optimizer_params"]["r_b_multy"]
        );

        //std::cout<<objOptimizer.e_target_i<<std::endl<<objOptimizer.x_arrow<<objOptimizer.y_arrow<<objOptimizer.z_arrow<<std::endl<<objOptimizer.task_type;

    
    //objOptimizer.test();

    ParamsArray a;
    bool satisfy = false;
    tbb::parallel_for( tbb::blocked_range<int>(0,int(file_read["optimizer_params"]["epoch"]),4),
                       [&](const tbb::blocked_range<int> &r ){
                           for(int i = r.begin();i!=r.end();++i) {
                               if(satisfy == true){

                               break;
                           }
                               std::cout << "Start Epoch: " << i << std::endl;
                               bool flag = false;
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
                                       file_read["initial_energy"]["e_sol"],
                                       file_read["initial_energy"]["e_in_dim"],
                                       file_read["initial_energy"]["e_on_dim"],
                                       x_arrow,
                                       y_arrow,
                                       z_arrow,
                                       file_read["optimizer_params"]["step"],
                                       file_read["optimizer_params"]["epoch"],
                                       file_read["optimizer_params"]["lambda"],
                                       file_read["optimizer_params"]["residual"],
                                       file_read["e_coh_B"], //add atom
                                       file_read["optimizer_params"]["epsilon"],
                                       file_read["optimizer_params"]["delta"],
                                       p1_x_2,
                                       p1_y_2,
                                       p1_z_2,
                                       p2_x_2,
                                       p2_y_2,
                                       p2_z_2,
                                       p1_x_3,
                                       p1_y_3,
                                       p1_z_3,
                                       p2_x_3,
                                       p2_y_3,
                                       p2_z_3,
                                       vacuum[0],
                                       file_read["optimizer_params"]["l_b_multy"],
                                       file_read["optimizer_params"]["r_b_multy"]
                               );
                               ParamsArray temp = objOptimizer.run(i,flag);
                               if(flag == true){
                                satisfy == true;
                                a = temp;
                               }

                           }

    });


    std::cout<<"End of evaluations"<<std::endl;
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

    //if(atoi(argv[3]) == 2 || atoi(argv[3]) == 3){
        file_write["B-B"]["A0"] =a.arr[B][B].A0;
        file_write["B-B"]["A1"] = a.arr[B][B].A1;
        file_write["B-B"]["qsi"] = a.arr[B][B].qsi;
        file_write["B-B"]["p"] = a.arr[B][B].p0;
        file_write["B-B"]["q"] = a.arr[B][B].q0;
    //}


    o << file_write; 
    o.close();



}

