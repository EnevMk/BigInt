#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "BigInt.hpp"


TEST_CASE("Fast raising to power") {
    BigInt number("5 1");
    CHECK(fastPow(number, BigInt(2)) == BigInt("25 10 1"));
}

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

TEST_CASE("Remove whitespaces in ends string method") {
    String withSpaces("  3 2  ");
    String noSpaces("3 2");

    withSpaces.removeEndWhiteSpaces();
    noSpaces.removeEndWhiteSpaces();
    CHECK(withSpaces == noSpaces);
}

TEST_CASE("negative BigInt by String initialization") {
    BigInt str("-3 0");

    BigInt vec;
    vec.reserveVectorCapacity(2);
    vec.pushLast(0);
    vec.pushLast(-3);

    CHECK(vec == str);
}