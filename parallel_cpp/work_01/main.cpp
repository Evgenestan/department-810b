#include <iostream>
#include "vector.h"

int main()
{
    auto vector1 = vector(1,22,3);
    auto vector2 = vector(33,44,5);

    std::cout << vector1;
    std::cout << vector2;

    std::cout << length(vector1) << "\n";
    std::cout << length(vector2) << "\n";

    auto sum = vector1 + vector2;
    auto diff = vector1 - vector2;
    auto mult = vector1 *5;
    auto div = vector1 / 5;

    std::cout << sum;
    std::cout << diff;
    std::cout << mult;
    std::cout << div;

    return 0;
}