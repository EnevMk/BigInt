#include "BigInt.hpp"

void BigInt::validate(long long num) {
    int len = 1;
    long long copy = num;
    
    while (copy / BASE != 0) {
        ++len;
        copy /= BASE;
    }
    this->bigNum.reserve(len);

    int del = 1;

    for (int i = len - 1; i >= 0; --i) {
        this->bigNum[i] = (num % BASE);
        del *= 10;
        num = num / BASE * BASE / del;
              
    }
}

BigInt::BigInt():bigNum() {

}

/* BigInt::BigInt(int size_):bigNum(size_) {
    
} */

BigInt::BigInt(long long num):bigNum() {
    validate(num);
    //bigNum.push(num);
}

BigInt::BigInt(const Vector<long long> &v) {
    bigNum = v;
}

BigInt& BigInt::operator=(const BigInt &obj) {
    bigNum = obj.bigNum;
}

BigInt operator+(const BigInt &obj1, const BigInt &obj2) {

    int fstLen = obj1.bigNum.maxCapacity();
    int sndLen = obj2.bigNum.maxCapacity();
    int newSize = (fstLen < sndLen) ? sndLen : fstLen;
    newSize++;
    
    //BigInt *res = new BigInt(newSize);
    BigInt res;
    res.bigNum.reserve(newSize);
    
    long long addend1;
    long long addend2;
    int remainder = 0;
    for (int i = newSize - 1; i >= 0; --i) {

        if (fstLen - 1 < 0) {
            addend1 = 0;
        }
        else {
            addend1 = obj1.bigNum[fstLen - 1];
        }

        if (sndLen - 1 < 0) {
            addend2 = 0;
        }
        else {
            addend2 = obj2.bigNum[sndLen - 1];
        }
        
        if (sndLen - 1 < 0) {
            addend2 = 0;
        }
        //std::cout << "i: " << i << "in foo: " << addend1 << ' ' << addend2 << '\n';
        
        long long sum = addend1 + addend2;
        res.bigNum[i] = sum % BASE + remainder;
        //res->bigNum.push(sum % BASE + remainder);

        long long rem = sum / BASE;

        if (rem) {
            remainder = 0;
            remainder += rem;
        }
        else {
            remainder = 0;
        }

        fstLen--;
        sndLen--;
    }

    int i = 0;

    while (res.bigNum[i] == 0) {
        ++i;
    }
    if (i != 0) {
        Vector<long long> resVec;
        int fixedSize = newSize - i; 
        resVec.reserve(fixedSize);

        for (int j = 0; j < fixedSize; ++j) {
            resVec.push(res.bigNum[j + i]);
            //resVec[j] = res.bigNum[j + i];
        }
        res.bigNum = resVec;
    }
    
    return res;
}

BigInt operator-(const BigInt &obj1, const BigInt &obj2) {

    int fstLen = obj1.bigNum.maxCapacity();
    int sndLen = obj2.bigNum.maxCapacity();
    int newSize = (fstLen < sndLen) ? sndLen : fstLen;

    BigInt res;
    res.bigNum.reserve(newSize);

    long long minuend;
    long long subtrahend;

    res.bigNum.null();

    for (int i = newSize - 1; i >= 0; --i) {

        minuend = (fstLen - 1 < 0) ? 0 : obj1.bigNum[fstLen - 1];
        subtrahend = (sndLen - 1 < 0) ? 0 : obj2.bigNum[fstLen - 1];

        (minuend < subtrahend) ? res.bigNum[i - 1]--, minuend += BASE : 1;

        res.bigNum[i] += minuend - subtrahend;

        fstLen--;
        sndLen--;
    }

    return res;
}

std::ostream& operator<<(std::ostream &os, const BigInt &obj) {
    for (int i = 0; i < obj.bigNum.maxCapacity(); ++i) {
        os << obj.bigNum[i] << ' ';
    }

    return os;
}