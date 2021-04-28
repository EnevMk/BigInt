#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include "Vector.hpp"

#define BASE 1000000000

class BigInt {

private:
    void validate(long long num);

public:
    Vector<long long> bigNum; //TODO: do it in dynamic memory
    
    BigInt();
    BigInt(long long num);
    //BigInt(int size_);
    BigInt(const Vector<long long> &v);
    void operator=(long long num);
    BigInt& operator=(const BigInt &obj);
    
    friend std::ostream& operator<<(std::ostream &os, const BigInt &obj);
    //friend std::ostream& operator<<(std::ostream &os, const BigInt *obj);
    friend BigInt operator+(const BigInt &obj1, const BigInt &obj2);
    friend BigInt operator-(const BigInt &obj1, const BigInt &obj2);
};

#endif