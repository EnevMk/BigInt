#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include "Vector.hpp"

#define BASE (long long)1000000000


class BigInt {

private:
    
    long long calculateDigitAddition(const BigInt &obj, int first, int second, long long &rem) const;
    long long calculateDigitSubtraction(const BigInt &obj, int first, int second, BigInt &result, int index) const;
    BigInt operatorHandlerAddition(const BigInt &obj) const;
    BigInt operatorHandlerSubtraction(const BigInt &obj) const;

    Vector<long long> bigNum;
public:
    
    friend BigInt multiplyByNum(const BigInt &obj, long long num); // multiplies a BigInt by a long long 
    
    BigInt();
    BigInt(long long num);
    //BigInt(int size_);
    BigInt(const Vector<long long> &v);
    BigInt(const BigInt &obj);
    
    void reserveVectorCapacity(int n);
    void pushLast(long long digit); // pushes a long long to the last free position of the vector
    bool operator==(const BigInt &obj) const;
    bool operator!=(const BigInt &obj) const;
    //long long operator[](size_t ind) const;
    int size() const;
    const Vector<long long>& getVector() const;
    const long long operator[](size_t i) const; // returning a digit of the BigInt on ith index
    bool operator>(const BigInt &obj) const;
    bool operator<(const BigInt &obj) const;
    bool operator>=(const BigInt &obj) const;
    bool operator<=(const BigInt &obj) const;
    BigInt& operator=(const BigInt &obj);
    BigInt negate() const; // returns the negated BigInt number
    
    friend std::ostream& operator<<(std::ostream &os, const BigInt &obj);

    BigInt operator+(const BigInt &obj) const;
    BigInt operator-(const BigInt &obj) const;
    BigInt operator*(const BigInt &obj) const;

    /* friend BigInt operator+(const BigInt &obj1, const BigInt &obj2);
    friend BigInt operator-(const BigInt &obj1, const BigInt &obj2);
    friend BigInt operator*(const BigInt &obj1, const BigInt &obj2); */
};

#endif