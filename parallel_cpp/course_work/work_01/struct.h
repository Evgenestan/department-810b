
#ifndef STRUCT_H
#define STRUCT_H

//stage 2



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

    Params arr [2][2];
    ParamsArray(){}
    
};

#endif
