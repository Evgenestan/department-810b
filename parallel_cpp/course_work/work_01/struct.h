
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

    ParamsArray(){size = 3;}
    ParamsArray(int _size){size = _size;}
    ParamsArray(const ParamsArray & in){
        this->size = in.size;
        this->vec = in.vec;
            this->arr[1][1] = in.arr[1][1];
            this->arr[1][2] = in.arr[1][2];
            this->arr[2][2] = in.arr[2][2];
    }


    void convert_to_vector(){
        
        //for(int i = 1; i<=this->size; ++i){

        this->vec.push_back(this->arr[1][1].A0);
        this->vec.push_back(this->arr[1][1].A1);
        this->vec.push_back(this->arr[1][1].p0);
        this->vec.push_back(this->arr[1][1].q0);
        this->vec.push_back(this->arr[1][1].qsi);
        this->vec.push_back(this->arr[1][2].A0);
        this->vec.push_back(this->arr[1][2].A1);
        this->vec.push_back(this->arr[1][2].p0);
        this->vec.push_back(this->arr[1][2].q0);
        this->vec.push_back(this->arr[1][2].qsi);
        this->vec.push_back(this->arr[2][2].A0);
        this->vec.push_back(this->arr[2][2].A1);
        this->vec.push_back(this->arr[2][2].p0);
        this->vec.push_back(this->arr[2][2].q0);
        this->vec.push_back(this->arr[2][2].qsi);

       // }
    }

    void receive_from_vector(){

        this->arr[1][1] = Params(
                this->vec[0],
                this->vec[1],
                this->vec[2],
                this->vec[3],
                this->vec[4]
                );
        this->arr[1][2] = Params(
                this->vec[5],
                this->vec[6],
                this->vec[7],
                this->vec[8],
                this->vec[9]
                );
       // if(this->size == 3){
            this->arr[2][2] = Params(
                    this->vec[10],
                    this->vec[11],
                    this->vec[12],
                    this->vec[13],
                    this->vec[14]
                    );
        //}



    }
};

#endif
