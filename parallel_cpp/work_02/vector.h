//
// Created by vasil on 9/24/19.
//

#ifndef WORK_01_VECTOR_H
#define WORK_01_VECTOR_H


#include <cmath>
#include <ostream>

struct vector{
    double x,y,z;
    vector& operator+=(const vector&);
    vector& operator*=(double);

    vector(){}
    vector(double _x, double _y, double _z):x(_x),y(_y),z(_z){}

    friend std::ostream& operator<<(std::ostream&,const vector&);
};

vector operator+ (const vector&,const vector&);
vector operator- (const vector&,const vector&);
vector operator* (const vector&, double rhs);
vector operator/ (const vector&, double rhs);

double length(const vector&);
double distance(const vector&,const vector&);


#endif //WORK_01_VECTOR_H
