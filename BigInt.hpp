#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include "Vector.hpp"

#define BASE (long long)1000000000


class BigInt {

private:
    
    friend BigInt multiplyByNum(const BigInt &obj, long long num);

    Vector<long long> bigNum;
public:
    
    
    BigInt();
    BigInt(long long num);
    //BigInt(int size_);
    BigInt(const Vector<long long> &v);
    BigInt(const BigInt &obj);
    void reserveVectorCapacity(int n);
    void pushLast(long long digit);
    bool operator==(const BigInt &obj) const;
    //long long operator[](size_t ind) const;
    int size() const;
    const Vector<long long>& getVector() const;
    const long long operator[](size_t i) const;
    bool operator>(const BigInt &obj) const;
    bool operator<(const BigInt &obj) const;
    BigInt& operator=(const BigInt &obj);
    BigInt negate() const;
    
    friend std::ostream& operator<<(std::ostream &os, const BigInt &obj);

    BigInt operator+(const BigInt &obj) const;
    BigInt operator-(const BigInt &obj) const;
    BigInt operator*(const BigInt &obj) const;

    /* friend BigInt operator+(const BigInt &obj1, const BigInt &obj2);
    friend BigInt operator-(const BigInt &obj1, const BigInt &obj2);
    friend BigInt operator*(const BigInt &obj1, const BigInt &obj2); */
};

#endif