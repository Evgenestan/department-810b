#include "optimizator.h"
/*#include <iostream>
#include "vector.h"
#include "nlohmann/json.hpp"
#include "fstream"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "struct.h"
*/


const double  Main_constant =  1.602;
const double alpha = 0.01;





double random_par(double lower_bound, double upper_bound){

    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;
    double a_random_double = unif(re);
    return a_random_double;
}
   

/*double optimizer_Huk_Jivs_beta(ParamsArray & init_pa, double & lambda, double & residual, int & step, double & epsilon, double & delta){

    //calculate_energy_params();



}*/


ParamsArray  Optimizer::vector_to_param(std::vector<double> & vec){


    ParamsArray pa{this->features.size};


    for(int i = 1; i<=pa.size; ++i){

        pa.arr[1][i] = Params(vec[0+5*(i-1)],vec[1+5*(i-1)],vec[2+5*(i-1)],vec[3+5*(i-1)],vec[4+5*(i-1)]);

    }

    return pa;
}



std::vector<double>  Optimizer::Params_to_vector(ParamsArray & obj){


    std::vector<double> vec;
    for(int i = 1; i<=obj.size; ++i){

        vec.push_back(obj.arr[1][i].A0);
        vec.push_back(obj.arr[1][i].A1);
        vec.push_back(obj.arr[1][i].p0);
        vec.push_back(obj.arr[1][i].q0);
        vec.push_back(obj.arr[1][i].qsi);

    }

    return vec;
}



double Optimizer::optimizer_Huk_Jivs(ParamsArray & init_pa){
    //do algorithm

    //init
    double temp;
    ParamsArray temp_pa {init_pa.size};
    temp_pa.vec = init_pa.vec;
    temp_pa.receive_from_vector();
    //std::vector<double> vec = this->Params_to_vector(init_pa);

    double max_func = this->calculate_energy_params(init_pa);
    double temp_func;
    //

    for(int i = 0; i<init_pa.vec.size(); ++i){

    
        temp_pa.vec[i] = temp_pa.vec[i]+this->delta;
        temp_pa.receive_from_vector();

        temp_func = this->calculate_energy_params(temp_pa);

        if(temp_func<max_func){
            max_func = temp_func;
        }
        else{
            temp_pa.vec[i] = init_pa.vec[i];
            temp_pa.vec[i] = temp_pa.vec[i]-this->delta;
            temp_pa.receive_from_vector();

            temp_func = this->calculate_energy_params(temp_pa);
            if(temp_func<max_func){
                max_func = temp_func;
            }
            else{

                 temp_pa.vec[i] = init_pa.vec[i];
                 temp_pa.receive_from_vector();

            }
        }
    }



    //diagonal step


    
}

ParamsArray Optimizer::random_variation_search(){
    ParamsArray new_random;
    new_random.arr[A][A] = Params(
        random_par(this->features.arr[A][A].A0/2,this->features.arr[A][A].A0*2),
        random_par(this->features.arr[A][A].A1/2,this->features.arr[A][A].A1*2),
        random_par(this->features.arr[A][A].p0/2,this->features.arr[A][A].p0*2),
        random_par(this->features.arr[A][A].q0/2,this->features.arr[A][A].q0*2),
        random_par(this->features.arr[A][A].qsi/2,this->features.arr[A][A].qsi*2)
    );
    new_random.arr[B][B] =  new_random.arr[A][A];
    //std::cout<<"Params:   "<<new_random.arr[A][A].A0<<" "<<new_random.arr[A][A].A1<<" "<<new_random.arr[A][A].p0<<" "<<new_random.arr[A][A].q0<<" "<<new_random.arr[A][A].qsi<<std::endl;
    //new_random.arr[A][B] =  new_random.arr[A][A];
    return new_random;
}

void Optimizer::run(){
    
    ParamsArray final_set;
    ParamsArray init_set_rand;
    double satisfy_loss_value;
    double loss_cur;
    bool satisfy = false;

    for(int i = 0; i<epoch; ++i){
        init_set_rand = this->random_variation_search();

        loss_cur = this->optimizer_Huk_Jivs(init_set_rand);
        //loss_cur = optimizer_Huk_Jivs_beta(init_set_rand, this->lambda, this->residual, this->step, this->epsilon, this->delta);
        //start optimizer function with init params


        if(loss_cur<=this->residual){
            final_set = init_set_rand;
            satisfy_loss_value = loss_cur;
            satisfy = true;
            break;
        }

    }

    if(satisfy = false){
        std::cout<<"No solution found :("<<std::endl;
    }

    else{
        std::cout<<"Solution found!!!"<<std::endl<<"Loss function = "<< satisfy_loss_value << std::endl;
    }
    
    //check error function


    //

}

