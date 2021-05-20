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
    std::cout << "\n\nc * d: " << c * d;

    /* BigInt f;
    f.reserveVectorCapacity(2);
    f.pushLast(50000);
    f.pushLast(13);

    BigInt res2;
    res2.reserveVectorCapacity(3);
    res2.pushLast(0);
    res2.pushLast(100000);
    res2.pushLast(26); */

    //std::cout << "\n\nres2 * f " << res2 * f;

    /* BigInt zero;
    zero.reserveVectorCapacity(4);
    zero.pushLast(0);
    zero.pushLast(0);
    zero.pushLast(0);
    zero.pushLast(0);

    std::cout << "\noperator <" << (zero > ZERO); */
    
    return 0;
}

#endif