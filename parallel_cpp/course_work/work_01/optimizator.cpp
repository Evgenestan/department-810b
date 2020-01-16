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

#define comment true;



double random_par(double lower_bound, double upper_bound,const int & epoch){

    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::mt19937_64 rng((epoch+1)*1000);
    double a_random_double = unif(rng);
    return a_random_double;
}
   

/*double optimizer_Huk_Jivs_beta(ParamsArray & init_pa, double & lambda, double & residual, int & step, double & epsilon, double & delta){

    //calculate_energy_params();



}*/


/*ParamsArray  Optimizer::vector_to_param(std::vector<double> &vec){


    ParamsArray pa{this->features.size};


    for(int i = 1; i<=pa.size; ++i){

        pa.arr[1][i] = Params(vec[0+5*(i-1)],vec[1+5*(i-1)],vec[2+5*(i-1)],vec[3+5*(i-1)],vec[4+5*(i-1)]);

    }

    return pa;
}*/




/*std::vector<double>  Optimizer::Params_to_vector(ParamsArray & obj){


    std::vector<double> vec;
    for(int i = 2; i<=obj.size; ++i){

        vec.push_back(obj.arr[1][i-1].A0);
        vec.push_back(obj.arr[1][i-1].A1);
        vec.push_back(obj.arr[1][i-1].p0);
        vec.push_back(obj.arr[1][i-1].q0);
        vec.push_back(obj.arr[1][i-1].qsi);

    }

    return vec;
}*/

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
    //std::cout<<X_0.size()<<std::endl;

    int count = 0;

    bool wrong_view = true;
    bool flag = false;
    bool flag_revert = false;


    do{

   //5     std::cout<<"Delta: "<<vector_std_len(delta) << " in iteration " << count <<std::endl;
        
        if(!flag){
            X_1 = first_stage(X_0, wrong_view,delta);
         //5   std::cout<<"First type step:  "<< wrong_view<<std::endl;
            
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
            //5    std::cout<<"Error function: "<<this->calculate_energy_params(X_0)<<std::endl;
            //5    std::cout<<"No change in X"<<std::endl;
                continue;
            }

            if(this->calculate_energy_params(X_3) > this->calculate_energy_params(X_1)){
                X_0 = X_1;
             //5   std::cout<<"Second type step is bad (X3>X1)"<<std::endl;
                flag = false;
                wrong_view = true ;
                flag_revert = true;
                continue;
            }

            else{
                X_0 = X_1;
                X_1 = X_3;


#ifndef  comment
                std::cout.setf(std::ios::fixed);
                std::cout.precision(80);
                std::cout<<"Error function: "<<this->calculate_energy_params(X_3)<<std::endl;
#endif
                flag = true;
                wrong_view = false;
                flag_revert = false;  
             //5   std::cout<<"Зашло"<<std::endl;
            }
        }

        ++count;
    } while(vector_std_len(delta) > (this->epsilon ) && count != step);

   //
   // std::cout<<"Energy found through computation = "<< this->energy_check<<std::endl;

    //5 std::cout<<"Final step:  "<<vector_std_len(delta)<<std::endl;
    double rez;
    //std::vector<double> ret_val;
    auto er1 = this->calculate_energy_params(X_1, true);
    auto er2 = this->calculate_energy_params(X_2, true);
    auto er3 = this->calculate_energy_params(X_3, true);
    //std::cout<<"X1 = "<<er1<<"X2 = "<<er2<<"X3 = "<<er3<<std::endl;
    if(er1<=er3 &&er1<=er2){
        init.vec = X_1;
        init.receive_from_vector();
        rez = er1;
    }
    else if(er2<=er1&&er2<=er3) {
        init.vec = X_2;
        init.receive_from_vector();
        rez = er2;
    }
    else {
        init.vec = X_3;
        init.receive_from_vector();
        rez = er3;
    }

    

    return rez;
    
}

