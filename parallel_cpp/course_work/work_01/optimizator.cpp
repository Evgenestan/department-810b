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
    std::mt19937_64 rng(time(0));
    double a_random_double = unif(rng);
    return a_random_double;
}
   

/*double optimizer_Huk_Jivs_beta(ParamsArray & init_pa, double & lambda, double & residual, int & step, double & epsilon, double & delta){

    //calculate_energy_params();



}*/


ParamsArray  Optimizer::vector_to_param(std::vector<double> &vec){


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

std::vector<double> operator-(const std::vector<double> & lhs, const std::vector<double> & rhs){
    //auto result = vector();
    std::vector<double> result;
    for(int i = 0; i< lhs.size(); ++i){
        result.push_back(lhs[i]-rhs[i]);
    }   
    return result;
}


std::vector<double> operator*(const std::vector<double> & lhs, const double & number){
    //auto result = vector();
    std::vector<double> result;
    for(int i = 0; i< lhs.size(); ++i){
        result.push_back(lhs[i]*number);
    }   
    return result;
}


 void show(std::vector<double> & vec){
                        for(auto i: vec){
                            std::cout<<" "<<i;
                        }
                        std::cout<<std::endl;
                    }


std::vector<double> Optimizer::first_stage(std::vector<double> & init_pa, bool & wrong_view, std::vector<double> & delta){

    //std::cout<<"ALgo 4  "<<init_pa.size()<<std::endl;

    //make delta

    //
    std::vector<double> temp_vec = init_pa;
    double F_1;
    this->min_func = this->calculate_energy_params(temp_vec);


    for(int i = 0; i<init_pa.size(); ++i){

       
        temp_vec[i] = init_pa[i]+delta[i];
        //std::cout<<"hereweare"<<std::endl;
        F_1 = this->calculate_energy_params(temp_vec);

        if(F_1 < this->min_func){
            this->min_func = F_1;
            wrong_view = false;
        }

        else{
            temp_vec[i] = init_pa[i] - delta[i];
            
            F_1 = this->calculate_energy_params(temp_vec);

            if(F_1<this->min_func){
                this->min_func = F_1;
                wrong_view = false;
            }
            else{
                 temp_vec[i] = init_pa[i];
            }
        }
    }
    return temp_vec;
}


double vector_std_len(std::vector<double> & vec){
    double len = 0;
    for(auto i: vec){
        len+=i*i;
    }
    return sqrt(len);
}

double Optimizer::optimizer_Huk_Jivs(ParamsArray  & init){
    //do algorithm

    //init delta vec
    std::vector<double> delta;
    for(auto i: this->features.vec){

        if(abs(i)<1)
            delta.push_back(this->delta/10.0);
        else
        {
            delta.push_back(this->delta);
        }

    }
    //init


    
    
    std::vector<double> X_1;
    std::vector<double> X_2;
    std::vector<double> X_3;
    std::vector<double> X_0 = init.vec; 
    std::cout<<X_0.size()<<std::endl;

    int count = 0;

    bool wrong_view = true;
    bool flag = false;
    bool flag_revert = false;


    do{

        std::cout<<"Delta: "<<vector_std_len(delta) << " in iteration " << count <<std::endl;
        
        if(!flag){
            X_1 = first_stage(X_0, wrong_view,delta);
            std::cout<<"First type step:  "<< wrong_view<<std::endl;
            
        }

        if(wrong_view || flag_revert)
            delta = delta*(0.5);
            if(flag_revert){
                flag_revert = false;
                flag = false;
            }
                
          
        else{
            X_2 = X_1*2 - X_0;
           
            wrong_view = true;
            X_3 = first_stage(X_2,wrong_view,delta);

            if(wrong_view){

                //flag_revert = true;
                flag = false;
                
                X_0 = X_2;
                std::cout<<"Error function: "<<this->calculate_energy_params(X_0)<<std::endl;
                std::cout<<"No change in X"<<std::endl;
                continue;
            }

            if(this->calculate_energy_params(X_3) > this->calculate_energy_params(X_1)){
                X_0 = X_1;
                std::cout<<"Second type step is bad (X3>X1)"<<std::endl;
                flag = false;
                wrong_view = true ;
                flag_revert = true;
                continue;
            }

            else{
                X_0 = X_1;
                X_1 = X_3;


                //std::cout.setf(std::ios::fixed);
                //std::cout.precision(80);
                std::cout<<"Error function: "<<this->calculate_energy_params(X_3)<<std::endl;
                flag = true;  
                wrong_view = false;
                flag_revert = false;  
                std::cout<<"Зашло"<<std::endl;   
            }
        }

        ++count;
    } while(vector_std_len(delta) > (this->epsilon ) && count != step);



    std::cout<<"Fimal step:  "<<vector_std_len(delta)<<std::endl;
    /*do{

        std::cout<<"Delta: "<<this->delta<< " in iteration " << count <<std::endl;
        
        if(!flag){
            wrong_view = true;
            X_1 = first_stage(X_0, wrong_view,delta);
        }

        if(wrong_view && !flag)
            delta = delta*(0.5);
          
        else{
            X_2 = X_1*2 - X_0;

            wrong_view = true;
            X_3 = first_stage(X_2,wrong_view,delta);
          
            if(this->calculate_energy_params(X_3) > this->calculate_energy_params(X_1)){
                X_0 = X_1;
                flag = false;
            }

            else{
                X_0 = X_1;
                X_1 = X_3;


                std::cout.setf(std::ios::fixed);
                std::cout.precision(80);
                std::cout<<"Error function: "<<this->calculate_energy_params(X_3)<<std::endl;
                flag = true;        
            }
        }

        ++count;
    } while(vector_std_len(delta) > (this->epsilon ) && count != step);*/






    //GOVNOKOD mama prosti menya

    std::vector<double> ret_val;

    if(this->calculate_energy_params(X_1)<=this->calculate_energy_params(X_3) && 
       this->calculate_energy_params(X_1)<=this->calculate_energy_params(X_2))
        ret_val = X_1;
    else if(this->calculate_energy_params(X_2)<=this->calculate_energy_params(X_3) &&
        this->calculate_energy_params(X_2)<=this->calculate_energy_params(X_1))
        ret_val = X_2;
    else 
        ret_val = X_3;
    
    init.vec = ret_val;
    init.receive_from_vector();


    show(X_1);
    show(X_2);
    show(X_3);
   // std::cout << this->calculate_energy_params(ret_val) << std::endl;
  //  show(ret_val);
    return this->calculate_energy_params(ret_val);
    
}

ParamsArray Optimizer::random_variation_search(){
    ParamsArray new_random;
    new_random.arr[A][A] = Params(
        random_par(this->features.arr[A][A].A0/4,this->features.arr[A][A].A0*4),
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


void Optimizer::test(){

    //A_0 = 0
        //init_set_rand.convert_to_vector();
        //std::cout<<"SIZW "<<init_set_rand.vec.size()<<std::endl;
        this->features.convert_to_vector();
        ParamsArray init_set_rand = this->features;
        
        //std::cout<<"start: "<<this->features.vec.size()<<std::endl;
        //std::cout<<"start: "<<init_set_rand.vec.size()<<std::endl;

        double loss_cur = this->optimizer_Huk_Jivs(init_set_rand);

        //double loss_cur = this->calculate_energy_params(init_set_rand.vec);
        std::cout<<"end"<<std::endl;
        std::cout<<"A0: "<<init_set_rand.vec[0]<<std::endl;
        std::cout<<"A1: "<<init_set_rand.vec[1]<<std::endl;
        std::cout<<"p0: "<<init_set_rand.vec[2]<<std::endl;
        std::cout<<"q0: "<<init_set_rand.vec[3]<<std::endl;
        std::cout<<"qsi: "<<init_set_rand.vec[4]<<std::endl;
        //loss_cur = optimizer_Huk_Jivs_beta(init_set_rand, this->lambda, this->residual, this->step, this->epsilon, this->delta);
        //start optimizer function with init params
        std::cout<<"Loss: "<<loss_cur<<std::endl;


}


ParamsArray Optimizer::run(){
    
    this->features.convert_to_vector();
    ParamsArray final_set;
    ParamsArray init_set_rand;
    double satisfy_loss_value;
    double loss_cur;
    bool satisfy = false;

    for(int i = 0; i<epoch; ++i){


        std::cout<<"Epoch: "<<i<<std::endl;

        init_set_rand = this->random_variation_search();
        init_set_rand.convert_to_vector();

        //std::cout<<"SIZW "<<init_set_rand.vec.size()<<std::endl;
        loss_cur = this->optimizer_Huk_Jivs(init_set_rand);
        //loss_cur = optimizer_Huk_Jivs_beta(init_set_rand, this->lambda, this->residual, this->step, this->epsilon, this->delta);
        //start optimizer function with init params
        std::cout<<"Loss: "<<loss_cur<<std::endl;
        if(loss_cur<=this->residual){
            final_set = init_set_rand;
            satisfy_loss_value = loss_cur;
            satisfy = true;
            break;
        }

    }

    if(satisfy == false){
        std::cout<<"No solution found :("<<std::endl;
        return ParamsArray();
    }

    else{
        std::cout<<"Solution found!!!"<<std::endl<<"Loss function = "<< satisfy_loss_value << std::endl;
        return final_set;
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
            //energy+=fi.qsi*exp(-2*fi.q0*(distance( i.vec,elem.vec, multy, matrix,size)/min_len-1));

        }
         
    }
    if(energy<0)
    std::cout<<"energy: "<<sqrt(energy)<<std::endl;

    return -sqrt(energy);
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
        //std::cout<<B<<" "<<C11<<" "<<C12<<" "<<C44<<" "<<e_target<<std::endl;

        //for release

        return sqrt((
        (B-this->B_i)*(B-this->B_i)/(this->B_i*this->B_i)+
        (C11-this->C11_i)*(C11-this->C11_i)/(this->C11_i*this->C11_i)+
        (C12-this->C12_i)*(C12-this->C12_i)/(this->C12_i*this->C12_i)+
        (C44-this->C44_i)*(C44-this->C44_i)/(this->C44_i*this->C44_i)+
        (e_coh-this->e_coh_i)*(e_coh-this->e_coh_i)/(this->e_coh_i * this->e_coh_i)+
        (e_target-this->e_target_i)*(e_target-this->e_target_i)/(this->e_target_i * this->e_target_i))/this->Pool.size());
        
        //FOR TEST

        /*return sqrt((
        (B-this->B_i)*(B-this->B_i)/(this->B_i*this->B_i)+
        (C11-this->C11_i)*(C11-this->C11_i)/(this->C11_i*this->C11_i)+
        (C12-this->C12_i)*(C12-this->C12_i)/(this->C12_i*this->C12_i)+
        (C44-this->C44_i)*(C44-this->C44_i)/(this->C44_i*this->C44_i)+
        (e_coh-this->e_coh_i)*(e_coh-this->e_coh_i)/(this->e_coh_i*this->e_coh_i))/this->Pool.size());*/

    }


double Optimizer::calculate_energy_params(std::vector<double>  & vec_in, bool flag){
    //E_coh
    ParamsArray temp_arr  {this->features.size};

    temp_arr.vec = vec_in;
    temp_arr.receive_from_vector();


    double matrix_E_0[]= {1.0,1.0,1.0};
    auto size = this->Pool.size();

    int x_arrow = this->arrow;

    auto e_c = E_c(this->Pool,this->Min_len,this->multy*x_arrow,matrix_E_0,3,temp_arr)/size;
    auto const alpha_p2 = alpha*alpha;
    auto const V_0 = this->multy*this->multy*this->multy/4;

    //C11 and C12

    double matrix_c_11_plus[]= {1+alpha,1+alpha,1.0};
    double matrix_c_11_minus[]= {1-alpha,1-alpha,1.0};


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

    auto e_c_44_plus = E_c(this->Pool, this->Min_len,  this->multy*x_arrow,matrix_c_44_plus,5,temp_arr)/size;
    auto e_c_44_minus = E_c(this->Pool, this->Min_len,  this->multy*x_arrow,matrix_c_44_minus,5,temp_arr)/size;
    auto C_44 = 1.0/(4*V_0)*(e_c_44_plus - 2*e_c + e_c_44_minus)/(alpha_p2)*Main_constant;

    //E_sol
    this->Pool[0].type = atom_kernel::B;

    auto e_AB = E_c(this->Pool, this->Min_len, this->multy*x_arrow, matrix_E_0, 3, temp_arr); 

    

    //auto e_c = E_c(this->Pool,this->Min_len,this->multy,matrix_E_0,3,temp_arr);

    // release
   auto e_sol = e_AB - e_c*this->Pool.size() - e_coh_B + e_c;

    
    


   //test
   //

     //double e_sol = 0;

    //
    this->Pool[0].type = atom_kernel::A;
    

    //std::cout<<"E_sol: "<<e_sol<<"Empty: "<<temp_arr.vec.size()<<std::endl;
    //show(temp_arr.vec);
    //std::cout<<"Energy:   "<< e_sol<< std::endl;



    // calculation of error function
    if(flag)
    std::cout<<"----params :"<<e_c<<" "<<B<<" "<<C_11<<" "<<C_12<<" "<<C_44<<std::endl;
    auto rezult = this->error_function(e_c,B,C_11,C_12,C_44,e_sol);
    //std::cout<<"Error function:   "<<rezult<<std::endl;
    //std::cout<<"Delta:   "<< this->delta<<std::endl; 
   
    return rezult;
//calculate all energy params


}




