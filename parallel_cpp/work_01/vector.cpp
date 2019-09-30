//
// Created by vasil on 9/24/19.
//

#include "vector.h"
#include <cmath>

vector& vector::operator+=(const vector & vec)
{
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;

    return *this;
}

vector& vector::operator*=(double number)
{
    this->x *= number;
    this->y *= number;
    this->z *= number;

    return *this;
}

vector operator+(const vector& lhs, const vector& rhs)
{
    auto result = vector();

    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    result.z = lhs.z + rhs.z;

    return result;
}

vector operator-(const vector& lhs, const vector& rhs)
{
    auto result = vector();

    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    result.z = lhs.z - rhs.z;

    return result;
}

vector operator* (const vector& lhs,double rhs)
{
    auto result = vector();

    result.x = lhs.x * rhs;
    result.y = lhs.y * rhs;
    result.z = lhs.z * rhs;

    return result;
}

vector operator/ (const vector& lhs,double rhs)
{
    auto result = vector();

    result.x = lhs.x / rhs;
    result.y = lhs.y / rhs;
    result.z = lhs.z / rhs;

    return result;
}

double length(const vector& v)
{
    double result = 0;

    result += pow(v.x,2);
    result += pow(v.y,2);
    result += pow(v.z,2);

    result = sqrt(result);

    return  result;
}

std::ostream& operator << (std::ostream& os,const vector& vec)
{
    os << "x : " << vec.x << " ";
    os << "y : " << vec.y << " ";
    os << "z : " << vec.z <<"\n";

    return os;
}