ParamsArray Optimizer::random_variation_search(const int & epoch){
    ParamsArray new_random;
    new_random.arr[A][A] = Params(
        random_par(this->features.arr[A][A].A0*this->l_b_multy,this->features.arr[A][A].A0*this->r_b_multy,epoch),
        random_par(this->features.arr[A][A].A1*this->l_b_multy,this->features.arr[A][A].A1*this->r_b_multy,epoch),
        random_par(this->features.arr[A][A].p0*this->l_b_multy,this->features.arr[A][A].p0*this->r_b_multy,epoch),
        random_par(this->features.arr[A][A].q0*this->l_b_multy,this->features.arr[A][A].q0*this->r_b_multy,epoch),
        random_par(this->features.arr[A][A].qsi*this->l_b_multy,this->features.arr[A][A].qsi*this->r_b_multy,epoch)
    );
    new_random.arr[B][B] =  new_random.arr[A][A];
    new_random.arr[A][B] =  new_random.arr[A][A];
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
        


        double loss_cur = this->optimizer_Huk_Jivs(init_set_rand);



}


ParamsArray Optimizer::run(int & i_epoch, bool & flag_check){
    
    this->features.convert_to_vector();
    ParamsArray final_set;
    ParamsArray init_set_rand;
    double satisfy_loss_value;
    double loss_cur;
    bool satisfy = false;
    int ep_good = -1;




        init_set_rand = this->random_variation_search(i_epoch);

        init_set_rand.convert_to_vector();
        this->look_at_start_vector = init_set_rand.vec;

        loss_cur = this->optimizer_Huk_Jivs(init_set_rand);
        //loss_cur = optimizer_Huk_Jivs_beta(init_set_rand, this->lambda, this->residual, this->step, this->epsilon, this->delta);
        //start optimizer function with init params
        //std::cout<<"Loss: "<<loss_cur<<std::endl;

        if(loss_cur<=this->residual){
            final_set = init_set_rand;
            satisfy_loss_value = loss_cur;
            satisfy = true;
            ep_good = i_epoch;
        }





    if(satisfy == false){
        //std::cout<<"No solution found at "<<std::endl;
        std::cout<<"No solution found at Epoch "<<i_epoch<<" Loss: "<<loss_cur<<std::endl;
        flag_check = false;
        return ParamsArray();
    }

    else{
        std::cout<<"Solution found!!!"<<std::endl<<"Loss function = "<< satisfy_loss_value << "  epoch: "<<ep_good<<std::endl;
        std::cout<<"Init rand vector"<<std::endl;
        flag_check = true;
        for(auto i:this->look_at_start_vector)
            std::cout<<i<<std::endl;
        return final_set;
    }




    //check error function


    //

}

