#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "BigInt.hpp"

TEST_CASE("+ operation") {
    BigInt a = 999999999;
    BigInt b = 1;
    BigInt c = a + b;
    CHECK(a.size() + b.size() == 2);

    Vector<long long> v(2);
    v.push(1);
    v.push(0);
    BigInt d = v;

    for (int i = 0; i < d.size(); ++i) {
        CHECK(c[i] == d[i]);
    }

    CHECK(c.size() == d.size());
    CHECK(1 + 1 == 2);

    BigInt e; //2 100 000 000
    e.reserveVectorCapacity(2);
    e.pushLast(100000000);
    e.pushLast(2);

    CHECK(e.size() == 2);
    CHECK(e[0] == 2);
    CHECK(e[1] == 100000000);

    BigInt res;
    res.reserveVectorCapacity(2);
    res.pushLast(200000000);
    res.pushLast(4);

    BigInt res2 = e + e;

    CHECK(res[0] == 4);
    CHECK(res[1] == 200000000);
    CHECK(res.size() == 2);

    CHECK(res2[0] == 4);
    CHECK(res2[1] == 200000000);
    CHECK(res2.size() == 2);
    CHECK(res2 == res);

    BigInt test;
    test.reserveVectorCapacity(2);
    test.pushLast(100000000);
    test.pushLast(5);

    CHECK(test[0] == 5);
    CHECK(test[1] == 100000000);
    //CHECK(test.size() == test.bigNum.maxCapacity());
    //CHECK(test.size() == test.bigNum.size());

    BigInt t2;
    t2.reserveVectorCapacity(2);
    t2.pushLast(100000000);
    t2.pushLast(5);
    

    CHECK(t2[0] == 5);
    CHECK(t2[1] == 100000000);
    //CHECK(t2.size() == t2.bigNum.maxCapacity());
    //CHECK(t2.size() == t2.bigNum.size());
    CHECK(t2 == test);

    BigInt mm = 900000000;
    CHECK(t2 - res2 == mm);
    CHECK(res - t2 == mm.negate());
}


TEST_CASE(" - operation") {
    BigInt a;
    a.reserveVectorCapacity(2);
    a.pushLast(0);
    a.pushLast(1);

    BigInt b = 999999999;
    BigInt c = 1;

    CHECK(a - b == c);
    CHECK(a - c == b);
    CHECK(b + c == a);
    CHECK(b.negate() - a.negate() == c);

    Vector<long long> v1;
    v1.push(-1);
    v1.push(999999999);
    CHECK(b.negate() - a == BigInt(v1));
    CHECK(b - a.negate() == a + b);
}

TEST_CASE("BigInt by long long multiplication") {
    BigInt a;
    a.reserveVectorCapacity(2);
    a.pushLast(100000000);
    a.pushLast(4);

    long long n = 999999000;

    BigInt result;
    result.reserveVectorCapacity(3);
    result.pushLast(0);
    result.pushLast((99999900 + 999996000));
    result.pushLast(3);

    CHECK(multiplyByNum(a, n) == result);

    BigInt s;
    s.reserveVectorCapacity(2);
    s.pushLast(0);
    s.pushLast(40);

    BigInt r;
    r.reserveVectorCapacity(2);
    r.pushLast(0);
    r.pushLast(120);

    CHECK(multiplyByNum(s, 3) == r);
}