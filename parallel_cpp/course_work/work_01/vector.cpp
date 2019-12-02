

#include "vector.h"
#include <cmath>
#include <iostream>


vector& vector::operator+=(const vector & vec){
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;

    return *this;
}

double vector::operator[](const int i){
    if(i == 0){
        return this->x;
    }
    else if (i == 1){
        return this->y;
    }
    else if(i == 2){
        return this->z;
    }
    else{
        throw std::logic_error("There is no such a parameter");
    }

}

bool operator==(const vector & vec1, const vector & vec2){
    if(vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z)
        return true;
    else return false;
}

vector& vector::operator*=(double number){
    this->x *= number;
    this->y *= number;
    this->z *= number;

    return *this;
}

vector operator+(const vector& lhs, const vector& rhs){

    return vector(lhs.x + rhs.x,lhs.y + rhs.y,lhs.z + rhs.z);

}

vector operator-(const vector& lhs, const vector& rhs){
    auto result = vector();

    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    result.z = lhs.z - rhs.z;

    return result;
}

vector operator* (const vector& lhs,double rhs){
    auto result = vector();

    result.x = lhs.x * rhs;
    result.y = lhs.y * rhs;
    result.z = lhs.z * rhs;

    return result;
}

vector operator/ (const vector& lhs,double rhs){
    auto result = vector();

    result.x = lhs.x / rhs;
    result.y = lhs.y / rhs;
    result.z = lhs.z / rhs;

    return result;
}

double vector::scalar(const vector& left){
    try
    {
        double sum = 0;
        for(int i =0; i < 3;i++){
            sum = left.x*(this->x)+left.y*(this->y)+left.z*this->z;
        }
        return sum;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    

}

double distance(const vector& lv,const vector& rv, const double & length){
    //double cur_len = sqrt(pow(lv.x-rv.x,2)+pow(lv.y-rv.y,2)+pow(lv.z-rv.z,2));
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
    
    return sqrt(x_r*x_r+y_r*y_r+z_r*z_r);
    
}

double length(const vector& v){
    double result = 0;

    result += pow(v.x,2);
    result += pow(v.y,2);
    result += pow(v.z,2);
    result = sqrt(result);
    return  result;
}

std::ostream& operator << (std::ostream& os,const vector& vec){
    os << "x : " << vec.x << " ";
    os << "y : " << vec.y << " ";
    os << "z : " << vec.z <<"\n";

    return os;
}
