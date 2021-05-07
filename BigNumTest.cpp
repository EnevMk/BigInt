#include <iostream>
#include "BigInt.hpp"

#ifndef ZERO
#define ZERO BigInt(0)

int main() {
    
    /* BigInt a;
    a.reserveVectorCapacity(2);
    a.pushLast(240000);
    a.pushLast(134);
    
    BigInt b;
    b.reserveVectorCapacity(2);
    b.pushLast(0);
    b.pushLast(2);

    std::cout << a * b; */

    /* BigInt a;
    a.reserveVectorCapacity(2);
    a.pushLast(0);
    a.pushLast(1);
    BigInt a2;
    a2 = a.negate();

    BigInt b = 999999999;
    BigInt c = 1;
    BigInt b2 = b.negate();

    std::cout << "b2: " << b2;
    std::cout << "\n-a: " << a.negate();
    std::cout << "\n-b -a: " << b2 - a2; */

    BigInt g = 999999999;
    std::cout << g;
    
    return 0;
}

#endif