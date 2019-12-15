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
    vector(const vector & cp): x(cp.x),y(cp.y),z(cp.z){}
    double scalar(const vector& left);
    friend std::ostream& operator<<(std::ostream&,const vector&);
};

vector operator+ (const vector&,const vector&);
vector operator- (const vector&,const vector&);
vector operator* (const vector&, double rhs);
vector operator/ (const vector&, double rhs);


double length(const vector&);
double distance(const vector&,const vector&);


#endif 
