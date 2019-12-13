#include <iostream>
#include "vector.h"
#include "nlohmann/json.hpp"
#include "fstream"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <tbb/parallel_for.h>


//#include "tbb/blocked_range.h"
//#include <tbb/parallel_for.h>


struct Config{

    vector vec;
    double A;
    double eps;
    double p;
    double q;
    Config(vector _vec, double _A, double _eps, double _q, double _p) :vec(_vec),A(_A), eps(_eps), q(_q), p(_p) {}

    
};


//stage 2

struct Atom{
vector vec;
int type;
Atom(vector _vec, int _type): vec(_vec), type(_type){}

};


struct Params{
    double A0;
    double A1;
    double r0;
    double p0;
    double q0;
    double qsi;
    Params(){}
    Params(double _A0, double _A1, double _r0, double _p0, double _q0, double _qsi): A0(_A0),A1(_A1), r0(_r0), p0(_p0),q0(_q0),qsi(_qsi){}
    Params(const Params &params){
         A0 = params.A0;
    }
    //input params
};


enum atom_kernel {
    A=1,B=2
};


struct ParamsArray{
    //Params arr[3][3]= {{1,2},{1,2}};
    


    Params arr [2][2];
    ParamsArray(){


       // Params param(1.0,2.0,3.0,4.0,5.0,6.0);     
        arr[A][A] = Params(1.0,2.0,3.0,4.0,5.0,6.0);
    }
    
};

double distance(const vector& lv,const vector& rv, const double & length, const double * matrix, int size =3){
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


bool operator == ( const Config & left, const Config & right ){
        return  (left.vec == right.vec &&  left.A == right.A && left.eps == right.eps && left.p == right.p && left.q == right.q);

    }


double E_b(
    Config const  &elem,
    std::vector <Config> const &field,
    double const &min_len,
    const double & multy,
    const double* matrix,
    const int & size){

    double energy = 0;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{

            energy+= pow(i.eps,2)*exp(-2*i.q*(distance( i.vec,elem.vec, multy, matrix,size)/min_len-1));
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
    const double * matrix,
    const int & size){

    double energy = 0;
    for(auto i : field){
        if(elem == i)
            continue;
            
        else{

            energy+= i.A*exp(-1*i.p*(distance(i.vec, elem.vec,  multy, matrix, size)/min_len-1));

        }
         
    }
    //std::cout<<"E_r "<<energy<<std::endl;

    return energy;
}


double E_c(
    std::vector <Config> const &field,
    double const &min_len,
    const double & multy,
    const double *matrix,
    const int & size){

    double Result_energy = 0;
    
    for(auto i: field){
        Result_energy += E_b(i,field,min_len, multy,matrix,size) + E_r(i,field,min_len, multy,matrix,size);
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








    /*const size_t SIZE = 10000000;
    std::vector<double> myArray(SIZE);

	// Запуск параллельного алгоритма for
	tbb::parallel_for(tbb::blocked_range<size_t>(0, SIZE),
	// Лямбда-функция
	[&myArray](const tbb::blocked_range<size_t> &r)
	{
		for (size_t i = r.begin(); i != r.end(); i++)
		    std::cout<<myArray[i]<<std::endl;
	});*/



    return 0;
}










