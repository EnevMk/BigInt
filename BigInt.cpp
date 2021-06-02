#include "BigInt.hpp"
#include <cassert>


bool isDigit(char character) {
    return character >= '0' && character <= '9';
}


BigInt::BigInt():digitsContainer() {

}

bool validate(const String &value) {
    for (int i = 0; i < value.size(); ++i) {
        if (value[i] == '-' && i == 0) {
            continue;
        }
        if (!isDigit(value[i]) && value[i] != ' ') {
            
            return false;
        }
    }
    return true;
}

BigInt::BigInt(const String &value) {

    String copy = value;
    copy.removeEndWhiteSpaces();
    copy.removeRepetitiveWhiteSpaces();

    assert(validate(copy));

    int countSpaces = 0;
    for (int i = 0; i < copy.size(); ++i) {
        (copy[i] == ' ') ? countSpaces++ : 1;
    }
    
    int size = countSpaces + 1;
    this->reserveVectorCapacity(size);

    int startIndex = 0, endIndex = -1;
    for (int i = 0; i < copy.size() + 1; ++i) {

        if (copy[i] == ' ' || copy[i] == '\0') {
            this->digitsContainer.push(mapStringToNumbers(copy.subStr(startIndex, endIndex), charToll));
            startIndex = endIndex + 2;
        }
        endIndex++;
    }

}

BigInt::BigInt(long long num):digitsContainer() {
    if (num < BASE) {
        
        pushLast(num);
    }
}

BigInt::BigInt(const Vector<long long> &v) {
    digitsContainer = v;
}

BigInt::BigInt(const BigInt &obj) {
    digitsContainer = obj.digitsContainer;
}

BigInt& BigInt::operator=(const BigInt &obj) {
    digitsContainer = obj.digitsContainer;
    return *this;
}

bool BigInt::operator==(const BigInt &obj) const {
    //return bigNum == obj.bigNum;
    for (int i = 0; i < this->digitsContainer.size(); ++i) {

        if (this->digitsContainer[i] != obj.digitsContainer[i]) {
            return false;
        }
    }
    return this->size() == obj.size();
}

void BigInt::reserveVectorCapacity(int n) {
    this->digitsContainer.reserve(n);
    //this->bigNum.null();
}

void BigInt::pushLast(long long digit) {
    int lastInd = digitsContainer.getLastFreeIndex();
    digitsContainer.push(digit, lastInd);
    digitsContainer.setLastFreeIndex(--lastInd);
}

void BigInt::push(long long digit) {
    digitsContainer.push(digit);
}

int BigInt::size() const {
    return digitsContainer.size();
}

const long long BigInt::operator[](size_t i) const {
    return digitsContainer[i];
}

const Vector<long long>& BigInt::getVector() const {
    return digitsContainer;
}

BigInt BigInt::negate() const {

    BigInt negated = *this;

    negated.digitsContainer[0] = -1 * this->digitsContainer[0];
    return negated;
}

void BigInt::cutFirstNull() {

    if (digitsContainer[0] == 0 && size() > 1) {

        digitsContainer.removeAtIndex(0);
        digitsContainer.shrink();
    }
}

void BigInt::null() {
    for (int i = 0; i < this->digitsContainer.maxCapacity(); ++i) {
        digitsContainer[i] = 0;
    }
}

BigInt BigInt::divideByTwo() const {

    BigInt res;
    res.reserveVectorCapacity(this->size());

    int remainder = 0;

    for (int i = 0; i < size(); ++i) {
        res.digitsContainer.push((*this)[i] / 2 + remainder);
        remainder = (*this)[i] % 2 * BASE / 2;
    }

    res.cutFirstNull();
    return res;
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

        if (this->digitsContainer[i] == obj[i]) continue;

        return this->digitsContainer[i] > obj[i];
    }
    return false;
}

bool BigInt::operator>=(const BigInt &obj) const {
    return (*this > obj || *this == obj);
}

bool BigInt::operator<=(const BigInt &obj) const {
    return (*this < obj || *this == obj);
}

bool BigInt::operator<(const BigInt &obj) const {
    return !(*this >= obj);
}

BigInt BigInt::operatorHandlerAddition(const BigInt &obj) const{

    if (*this > ZERO && obj < ZERO) {
        
        return *this - obj.negate();
    }
    else if (*this < ZERO && obj < ZERO) {
        
        return (this->negate() + obj.negate()).negate();
    }
    else if (*this < ZERO && obj > ZERO) {
        
        return (this->negate() - obj).negate();
    }
    
    return BigInt(0);
}

bool BigInt::operator!=(const BigInt &obj) const {
    return !(*this == obj);
}

long long BigInt::calculateDigitAddition(const BigInt &obj, int first, int second, long long &remainder) const {
    long long addend1, addend2;

    addend1 = (first - 1 < 0) ? 0 : (*this)[first - 1];
    addend2 = (second - 1 < 0) ? 0 : obj[second - 1];

    long long sum = addend1 + addend2;
    long long digit = sum % BASE + remainder;

    remainder = sum / BASE;

    return digit;
}

