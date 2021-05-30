#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include "String.hpp"
#include "Vector.hpp"

#define BASE (long long)1000000000
#define ZERO BigInt(0)


class BigInt {

private:
    
    long long calculateDigitAddition(const BigInt &obj, int first, int second, long long &rem) const;
    long long calculateDigitSubtraction(const BigInt &obj, int first, int second, BigInt &result, int index) const;
    void calculateBigIntByNum(int bigIntLen, const BigInt &obj, BigInt& result, long long num) const;

    BigInt operatorHandlerAddition(const BigInt &obj) const;
    BigInt operatorHandlerSubtraction(const BigInt &obj) const;
    BigInt operatorHandlerMultiplication(const BigInt &obj) const;

    void sumVectorsMultiplication(Vector<BigInt> &obj);

    Vector<long long> digitsContainer;
public:
    
    BigInt multiplyByNum(long long num) const; // multiplies a BigInt by a long long
    BigInt divideByTwo() const;
    
    BigInt();
    BigInt(const String &value);
    BigInt(long long num);
    BigInt(const Vector<long long> &v);
    BigInt(const BigInt &obj);
    BigInt& operator=(const BigInt &obj);
    
    const long long operator[](size_t i) const; // returning a digit of the BigInt on ith index

    bool operator==(const BigInt &obj) const;
    bool operator!=(const BigInt &obj) const;
    bool operator>(const BigInt &obj) const;
    bool operator<(const BigInt &obj) const;
    bool operator>=(const BigInt &obj) const;
    bool operator<=(const BigInt &obj) const;

    BigInt negate() const; // returns the negated BigInt number
    void cutFirstNull();
    void null();
    void reserveVectorCapacity(int n);
    void pushLast(long long digit); // pushes a long long to the last free position of the vector
    int size() const;
    const Vector<long long>& getVector() const;
    
    friend std::ostream& operator<<(std::ostream &os, const BigInt &obj);

    BigInt operator+(const BigInt &obj) const;
    BigInt operator-(const BigInt &obj) const;
    BigInt operator*(const BigInt &obj) const;
    //BigInt fastPow(const BigInt &obj) const;
    friend BigInt fastPow(const BigInt &number, const BigInt &power);
    BigInt fastPow(const BigInt &power) const;
};

inline long long charToll(char character) {

    return (character - '0');
}

inline long long mapStringToNumbers(const String &str, long long (*ptr)(char)) {
    long long num = 0;
    bool isNegative = false;

    int i = 0;
    if (str[0] == '-') {
        i = 1;
        isNegative = true;
    }
    
    for (i; i < str.size(); ++i) {
        num = num * 10 + (*ptr)(str[i]);
    }
    
    if (isNegative) {
        return num - 2 * num;
    }
    return num;
}

#endif