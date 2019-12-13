

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
