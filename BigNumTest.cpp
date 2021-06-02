#include <iostream>
#include "BigInt.hpp"


int main() {
    
    String spaces("33    987");
    spaces.removeRepetitiveWhiteSpaces();
    std::cout << spaces;

    return 0;
}

