#include <iostream>
#include "Vector.hpp"
#include "catch_amalgamated.hpp"
#include "BigInt.hpp"
#define CATCH_CONFIG

TEST_CASE("testing vector") {
    int arr[] = {2, 49, 77};
    Vector<int> vec(arr, 3);

    CHECK(vec[2] == 77);
    CHECK(vec.size() == 3);

    Vector<int> v2 = vec;
    
    v2.push(14);
    CHECK(v2[3] == 14);
    CHECK(v2.size() == 4);
    v2.popBack();

    CHECK(v2.size() == 3);
    v2.removeAtIndex(1);
    CHECK(v2[1] == 77);
}

TEST_CASE("testing bigint") {
    
    long long arr[] = {789991124, 300000981, 101478077};
    Vector<long long> vis(arr, 3);

    BigInt a = vis;

    CHECK(a.bigNum[2] == 101478077);
    a.bigNum.push(7899911241);
    CHECK(a.bigNum.size() == 4);
    CHECK(a.bigNum[3] == 7899911241);
}

/* int main() {

    


    return 0;
} */