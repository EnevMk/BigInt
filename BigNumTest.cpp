#include <iostream>
#include "BigInt.hpp"

#ifndef ZERO
#define ZERO BigInt(0)

int main() {
    
    BigInt a;
    a.reserveVectorCapacity(2); // _ _
    a.pushLast(300000000); // _ 0
    a.pushLast(-17); // -17 0

    BigInt b;
    b.reserveVectorCapacity(2);
    b.pushLast(300000000);
    b.pushLast(7);

    //std::cout << a + b;

    BigInt c;
    c.reserveVectorCapacity(2);
    c.pushLast(240000);
    c.pushLast(134);
    
    BigInt d;
    d.reserveVectorCapacity(2);
    d.pushLast(0);
    d.pushLast(2);

    BigInt test1 = multiplyByNum(c, 0);
    BigInt test2;
    test2.reserveVectorCapacity(3);
    test2.pushLast(0);
    test2.pushLast(480000);
    test2.pushLast(268);


    //std::cout << "\n\nttt:\n" <<  multiplyByNum(c, 0);
    //std::cout << '\n' << multiplyByNum(c, 2);
    std::cout << "\n\nc * d: " << c * d.negate();

    
    
    return 0;
}

#endif