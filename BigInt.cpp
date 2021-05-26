#include "BigInt.hpp"
#define ZERO BigInt(0)


BigInt::BigInt():bigNum() {

}

BigInt::BigInt(const String &value) {

    //BigInt s("12 350000 0");
    int countSpaces = 0;
    for (int i = 0; i < value.size(); ++i) {
        (value[i] == ' ') ? countSpaces++ : 1;
    }
    
    int size = countSpaces + 1;
    this->reserveVectorCapacity(size);
    //std::cout << "Reserved space for : " << size << " digits\n";

    int startIndex = 0, endIndex = -1;
    for (int i = 0; i < value.size() + 1; ++i) {

        if (value[i] == ' ' || value[i] == '\0') {
            this->bigNum.push(map(value.subStr(startIndex, endIndex), charToll));
            //std::cout << '\n' << startIndex << ' ' << endIndex << '\n';
            startIndex = endIndex + 2;
        }
        endIndex++;
    }

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
    //return bigNum == obj.bigNum;
    for (int i = 0; i < this->bigNum.size(); ++i) {

        if (this->bigNum[i] != obj.bigNum[i]) {
            return false;
        }
    }
    return this->size() == obj.size();
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
    
    BigInt negated = *this;

    negated.bigNum[0] = -1 * this->bigNum[0];
    return negated;
}

void BigInt::cutFirstNull() {

    if (bigNum[0] == 0) {
        
        long long *newArr = new long long[bigNum.capacity - 1];
        for (int i = 0; i < bigNum.capacity - 1; ++i) {
            newArr[i] = bigNum.arr[i + 1];
        }
        bigNum.capacity--;
        bigNum.current = bigNum.capacity;
        delete[] bigNum.arr;
        bigNum.arr = newArr;
    }
}

void BigInt::null() {
    for (int i = 0; i < this->bigNum.maxCapacity(); ++i) {
        bigNum[i] = 0;
    }
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

    res.bigNum.popBack();
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

    (minuend < subtrahend) ? result.bigNum[index - 1]--, minuend += BASE : 1;

    long long digit = minuend - subtrahend + result.bigNum[index];

    return digit;
}

BigInt BigInt::operator-(const BigInt &obj) const {
    
    BigInt res = operatorHandlerSubtraction(obj);
    if (res != 0) return res;

    int fstLen = this->size(), sndLen = obj.size();
    int newSize = (fstLen < sndLen) ? sndLen : fstLen;

    res.reserveVectorCapacity(newSize);
    res.null();
    res.bigNum.popBack();

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
            
            numbersVector[i].bigNum.push(0);
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
        BigInt temp = multiplyByNum(*this, obj.bigNum[i]);
        
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

    if (remainder) result.pushLast(remainder);

}

BigInt multiplyByNum(const BigInt &obj, long long num) {
    int bigIntLen = obj.size();
    int maxLen = bigIntLen + 1;
    //int diff = maxLen - bigIntLen;

    BigInt res;
    res.reserveVectorCapacity(maxLen);

    res.null();
    obj.calculateBigIntByNum(bigIntLen, obj, res, num);

    res.cutFirstNull();
    return res;
}

std::ostream& operator<<(std::ostream &os, const BigInt &obj) {
    for (int i = 0; i < obj.bigNum.size(); ++i) {
        os << obj.bigNum[i] << ' ';
    }

    return os;
}