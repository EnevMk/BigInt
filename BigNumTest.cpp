#include <iostream>
#include "BigInt.hpp"

#ifndef ZERO
#define ZERO BigInt(0)

int main() {
    
    BigInt a;
    a.reserveVectorCapacity(2);
    a.pushLast(240000);
    a.pushLast(134);
    
    BigInt b;
    b.reserveVectorCapacity(2);
    b.pushLast(0);
    b.pushLast(2);

    std::cout << a * b;
    
    return 0;
}

#endif