#ifndef OPTIMIZATOR_H
#define OPTIMIZATOR_H



#include <iostream>
#include "vector.h"
#include "fstream"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "struct.h"
#include "nlohmann/json.hpp"
#include <random>
#include <algorithm>
//#include "optimizator.h"


struct Optimizer{
    double e_coh_i, B_i, C11_i, C12_i, C44_i, e_target_i, multy, e_coh_B;
    double lambda, residual, delta;
    double epsilon;
    int epoch, step;
    int x_arrow, y_arrow, z_arrow;
    std::vector<Atom> Pool;
    ParamsArray features;
    double Min_len;
    double min_func;
    int task_type;
    int id2,id3_1, id3_2;
    double energy_check;
    //double residue;
    Optimizer(){};

    Optimizer(double  _e_coh_i,
        double  _B_i,
        double  _C11_i,
        double  _C12_i,
        double  _C44_i,        
        std::vector<Atom>  _Pool,
        ParamsArray & _feature,
        double  _Min_len,
        double  _multy,
        double  _e_target_i,
        int _x_arrow,
        int _y_arrow,
        int _z_arrow,
        int _step,
        int _epoch,
        double _lambda,
        double _residual,
        double _e_coh_B,
        double _epsilon,
        double _delta,
        int _task_type):
        
    e_coh_i(_e_coh_i),
    B_i(_B_i),
    C11_i(_C11_i),
    C12_i(_C12_i),
    C44_i(_C44_i),
    e_target_i(_e_target_i),
    Pool(_Pool),
    features(_feature),
    Min_len(_Min_len),
    multy(_multy),
    x_arrow(_x_arrow),
    y_arrow(_y_arrow),
    z_arrow(_z_arrow),
    step(_step),
    epoch(_epoch),
    lambda(_lambda),
    residual(_residual),
    e_coh_B(_e_coh_B),
    epsilon(_epsilon),
    delta(_delta),
    task_type(_task_type)
    {

        if(task_type == 2){
            auto find_atom = vector(this->Min_len/2,this->Min_len/2,0);
        
        int m;
        for(m = 0; m<this->Pool.size(); ++m){
            if(this->Pool[m].vec == find_atom){
                
                break;
            }
        }
        id2 = m;
        }
        if(task_type ==3){
            

        auto find_atom_1_surf = vector(0,0,this->multy*(this->z_arrow)/2.0);
        auto find_atom_2_surf = vector(this->Min_len/2.0,this->Min_len/2.0,this->multy*(this->z_arrow)/2.0);

        int m;
        int m1,m2;
        bool f1 = false;
        bool f2 = false;
        for(m = 0; m<this->Pool.size(); ++m){
            if((f1 && f2)){
                break;
            }
            if(this->Pool[m].vec == find_atom_1_surf){
                //std::cout<<"m1"<<std::endl;
                m1 = m;
                f1 = true;
                continue;
            }

            if(this->Pool[m].vec == find_atom_2_surf){
                //std::cout<<"m2"<<std::endl;
                m2 = m;
                f2 = true;
                continue;
            }
        }
        id3_1 = m1;
        id3_1 = m2;
        }
        
    };

    inline double error_function(double & e_coh,
    double & B,
    double & C11,
    double & C12,
    double & C44,
    double & e_target );

    double calculate_energy_params(std::vector<double>  &vec_in, bool flag = false);

    ParamsArray run();   

    double optimizer_Huk_Jivs(ParamsArray &);
    
    ParamsArray random_variation_search();

    std::vector<double> Params_to_vector (ParamsArray & obj);

    ParamsArray vector_to_param(std::vector<double> &vec);

    std::vector<double> first_stage(std::vector<double>  &init_pa, bool & wrong_view, std::vector<double> & delta);

    void test();
};


double vector_std_len(std::vector<double> & vec);

double optimizer_Huk_Jivs_beta(
    ParamsArray & init_pa,
    double & lambda,
    double & residual,
    int & step);


double distance(const vector& lv,
    const vector& rv, 
    const double * array_multy, 
    const double * matrix,
    int size =3);

double E_b(
    Atom const  &elem,
    std::vector <Atom> const &field,
    double const &min_len,
    const double *array_multy,
    const double* matrix,
    const int & size,
    const ParamsArray& feature);


double E_r(
    Atom const & elem,
    std::vector <Atom> const  &field,
    double const  &min_len,
    const double *array_multy,
    const double * matrix,
    const int & size,
    const ParamsArray& feature
    );

double E_c(
    std::vector <Atom> const &field,
    double const &min_len,
    const double *array_multy,
    const double *matrix,
    const int & size,
    const ParamsArray& feature);

std::vector<Atom> generate_edge( 
    std::vector<Atom>  &Field,
    const nlohmann::json &file_read,
    std::string const & path_to,
    const double & _a,
    const int &_x,
    const int & _y,
    const int & _z);

bool operator == (
    const Atom & left,
    const Atom & right );


double random_par(
    double lower_bound,
    double upper_bound);





#endif