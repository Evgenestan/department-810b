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




