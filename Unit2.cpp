#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "BigInt.hpp"


/* TEST_CASE("Fast raising to power") {
    BigInt number("5 1");
    //CHECK(fastPow(number, BigInt(2)) == BigInt("25 10 1"));
    CHECK(number.fastPow(BigInt(2)) == BigInt("25 10 1"));
} */

/* TEST_CASE("Fast raising to power 2") {
    BigInt number("5 0");
    //CHECK(fastPow(number, BigInt(2)) == BigInt("25 0 0"));
    CHECK(number.fastPow(BigInt("2")) == BigInt("25 0 0"));
} */

TEST_CASE("getting to ZERO by Minus operation") {
    BigInt num("2");
    
    BigInt minuend("1");
    CHECK(num - minuend == minuend);
    CHECK(num - minuend - minuend == ZERO);
}

TEST_CASE("String init") {
    BigInt v("5 0");
    BigInt s;
    s.reserveVectorCapacity(2);
    s.pushLast(0);
    s.pushLast(5);

    CHECK(v.size() == 2);
    CHECK(v == s);
}

TEST_CASE("String initialization bigger number") {
    BigInt str("134 240000");
    BigInt vec;
    vec.push(134);
    vec.push(240000);

    CHECK(str == vec);
}

TEST_CASE("Remove whitespaces in ends string method") {
    String withSpaces("  3 2  ");
    String noSpaces("3 2");

    withSpaces.removeEndWhiteSpaces();
    noSpaces.removeEndWhiteSpaces();
    CHECK(withSpaces == noSpaces);
}

TEST_CASE("negative BigInt by String initialization") {
    
    BigInt str("  -3 0");

    BigInt vec;
    vec.reserveVectorCapacity(2);
    vec.pushLast(0);
    vec.pushLast(-3);

    CHECK(vec == str);
}

TEST_CASE("BigInt by ll0 multiplication") {
    BigInt num("1 4 240000");
    long long ll = 0;
    CHECK(num.multiplyByNum(ll) == BigInt(0));
}

TEST_CASE("BigInt by single-digit long long multiplication") {
    BigInt number("134 240000");
    long long ll = 2;
    CHECK(number.multiplyByNum(ll) == BigInt("268 480000"));
}

TEST_CASE("Testing String initialization validation - middle whitespaces") {
    BigInt bigNumber("13     0   99391");
    BigInt vec;
    vec.push(13);
    vec.push(0);
    vec.push(99391);

    CHECK(bigNumber == vec);
}

TEST_CASE("Removing String repetitive Whitespaces") {
    String spaces("32     8    90");
    spaces.removeRepetitiveWhiteSpaces();
    String noSpaces("32 8 90");
    CHECK(spaces == noSpaces);
}
TEST_CASE("Minus operation ") {
    BigInt numb("1 700000000");
    BigInt num2("900000000");
    CHECK(numb - num2 == BigInt("800000000"));
}

TEST_CASE("negative Minus negative") {
    BigInt neg1("-23 198 0");
    BigInt neg2("-19 199 0");
    BigInt res("-3 999999999 0");
    CHECK(neg1 - neg2 == res);
}

TEST_CASE("Negative Plus positive") {
    BigInt neg("-3 170000987");
    BigInt pos("3 170000987");
    CHECK(neg - pos == BigInt("-6 340001974"));
}

TEST_CASE("fastPow a negative num") {
    BigInt fast("-4 2");
    CHECK(fast.fastPow(BigInt("2")) == BigInt("16 16 4"));
}

TEST_CASE("fastPow a negative num by odd power") {
    BigInt big("-3 0");
    CHECK(big.fastPow(BigInt("3")) == BigInt("-27 0 0 0"));
}

TEST_CASE("Multiply negative by negative") {
    BigInt a("-500 000 000"); // half a billion
    BigInt b("-1 0");
    CHECK(a * b == BigInt("500000000 0"));
}

TEST_CASE("Multiplication") {
    BigInt a("134 240000");
    BigInt b("2 0");;
    CHECK(a * b == BigInt("268 480000 0"));
}

TEST_CASE("Negate method") {
    BigInt one("1");
    CHECK(one.negate() == BigInt("-1"));
}