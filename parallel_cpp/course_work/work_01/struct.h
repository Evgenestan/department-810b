
#ifndef STRUCT_H
#define STRUCT_H

//stage 2

#include <vector>

enum atom_kernel {
    A=1,B=2
};


struct Atom{
vector vec;
int type;
Atom(vector _vec, int _type): vec(_vec), type(_type){}


};



struct Params{
    double A0;
    double A1;
    double p0;
    double q0;
    double qsi;
    Params(){}
    Params(double _A0, double _A1, double _p0, double _q0, double _qsi): A0(_A0),A1(_A1), p0(_p0),q0(_q0),qsi(_qsi){}
    Params(const Params &params){
         this->A0 = params.A0;
         this->A1 = params.A1;
         this->p0 = params.p0;
         this->q0 = params.q0;
         this->qsi = params.qsi;
    }
    //input params
};



struct ParamsArray{

    int size;

    Params arr [3][3];

    std::vector<double> vec;

    ParamsArray(){size = 2;}
    ParamsArray(int _size){size = _size;}

    
   

    void convert_to_vector(){
        
    for(int i = 1; i<=this->size; ++i){

        this->vec.push_back(this->arr[1][i].A0);
        this->vec.push_back(this->arr[1][i].A1);
        this->vec.push_back(this->arr[1][i].p0);
        this->vec.push_back(this->arr[1][i].q0);
        this->vec.push_back(this->arr[1][i].qsi);

    }
    }

    void receive_from_vector(){

        for(int i = 1; i<=this->size; ++i){

            this->arr[1][i] = Params(this->vec[0+5*(i-1)],this->vec[1+5*(i-1)],this->vec[2+5*(i-1)],this->vec[3+5*(i-1)],this->vec[4+5*(i-1)]);

        }

    }


    /*void change_value_matrix(int i,double value){

        
        this->>arr[1][i>=5 ? 2 : 1] = value;
    }*/
};

#endif
