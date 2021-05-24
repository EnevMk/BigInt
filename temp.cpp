#include <iostream>

#include "String.hpp"
#include "BigInt.hpp"

/* long long charToll(char character) {
    return (character - '0');
}

long long map(const String &str, long long (*ptr)(char)) {
    long long num = 0;

    for (int i = 0; i < str.size(); ++i) {
        num = num * 10 + (*ptr)(str[i]);
    }
    
    return num;
} */

int main() {
    //std::cout << ((long long)480000000000000 / 1000000000) << ' ' << 268000000000 / 1000000000;

    //BigInt b("12 350000 0");
    String number("12 350000 0");
    BigInt bi(number);
    std::cout << "as string: " << number;
    std::cout << "\nas BigINt: " << bi;
    
    char ch = '2';
    std::cout << "\nsubstr: " << number.subStr(10,10) << '\n';
    std::cout << map(number.subStr(3, 8), charToll) + 4;
    std::cout << '\n' << number.size();

    
    return 0;
}