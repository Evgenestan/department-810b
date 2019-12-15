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
//#include "optimizator.h"


struct Optimizer{
    double e_coh_i, B_i, C11_i, C12_i, C44_i, e_target_i, multy, e_coh_B;
    double lambda, residual;
    double epsilon;
    int epoch, step;
    int arrow;
    std::vector<Atom> Pool;
    ParamsArray features;
    double Min_len;
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
        int _step,
        int _epoch,
        double _lambda,
        double _residual,
        double _e_coh_B,
        double _epsilon):

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
    arrow(_x_arrow),
    step(_step),
    epoch(_epoch),
    lambda(_lambda),
    residual(_residual),
    e_coh_B(_e_coh_B),
    epsilon(_epsilon)
    {


        //intervals



    };

    inline double error_function(double & e_coh,
    double & B,
    double & C11,
    double & C12,
    double & C44,
    double & e_target );

    double calculate_energy_params(ParamsArray & temp_arr);

    void run();   

    double optimizer_Huk_Jivs(ParamsArray & init_pa);
    
    ParamsArray random_variation_search();



};


double optimizer_Huk_Jivs_beta(
    ParamsArray & init_pa,
    double & lambda,
    double & residual,
    int & step);


double distance(const vector& lv,
    const vector& rv, 
    const double & length, 
    const double * matrix,
    int size =3);

double E_b(
    Atom const  &elem,
    std::vector <Atom> const &field,
    double const &min_len,
    const double & multy,
    const double* matrix,
    const int & size,
    const ParamsArray& feature);


double E_r(
    Atom const & elem,
    std::vector <Atom> const  &field,
    double const  &min_len,
    const double& multy,
    const double * matrix,
    const int & size,
    const ParamsArray& feature
    );

double E_c(
    std::vector <Atom> const &field,
    double const &min_len,
    const double & multy,
    const double *matrix,
    const int & size,
    const ParamsArray& feature);

std::vector<Atom> generate_edge( 
    std::vector<Atom>  &Field,
    const nlohmann::json &file_read,
    std::string const & path_to);

bool operator == (
    const Atom & left,
    const Atom & right );


double random_par(
    double lower_bound,
    double upper_bound);





#endif