#include <iostream>
#include "BigInt.hpp"

int main() {
    
    BigInt a = 999999999;
    BigInt b = 999999999;
    BigInt w = 2;

    BigInt z = 2000000001;
               //999 999 999
               //10
               //11
               //1 999 999 999
               //20
               //21
    
    BigInt c = a + b;

    
    BigInt f = c + w;

    Vector <long long> bign;
    bign.push(23000);
    bign.push(500000000);

    BigInt g = bign;
    BigInt g2 = g + g;

    std::cout << "a: " << a
    << "\nb: " << b
    << "\nc: " << (c)
    << "\nf: " << f
    << "\nz: " << z + z
    << "\ng: " << g
    << "\ng + g: " << g2
    << "\n g2 - g: " << g2 - g
    << "\na - w: " << a - w;

    //BigInt y = z - a;
    std::cout << '\n' << z.bigNum.size() << '\n' << z.bigNum.maxCapacity();
    std::cout << '\n' << z.bigNum[0] << ' ' << z.bigNum[1];
    
    //delete c;
    return 0;
}