double distance(const vector& lv,const vector& rv, const double & length, const double * matrix, int size){
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
    
    

    if(size!=3){
    return sqrt((x_r*matrix[0]+y_r*matrix[1])*((x_r*matrix[0]+y_r*matrix[1]))
    +(y_r*matrix[3]+x_r*matrix[2])*(y_r*matrix[3]+x_r*matrix[2])+(z_r*matrix[4])*(z_r*matrix[4]));
    }
    else{
    return sqrt(x_r*x_r*matrix[0]*matrix[0]+y_r*y_r*matrix[1]*matrix[1]+z_r*z_r*matrix[2]*matrix[2]);
    }
    
}




double E_b(
    Atom const  &elem,
    std::vector <Atom> const &field,
    double const &min_len,
    const double & multy,
    const double* matrix,
    const int & size,
    const ParamsArray& feature){

    double energy = 0;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{

            auto fi = feature.arr[i.type][elem.type];
            energy+= pow(fi.qsi,2)*exp(-2*fi.q0*(distance( i.vec,elem.vec, multy, matrix,size)/min_len-1));
            energy+=fi.qsi*exp(-2*fi.q0*(distance( i.vec,elem.vec, multy, matrix,size)/min_len-1));

        }
         
    }

    return -pow(energy,0.5);
}

double E_r(
    Atom const & elem,
    std::vector <Atom> const  &field,
    double const  &min_len,
    const double& multy,
    const double * matrix,
    const int & size,
    const ParamsArray& feature
    ){

    double energy = 0;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{
            auto fi = feature.arr[i.type][elem.type];
            energy+= (fi.A1*(distance( i.vec,elem.vec, multy, matrix,size)-min_len)+fi.A0)*exp(-fi.p0*(distance(i.vec, elem.vec,  multy, matrix, size)/min_len-1));
        }
         
    }
    //std::cout<<"E_r "<<energy<<std::endl;

    return energy;
}


double E_c(
    std::vector <Atom> const &field,
    double const &min_len,
    const double & multy,
    const double *matrix,
    const int & size,
    const ParamsArray& feature){

    double Result_energy = 0;
    
    for(auto i: field){
        Result_energy += E_b(i,field,min_len, multy,matrix,size,feature) + E_r(i,field,min_len, multy,matrix,size,feature);
    }

    return Result_energy;


}


std::vector<Atom> generate_edge( std::vector<Atom>  &Field,const nlohmann::json &file_read, std::string const & path_to){

    std::vector<Atom> Pool = Field;
    double a = file_read["initial_energy"]["a"]; 
    int x_ar =file_read["size"]["x"];
    int y_ar = file_read["size"]["y"];
    int z_ar = file_read["size"]["z"];
    for(auto i: Field){    // OY
        for(int j = 1; j<y_ar; ++j){
            //if(i.vec.y+a*j<=y_ar*a){
            Pool.push_back(Atom(vector(i.vec.x, i.vec.y+a*j, i.vec.z),
            file_read["type"]));
            //}
           
        }
    }

    Field = Pool;
    for(auto i: Field){    // OX
        for(int j = 1; j<x_ar; ++j){
            //if(i.vec.x+a*j<=x_ar*a){
            Pool.push_back(Atom(vector(i.vec.x+a*j, i.vec.y, i.vec.z),
            file_read["type"]));
            //}
            
        }
    }
    Field = Pool;
    for(auto i: Field){    // OZ
        for(int j = 1; j<z_ar; ++j){
           // if(i.vec.z+a*j<=z_ar*a){
            Pool.push_back(Atom(vector(i.vec.x, i.vec.y, i.vec.z+a*j),
            file_read["type"]));
            //}
            
        }
    }


    std::cout<<"Nodes amount: "<<Pool.size()<<std::endl<<std::endl;


    //Write to file


    std::ofstream fout(path_to,std::ios_base::out);

    fout<<Pool.size()<<std::endl<<std::endl;
    for(auto i:Pool){
        fout<<"V "<<i.vec[0]<<" "<<i.vec[1]<<" "<<i.vec[2]<<std::endl;
    }
    fout.close();
    return Pool;
}


bool operator == ( const Atom & left, const Atom & right ){
        return  (left.vec == right.vec &&  left.type == right.type);

    }


