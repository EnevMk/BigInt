#include "BigInt.hpp"
#define ZERO BigInt(0)


BigInt::BigInt():bigNum() {

}

BigInt::BigInt(long long num):bigNum() {
    if (num < BASE) {
        
        pushLast(num);
    }
}

BigInt::BigInt(const Vector<long long> &v) {
    bigNum = v;
}

BigInt::BigInt(const BigInt &obj) {
    bigNum = obj.bigNum;
}

BigInt& BigInt::operator=(const BigInt &obj) {
    bigNum = obj.bigNum;
    return *this;
}

bool BigInt::operator==(const BigInt &obj) const {
    return bigNum == obj.bigNum;
}

void BigInt::reserveVectorCapacity(int n) {
    this->bigNum.reserve(n);
    //this->bigNum.null();
}

void BigInt::pushLast(long long digit) {
    int lastInd = bigNum.getLastFreeIndex();
    bigNum.push(digit, lastInd);
    bigNum.setLastFreeIndex(--lastInd);
}

int BigInt::size() const {
    return bigNum.size();
}

const long long BigInt::operator[](size_t i) const {
    return bigNum[i];
}

const Vector<long long>& BigInt::getVector() const {
    return bigNum;
}

BigInt BigInt::negate() const {

    int prevLen = this->size();

    BigInt negated = *this;

    negated.bigNum[0] = -1 * this->bigNum[0];
    return negated;
}

bool BigInt::operator>(const BigInt &obj) const {

    if (this->getVector()[0] < 0 && obj.getVector()[0] >= 0) {
        
        return false;
    }

    else if (this->getVector()[0] >= 0 && obj.getVector()[0] < 0) {
        
        return true;
    }

    else if (this->getVector()[0] < 0 && obj.getVector()[0] < 0) {
        
        return !(this->negate() > obj.negate());
    }

    int thisLen = this->size();
    int objlen = obj.size();

    if (thisLen != objlen) {
        return (thisLen > objlen) ? true : false;
    }

    int i;
    for (i = 0; i < thisLen; ++i) {

        if (this->bigNum[i] == obj[i]) continue;

        return this->bigNum[i] > obj[i];
    }
    return false;
}

bool BigInt::operator<(const BigInt &obj) const {
    return !(*this > obj);
}

BigInt BigInt::operator+(const BigInt &obj) const {
    BigInt res;

    if (*this > ZERO && obj < ZERO) {
        
        res = *this - obj.negate();
        return res;
    }
    else if (*this < ZERO && obj < ZERO) {

        res = (this->negate() + obj.negate()).negate();
        return res;
    }/* 
    else if (*this < ZERO && obj > ZERO) {
        return obj - this->negate();
    } */

    int fstLen = this->size();
    int sndLen = obj.size();

    if (fstLen == 0) {
        res = obj;
        return res;
    }
    else if (sndLen == 0) {
        res = *this;
        return res;
    }

    int newSize = (fstLen < sndLen) ? sndLen + 1: fstLen + 1;

    res.reserveVectorCapacity(newSize);
    res.bigNum.null();

    long long addend1;
    long long addend2;
    long long remainder = 0;
    for (int i = newSize - 1; i >= 0; --i) {

        addend1 = (fstLen - 1 < 0) ? 0 : (*this)[fstLen - 1];
        addend2 = (sndLen - 1 < 0) ? 0 : obj[sndLen - 1];
        
        long long sum = addend1 + addend2;
        long long digit = sum % BASE + remainder;

        res.pushLast(digit);

        long long rem = sum / BASE;

        remainder = (rem) ? rem : 0;

        fstLen--;
        sndLen--;
    }

    res.bigNum.cutFirstNull();

    return res;
}

BigInt BigInt::operator-(const BigInt &obj) const {
    BigInt res;
    
    if (*this < ZERO && obj < ZERO) {
        //return (this->negate() - (obj.negate())).negate();
        
        return obj.negate() - this->negate();
    }

    else if (*this < ZERO && obj > ZERO) {
        
        return (this->negate() + obj).negate();
    }

    else if (*this > ZERO && obj < ZERO) {
        return *this + obj.negate();
    }

    if (*this < obj) {
        res = obj - *this;
        //res.negate();
        //res = res.negate();
        return res.negate();
    }

    int fstLen =this->size();
    int sndLen = obj.size();
    int newSize = (fstLen < sndLen) ? sndLen : fstLen;

    res.reserveVectorCapacity(newSize);

    long long minuend;
    long long subtrahend;

    res.bigNum.null();

    for (int i = newSize - 1; i >= 0; --i) {

        minuend = (fstLen - 1 < 0) ? 0 : (*this)[fstLen - 1];
        subtrahend = (sndLen - 1 < 0) ? 0 : obj[sndLen - 1];

        (minuend < subtrahend) ? res.bigNum[i - 1]--, minuend += BASE : 1;

        long long digit = minuend - subtrahend + res.bigNum[i];
        res.pushLast(digit);

        fstLen--;
        sndLen--;
    }

    res.bigNum.cutFirstNull();

    return res;
}

BigInt BigInt::operator*(const BigInt &obj) const {
    int fstLen = this->size();
    int sndlen = obj.size();

    int newSize = fstLen + sndlen;
    
    BigInt res;
    res.reserveVectorCapacity(newSize);
    res.bigNum.null();

    Vector<BigInt> prods;
    prods.reserve(sndlen);

    for (int i = sndlen - 1; i >= 0; i--) {
        BigInt temp = multiplyByNum(*this, obj.bigNum[i]);
        
        prods.push(temp);
    }
    
    for (int i = 0; i < sndlen; ++i) {

        int newCapacity = prods[i].size() + i;
        
        if (i != 0) prods[i].reserveVectorCapacity(newCapacity);

        for (int j = 0 ; j < i; ++j) {
            
            prods[i].bigNum.push(0);
        }
        res = res + prods[i];
    }

    return res;
}

BigInt multiplyByNum(const BigInt &obj, long long num) {
    int bigIntLen = obj.size();
    int maxLen = bigIntLen + 1;
    int diff = maxLen - bigIntLen;

    BigInt res;
    res.reserveVectorCapacity(maxLen);

    res.bigNum.null();
    int len = maxLen;

    long long rem = 0;
    for (int i = bigIntLen - 1; i >= 0; --i) {
        
        long long digit = res.bigNum[i + diff] + (obj.bigNum[i] * num) % BASE;
        res.pushLast(digit + rem);

        rem = (obj.bigNum[i] * num) / BASE;
        
    }

    if (rem) {
        res.pushLast(rem);
    }

    res.bigNum.cutFirstNull();
    return res;
}

std::ostream& operator<<(std::ostream &os, const BigInt &obj) {
    for (int i = 0; i < obj.bigNum.size(); ++i) {
        os << obj.bigNum[i] << ' ';
    }

    return os;
}