double distance(const vector& lv,const vector& rv, const double * array_multy, const double * matrix, int size){
    double x_r, y_r,z_r;
    double x_dif = lv.x-rv.x;
    double y_dif = lv.y - rv.y;
    double z_dif = lv.z - rv.z; 
    if(x_dif>array_multy[0]/2){
        x_r =  (x_dif)-array_multy[0];
    }
    else if(x_dif<-array_multy[0]/2){
    x_r = array_multy[0]+x_dif;
    }
    else{
        x_r = x_dif;
    }

    if(y_dif>array_multy[1]/2){
        y_r =  (y_dif)-array_multy[1];
    }
    else if(y_dif<-array_multy[1]/2){
        y_r = array_multy[1]+y_dif;
    }
    else{
        y_r = y_dif;
    }

    if(z_dif>array_multy[2]/2){
        z_r =  (z_dif) - array_multy[2] ;
    }
    else if(z_dif<-array_multy[2]/2){
        z_r = array_multy[2]+z_dif;
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
    const double *array_multy,
    const double* matrix,
    const int & size,
    const ParamsArray& feature){
    int atom1,atom2;
    double energy = 0;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{

            atom1 = i.type;
            atom2 = elem.type;

            if(i.type == 2){
                atom1 = elem.type;
                atom2 = i.type;

            }


            auto fi = feature.arr[atom1][atom2];

            energy+= pow(fi.qsi,2)*exp(-2*fi.q0*(distance( i.vec,elem.vec, array_multy, matrix,size)/min_len-1));
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
    const double *array_multy,
    const double * matrix,
    const int & size,
    const ParamsArray& feature
    ){

    double energy = 0;
    int atom1, atom2;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{

            atom1 = i.type;
            atom2 = elem.type;

            if(i.type == 2){
                atom1 = elem.type;
                atom2 = i.type;

            }


            auto fi = feature.arr[atom1][atom2];
            energy+= (fi.A1*(distance( i.vec,elem.vec, array_multy, matrix,size)-min_len)+fi.A0)*exp(-fi.p0*(distance(i.vec, elem.vec,  array_multy, matrix, size)/min_len-1));
        }
         
    }
    //std::cout<<"E_r "<<energy<<std::endl;

    return energy;
}


double E_f(
    std::vector <Atom> const &field,
    double const &min_len,
    const double *array_multy,
    const double *matrix,
    const int & size,
    const ParamsArray& feature){

    double Result_energy = 0;
    
    //temp


    for(auto i: field){
        Result_energy += E_b(i,field,min_len, array_multy,matrix,size,feature) + E_r(i,field,min_len, array_multy,matrix,size,feature);
    }

    return Result_energy;


}


std::vector<Atom> generate_edge( 
    std::vector<Atom>  &Field,
    const nlohmann::json &file_read,
    std::string const & path_to,
    const double & _a,
    const int &_x,
    const int & _y,
    const int & _z){

    std::vector<Atom> Pool = Field;
    double a = _a; 
    int x_ar = _x;
    int y_ar = _y;
    int z_ar = _z;
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
    double & e_sol,
    double & e_in_dim,
    double & e_on_dim){

        return sqrt((
        (B-this->B_i)*(B-this->B_i)/(this->B_i*this->B_i)+
        (C11-this->C11_i)*(C11-this->C11_i)/(this->C11_i*this->C11_i)+
        (C12-this->C12_i)*(C12-this->C12_i)/(this->C12_i*this->C12_i)+
        (C44-this->C44_i)*(C44-this->C44_i)/(this->C44_i*this->C44_i)+
        (e_coh-this->e_coh_i)*(e_coh-this->e_coh_i)/(this->e_coh_i * this->e_coh_i)+
        (e_in_dim-this->e_in_dim)*(e_in_dim-this->e_in_dim)/(this->e_in_dim * this->e_in_dim)+
        (e_on_dim-this->e_on_dim)*(e_on_dim-this->e_on_dim)/(this->e_on_dim * this->e_on_dim)+
        (e_sol-this->e_sol)*(e_sol-this->e_sol)/(this->e_sol * this->e_sol))/8);
        


    }


double Optimizer::calculate_energy_params(std::vector<double>  & vec_in, bool flag){
    //E_coh
    ParamsArray temp_arr  {this->features.size};

    temp_arr.vec = vec_in;
    temp_arr.receive_from_vector();


    double matrix_E_0[]= {1.0,1.0,1.0};
    auto size = this->Pool.size();


    double array_mr[] = {this->x_arrow*this->multy,this->y_arrow*this->multy,this->z_arrow*this->multy };

    auto e_c = E_f(this->Pool,this->Min_len,array_mr,matrix_E_0,3,temp_arr)/size;
    auto const alpha_p2 = alpha*alpha;
    auto const V_0 = this->multy*this->multy*this->multy/4;


    double matrix_c_11_plus[]= {1+alpha,1+alpha,1.0};
    double matrix_c_11_minus[]= {1-alpha,1-alpha,1.0};


    auto e_c_11_plus = E_f(this->Pool, this->Min_len, array_mr,matrix_c_11_plus,3,temp_arr)/size;
    auto e_c_11_minus = E_f(this->Pool, this->Min_len,  array_mr,matrix_c_11_minus,3,temp_arr)/size;

    double matrix_c_12_plus[]= {1+alpha,1-alpha,1.0};
    double matrix_c_12_minus[]= {1-alpha,1+alpha,1.0};


    auto e_c_12_plus = E_f(this->Pool, this->Min_len,array_mr,matrix_c_12_plus,3,temp_arr)/size;
    auto e_c_12_minus = E_f(this->Pool, this->Min_len,array_mr,matrix_c_12_minus,3,temp_arr)/size;


    auto der11 =  (e_c_11_plus - 2*e_c + e_c_11_minus)/(alpha_p2);
    auto der12 = (e_c_12_plus-2*e_c+e_c_12_minus)/(alpha_p2);
    auto C_11 = 1.0/(4.0*V_0)*(der11+der12)*Main_constant;

    auto C_12 = 1.0/(4.0*V_0)*(der11-der12)*Main_constant;

    //B

    double B_plus[]= {1+alpha,1+alpha,1+alpha};
    double B_minus[] = {1-alpha,1-alpha,1-alpha};

    auto B_plus_energy = E_f(this->Pool, this->Min_len, array_mr,B_plus,3,temp_arr)/size;
    auto B_minus_energy = E_f(this->Pool, this->Min_len, array_mr,B_minus,3,temp_arr)/size;


    auto B = 1.0/(9.0*V_0)*(B_plus_energy-2*e_c+B_minus_energy)/(alpha_p2)*Main_constant;

    //C44



    double matrix_c_44_plus[]= {1.0,alpha,alpha,1.0,1.0/(1-alpha_p2)};
    double matrix_c_44_minus[]= {1.0,-alpha,-alpha,1.0,1.0/(1+alpha_p2)};

    auto e_c_44_plus = E_f(this->Pool, this->Min_len,  array_mr,matrix_c_44_plus,5,temp_arr)/size;
    auto e_c_44_minus = E_f(this->Pool, this->Min_len,  array_mr,matrix_c_44_minus,5,temp_arr)/size;
    auto C_44 = 1.0/(4*V_0)*(e_c_44_plus - 2*e_c + e_c_44_minus)/(alpha_p2)*Main_constant;


    this->Pool[0].type = atom_kernel::B;
    auto e_AB = E_f(this->Pool, this->Min_len, array_mr, matrix_E_0, 3, temp_arr);
    auto e_sol = e_AB - e_c*this->Pool.size() - this->e_coh_B + e_c;
    //std::cout<<"e_AB = "<<e_AB<<"e_c2 =  "<<e_c*this->Pool.size()<<"e_coh_B = "<<e_coh_B<<"e_c = "<<e_c<<std::endl;
    this->Pool[0].type = atom_kernel::A;

    if(this->vacuum == 'x'){
        array_mr[0] *=2;
    }
    else if(this->vacuum =='y'){
        array_mr[1] *=2;
    }
    else {
        array_mr[2] *=2;
    }

    auto e_surf_in = E_f(this->Pool, this->Min_len, array_mr, matrix_E_0, 3, temp_arr);

    this->Pool[this->id_1].type = atom_kernel::B;

    auto e_adatom_in =  E_f(this->Pool, this->Min_len, array_mr, matrix_E_0, 3, temp_arr);

        
    this->Pool[this->id_2].type =atom_kernel::B;

    auto e_dim_surf_in = E_f(this->Pool, this->Min_len, array_mr, matrix_E_0, 3, temp_arr);
        

    auto e_in_dim = (e_dim_surf_in*-e_surf_in)-2*(e_adatom_in - e_surf_in);


    this->Pool[this->id_1].type = atom_kernel::A;
    this->Pool[this->id_2].type = atom_kernel::A;

    auto e_surf_on = E_f(this->Pool, this->Min_len, array_mr, matrix_E_0, 3, temp_arr);


    this->Pool.push_back(Atom(this->point1_3,atom_kernel::B));


    auto e_adatom_on = E_f(this->Pool, this->Min_len, array_mr, matrix_E_0, 3, temp_arr);


    this->Pool.push_back(Atom(this->point2_3,atom_kernel::B));


        
    auto e_dim_surf_on = E_f(this->Pool, this->Min_len, array_mr, matrix_E_0, 3, temp_arr);
        

    auto e_on_dim = (e_dim_surf_on*-e_surf_on)-2*(e_adatom_on - e_surf_on);

    this->Pool.pop_back();
    this->Pool.pop_back();

    if(flag)
        std::cout<<"----params :"<<e_c<<" "<<B<<" "<<C_11<<" "<<C_12<<" "<<C_44<<" "<<e_sol<<" "<<e_in_dim<<" "<<e_on_dim<<std::endl;
    auto result = this->error_function(e_c,B,C_11,C_12,C_44,e_sol,e_in_dim,e_on_dim);

    return result;
//calculate all energy params


}




