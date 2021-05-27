#include <iostream>
#include "BigInt.hpp"


int main() {
    
    //std::cout << a + b;

    BigInt c;
    c.reserveVectorCapacity(2);
    c.pushLast(240000);
    c.pushLast(134);
    
    BigInt d;
    d.reserveVectorCapacity(2);
    d.pushLast(0);
    d.pushLast(2);


    //std::cout << "\n\nttt:\n" <<  multiplyByNum(c, 0);
    //std::cout << '\n' << multiplyByNum(c, 2);
    //std::cout << "\n\nc * d: " << c * d.negate();

    BigInt s("5 0");
    BigInt power(2);
    
    std::cout << fastPow(s, power);
    std::cout << '\n' << power[power.size() - 1];
    return 0;
}