double Optimizer::error_function(double & e_coh,
    double & B,
    double & C11,
    double & C12,
    double & C44,
    double & e_target ){

        return sqrt((
        (B-this->B_i)*(B-this->B_i)/(this->B_i*this->B_i)+
        (C11-this->C11_i)*(C11-this->C11_i)/(this->C11_i*this->C11_i)+
        (C12-this->C12_i)*(C12-this->C12_i)/(this->C12_i*this->C12_i)+
        (C44-this->C44_i)*(C44-this->C44_i)/(this->C44_i*this->C44_i)+
        (e_coh-this->e_coh_i)*(e_coh-this->e_coh_i)/(this->e_coh_i*this->e_coh_i)+
        (e_target-this->e_target_i)*(e_target-this->e_target_i)/(this->e_target_i*this->e_target_i))/this->Pool.size());

    }


double Optimizer::calculate_energy_params(ParamsArray & temp_arr){
    //E_coh

    double matrix_E_0[]= {1.0,1.0,1.0};
    auto size = this->Pool.size();
    auto e_c = E_c(this->Pool,this->Min_len,this->multy,matrix_E_0,3,temp_arr);
    auto const alpha_p2 = alpha*alpha;
    auto const V_0 = this->multy*this->multy*this->multy/4;

    //C11 and C12

    double matrix_c_11_plus[]= {1+alpha,1+alpha,1.0};
    double matrix_c_11_minus[]= {1-alpha,1-alpha,1.0};

    int x_arrow = this->arrow;

    auto e_c_11_plus = E_c(this->Pool, this->Min_len, this->multy*x_arrow,matrix_c_11_plus,3,temp_arr)/size;
    auto e_c_11_minus = E_c(this->Pool, this->Min_len,  this->multy*x_arrow,matrix_c_11_minus,3,temp_arr)/size;

    double matrix_c_12_plus[]= {1+alpha,1-alpha,1.0};
    double matrix_c_12_minus[]= {1-alpha,1+alpha,1.0};


    auto e_c_12_plus = E_c(this->Pool, this->Min_len,  this->multy*x_arrow,matrix_c_12_plus,3,temp_arr)/size;
    auto e_c_12_minus = E_c(this->Pool, this->Min_len,  this->multy*x_arrow,matrix_c_12_minus,3,temp_arr)/size;


    auto der11 =  (e_c_11_plus - 2*e_c + e_c_11_minus)/(alpha_p2);
    auto der12 = (e_c_12_plus-2*e_c+e_c_12_minus)/(alpha_p2);
    auto C_11 = 1.0/(4.0*V_0)*(der11+der12)*Main_constant;

    auto C_12 = 1.0/(4.0*V_0)*(der11-der12)*Main_constant;

    //B

    double B_plus[]= {1+alpha,1+alpha,1+alpha};
    double B_minus[] = {1-alpha,1-alpha,1-alpha};

    auto B_plus_energy = E_c(this->Pool, this->Min_len,  this->multy*x_arrow,B_plus,3,temp_arr)/size;
    auto B_minus_energy = E_c(this->Pool, this->Min_len,  this->multy*x_arrow,B_minus,3,temp_arr)/size;


    auto B = 1.0/(9.0*V_0)*(B_plus_energy-2*e_c+B_minus_energy)/(alpha_p2)*Main_constant;

    //C44



    double matrix_c_44_plus[]= {1.0,alpha,alpha,1.0,1.0/(1-alpha_p2)};
    double matrix_c_44_minus[]= {1.0,-alpha,-alpha,1.0,1.0/(1+alpha_p2)};

    auto e_c_44_plus = E_c(Pool, Min_len,  this->multy*x_arrow,matrix_c_44_plus,5,temp_arr)/size;
    auto e_c_44_minus = E_c(Pool, Min_len,  this->multy*x_arrow,matrix_c_44_minus,5,temp_arr)/size;
    auto C_44 = 1.0/(4*V_0)*(e_c_44_plus - 2*e_c + e_c_44_minus)/(alpha_p2)*Main_constant;

    //E_sol
    this->Pool[0].type = atom_kernel::B;
    auto e_AB = E_c(Pool, Min_len, this->multy*x_arrow, matrix_E_0, 3, temp_arr); 
    auto e_sol = e_AB - e_c/this->Pool.size() - e_coh_B + e_c;
    this->Pool[0].type = atom_kernel::A;
    std::cout<<"Energy:   "<< e_sol<< std::endl;



    // calculation of error function
    auto rezult = this->error_function(e_c,B,C_11,C_12,C_44,e_sol);

    return rezult;
//calculate all energy params


}