BigInt BigInt::operator+(const BigInt &obj) const {

    BigInt res = this->operatorHandlerAddition(obj);
    if (res != ZERO) return res;

    int fstLen = this->size(), sndLen = obj.size();

    if (fstLen == 0) return obj;
    if (sndLen == 0) return *this;

    int newSize = (fstLen < sndLen) ? sndLen + 1: fstLen + 1;

    res.digitsContainer.popBack();
    res.reserveVectorCapacity(newSize);
    res.null();
    
    long long remainder = 0;

    for (int i = newSize - 1; i >= 0; --i) {

        long long digit = calculateDigitAddition(obj, fstLen, sndLen, remainder);
        res.pushLast(digit);

        fstLen--;
        sndLen--;
    }

    res.cutFirstNull();
    return res;
}

BigInt BigInt::operatorHandlerSubtraction(const BigInt &obj) const {
    
    if (*this < ZERO && obj < ZERO) {
        return obj.negate() - this->negate();
    }

    else if (*this < ZERO && obj > ZERO) {
        
        return (this->negate() + obj).negate();
    }

    else if (*this > ZERO && obj < ZERO) {
        return *this + obj.negate();
    }

    if (*this < obj) {

        return (obj - *this).negate();
    }
    
    return BigInt(0);
}

long long BigInt::calculateDigitSubtraction(const BigInt &obj, int first, int second, BigInt &result, int index) const {

    long long minuend;
    long long subtrahend;

    minuend = (first - 1 < 0) ? 0 : (*this)[first - 1];
    subtrahend = (second - 1 < 0) ? 0 : obj[second - 1];
    
    (minuend < subtrahend) ? result.digitsContainer[index - 1]--, minuend += BASE : 1;

    //(minuend < subtrahend) ? result.digitsContainer[index - 1]--, minuend += BASE : 1;

    //this->digitsContainer[index - 1]--;

    long long digit = minuend - subtrahend + result.digitsContainer[index];

    return digit;
}

BigInt BigInt::operator-(const BigInt &obj) const {
    
    BigInt res = operatorHandlerSubtraction(obj);
    if (res != ZERO) return res;
    if (*this == obj) return ZERO;

    int fstLen = this->size(), sndLen = obj.size();
    int newSize = (fstLen < sndLen) ? sndLen : fstLen;
    
    res.digitsContainer.popBack();
    res.digitsContainer.shrink();

    res.reserveVectorCapacity(newSize);
    res.null();
    
    for (int i = newSize - 1; i >= 0; --i) {
        
        long long digit = calculateDigitSubtraction(obj, fstLen, sndLen, res, i);
        
        res.pushLast(digit);

        fstLen--;
        sndLen--;
    }
    
    res.cutFirstNull();
    return res;
}

BigInt BigInt::operatorHandlerMultiplication(const BigInt &obj) const {

    if (*this < 0 && obj > 0) {
        return (this->negate() * obj).negate();
    }

    else if (*this > 0 && obj < 0) {
        return (*this * obj.negate()).negate();
    }

    else if (*this < 0 && obj < 0) {
        return (this->negate() * obj.negate());
    }

    return BigInt(0);
}

void BigInt::sumVectorsMultiplication(Vector<BigInt> &numbersVector) {
    int count = numbersVector.size();

    for (int i = count - 1; i >= 0; i--) {

        int newCapacity = numbersVector[i].size() + i;

        if (i != 0) numbersVector[i].reserveVectorCapacity(newCapacity);

        for (int j = 0; j < i; ++j) {
            
            numbersVector[i].digitsContainer.push(0);
        }

        *this = *this + numbersVector[i];
    }
}

BigInt BigInt::operator*(const BigInt &obj) const {

    BigInt res = operatorHandlerMultiplication(obj);
    if (res != ZERO) return res;

    int fstLen = this->size(), sndlen = obj.size();
    int newSize = fstLen + sndlen;
    
    res.reserveVectorCapacity(newSize);
    
    Vector<BigInt> prods;
    prods.reserve(sndlen);

    for (int i = sndlen - 1; i >= 0; i--) {
        BigInt temp = this->multiplyByNum(obj.digitsContainer[i]);
        
        prods.push(temp);
    }

    res.sumVectorsMultiplication(prods);

    return res;
}

void BigInt::calculateBigIntByNum(int bigIntLen, const BigInt &obj, BigInt& result, long long num) const {

    int maxLen = bigIntLen + 1, diff = 1;

    long long remainder = 0;

    for (int i = bigIntLen - 1; i >= 0; --i) {
        
        long long digit = result[i + diff] + (obj[i] * num) % BASE;
        result.pushLast(digit + remainder);

        remainder = (obj[i] * num) / BASE;
    }

    if (remainder != 0) result.pushLast(remainder);
    else {
        result.pushLast(0);
    }

}

BigInt BigInt::multiplyByNum(long long num) const {

    if (num == 0) {
        return BigInt(0);
    }

    int bigIntLen = size();
    int maxLen = bigIntLen + 1;

    BigInt res;
    res.reserveVectorCapacity(maxLen);

    res.null();
    this->calculateBigIntByNum(bigIntLen, *this, res, num);

    res.cutFirstNull();
    return res;
}

BigInt BigInt::fastPow(const BigInt &power) const {

    if (power == ZERO) return BigInt(1);
    if (power == BigInt(1)) return BigInt(*this);

    if (power[power.size() - 1] % 2 == 0) {
        return (*this * *this).fastPow(power.divideByTwo());
    }

    return *this * (*this * *this).fastPow((power - BigInt(1)).divideByTwo());
}

std::ostream& operator<<(std::ostream &os, const BigInt &obj) {
    for (int i = 0; i < obj.digitsContainer.size(); ++i) {
        os << obj.digitsContainer[i] << ' ';
    }

    return os;
}