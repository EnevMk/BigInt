#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <iostream>
#include "String.hpp"
#include "Vector.hpp"

#define BASE (long long)1000000000
#define ZERO BigInt(0)


/// @brief The main class for the whole project.
///
/// Class BigInt, its purpose being enabling users to work with numbers too big that aren't supported by
/// the language built-in types. Working in a billion number system, it offers broad functionality along with 
/// great effectiveness resource-wise. 
/// 
/// Core functionalities are: Addition, Subtraction, Multiplication and a fast exponentiation alghoritm.
/// 
class BigInt {

private:
    
    /// Helper method for the addition operator.
    ///
    /// This method is used in the main addition operator. Given two BigInt numbers
    /// (one as argument, the other passed implicitly, as caller of the method), 
    /// two indexes showing which exact digits in the two numbers are being summed,
    /// and a remainder variable passed by reference to keep the remainder of the operation.
    /// @param obj - a const reference to the second BigInt number (the other is caller of the method)
    /// @param first - the index of the digit from the first BigInt number (namely *this*)
    /// @param second - the index of the digit from the second BigInt number (*obj*)
    /// @param rem - A long long variable storing the eventual remainder of the sum of the two digits modulo the BASE
    /// @return - returns a long long variable holding the result digit
    long long calculateDigitAddition(const BigInt &obj, int first, int second, long long &rem) const;

    /// Helper method for the subtraction operator.
    ///
    /// This method is used in the main subtraction operator. Given two BigInt numbers
    /// (one as argument, the other passed implicitly, as caller of the method), 
    /// two indexes showing which exact digits in the two numbers are are respectively the minuend and subtrahend,
    /// @param obj - a const reference to the second BigInt number (the other is caller of the method)
    /// @param first - the index of the digit from the first BigInt number (namely *this*)
    /// @param second - the index of the digit from the second BigInt number (*obj*)
    /// @return - returns a long long variable holding the result digit
    //long long calculateDigitSubtraction(const BigInt &obj, int first, int second, BigInt &result, int index) const;
    long long calculateDigitSubtraction(const BigInt &obj, int first, int second);

    
    //void calculateBigIntByNum(int bigIntLen, const BigInt &obj, BigInt& result, long long num) const;
    //BigInt calculateBigIntByNum(int bigIntLen, long long num) const;

    /// @brief Helper method for the addition operator.
    ///
    /// Used in the addition operator, this method handles addition for negative numbers. Works with two BigInt numbers,
    /// the first one being *this* (the caller of the method) and the other as a const Bigint by reference.
    /// The Class basically simulates
    /// operations with negative numbers, but under the hood, it gets all the work down to operations with positive numbers and then
    /// returns their negated values. So this handler method takes care of that. Bear in mind there is a differrent handler for 
    /// each operation - +, -, *
    /// @param obj - the second BigInt addend (first one is *this*)
    /// @see operator+(const BigInt &obj) const
    /// @return - if the two BigInts are positive, returns ZERO. Otherwise, returns the result of the
    /// proper operation called with positive numbers by negating the initial ones.
    /// @see negate() const
    BigInt operatorHandlerAddition(const BigInt &obj) const;

    /// @brief Helper method for the subtraction operator.
    ///
    /// @param obj - the subtrahend (minuend is passed implicitly, *this*)
    /// @see operator-(const BigInt &obj) const
    /// @return - if operation doesn't need further handling - returns ZERO, Otherwise calls proper operation with negated values
    /// 
    BigInt operatorHandlerSubtraction(const BigInt &obj) const;

    /// @brief Helper method for the multiplication operator.
    ///
    /// @param obj - the second multipliеr (first one is caller of the method)
    /// @see operator*(const BigInt &obj) const
    /// @return - if operation doesn't need further handling - returns ZERO, Otherwise calls proper operation with negated values
    BigInt operatorHandlerMultiplication(const BigInt &obj) const;

    /// @brief Helper method for the multiplication operator.
    /// 
    /// The multiplication operator works in the following way: Takes two BigInt numbers,
    /// separates the second BigInt number's digits and multiplies the first BigInt by all those digits.
    /// The result of that is a Vector of BigInts. This method takes that Vector and sums all its elements in a special way,
    /// so that in the end the result is the product of the two initial BigInts.
    /// @param obj - Vector containg all *subproducts*
    /// @return - returns the final Product
    /// @see operator*(const BigInt &obj)
    void sumVectorsMultiplication(Vector<BigInt> &obj);

    /// @brief The BigInt Number itself.
    ///
    /// A vector of type long long, containing the digits of the BigInt.
    Vector<long long> digitsContainer;
public:
    
    /// @brief Helper for the multiplication operator.
    ///
    /// As mentioned before, multiplication works by multiplying a BigInt by all the digits of the other BigInt.
    /// This Helper method takes a BigInt (implicitly) and multiplies it by the passed long long number (BigInt digit)
    /// @param num - long long number, BigInt digit in context
    /// @return - returns a new BigInt object.
    /// @see operator*(const BigInt &obj)

    BigInt multiplyByNum(long long num) const; // multiplies a BigInt by a long long

    /// @brief Helper method for the fast exponentiation method.
    ///
    /// The effective exponentiation works on an algorithm using division by two in simplifying the operation,
    /// and as the project doesn't support division, this method was implemented
    /// (Alghorithm simplifies the operation by dividing the BigInt number by two each step)
    /// @return - Returns the caller of the method divided by long long 2.
    /// @see fastPow(const BigInt &power)
    BigInt divideByTwo() const;
    
    /// @brief Default constructor - Initializes An empty Vector with capacity of one.
    BigInt();

    /// @brief Paramater Constructor, initializing a BigInt number by String.
    ///
    /// This is the easiest and most intuitive way of initializing an object of Class BigInt.
    /// Given that the library uses a not-so-popular billion number system,
    /// the developers want to use it should conform to some standarts. Since a single digit in a billion number system 
    /// is in the range [0 - 999999999], BigInt numbers can look messy at first. So, the developers have decided that BigInt numbers 
    /// should be represented with a space between every *billion system digit* and no spaces between single (decimal) digits.
    /// Therefore, strings passed to that constructor should stick to that standart.
    /// ### Example
    
    /// BigInt("134 240000"); // This Creates the BigInt number 134 240000, two digits, which in decimal is 134 000 240 000. \n
    /// BigInt("5 1"); // This creates the BigInt number 5 1, that's two digits, which in decimal is 5 000 000 001 \n \n
    
    /// The constructor supports a bit of validation, like removing whiteSpaces.
    /// ### Example
    /// BigInt bigNumber("13     0   99391"); // Creates number 13 0 99391, three digits, 
    /// 13 000 000 000 000 099 391 - thirteen quintillion something.. \n
    /// BigInt("900000000 0") // 900 000 000 000 000 000 - nine hundred quadrillion. \n \n
    /// Passing an invalid string though (cont. symbols other than numbers) causes the program to stop. \n
    /// Therefore developers who use this library in their project should think of implementing proper validation.
    /// @param value - String containing the correct presentation of the desired BigInt nuber
    BigInt(const String &value);

    /// @brief Parameter Constructor taking long long variable.
    ///
    /// This one initializes a single-digit BigInt (max value 999 999 999), used in pre-development, not recommended to use.
    BigInt(long long num);

    /// @brief Param Constructor taking a Vector. Sets the BigInt memeber vector as the passed param. Used In pre-development.
    /// Reccommendet to use The String Constructor instead.
    BigInt(const Vector<long long> &v);

    /// @brief Copy Constructor
    BigInt(const BigInt &obj);

    /// @brief Assignment operator
    BigInt& operator=(const BigInt &obj);
    
    const long long operator[](size_t i) const; // returning a digit of the BigInt on ith index
    long long operator[](size_t i);

    bool operator==(const BigInt &obj) const;
    bool operator!=(const BigInt &obj) const;
    bool operator>(const BigInt &obj) const;
    bool operator<(const BigInt &obj) const;
    bool operator>=(const BigInt &obj) const;
    bool operator<=(const BigInt &obj) const;

    /// @brief A method that returns its caller, but negated.
    ///
    /// As mentioned before, to handle arithmetical operations class BigInt sometimes needs to use the negated values of the arguments.
    /// This method is simple, but fundamental for the class. For example * a + (-b) * is * a - b *,  * -a + (-b) * is * -a -b * and so forth.
    /// @return - the negated caller of the method.
    /// ### Example
    /// BigInt("5 0").negate(); // The constructor will create the number 5 0 (5 000 000 000 in dec.) and then the negate method will return 
    /// the number -5 0. So the whole evaluation of the method will result in -5 0.
    BigInt negate() const; // returns the negated BigInt number

    /// @brief Helper method for arithmetic operations +, -, *
    ///
    /// by default, all three arithmetic operations presume that the result will be one with maximal count of digits.
    /// For example, lets take two two-digit numbers. Due to the nature of the container (a Vector), it is needed to reserve memory
    /// for the result before the actual evaluation of the expression. So, for two two-digit numbers and operation + called, memory for 
    /// a Three-digit bignum will be reserved. (BigInt("9 9") + BigInt("9 9") results in BigInt("1 0 8")). 
    /// But, sometimes that may not be a proper final return value - let's have BigInt("2 5") + BigInt("1 5"). In that case we want the answer 
    /// BigInt("4 0"), but as the operator will have reserved a Vector of size three for the result so we will actually have BigInt("0 4 0"),
    /// which is incorrect. That's what this method does - in case of a zero digit on first position, it handles it and returns a correct result.
    void cutFirstNull();

    /* /// @brief Helper method for the arithmetical operations.
    ///
    /// In the - operation, while applying the operation digit by digit, sometimes we may have a similar situation:
    /// Let's say we want to do BigInt("1 750000000") - BigInt("900000000"). Digit by digit means the operator will do 
    /// 750000000 * BASE^0 - 900000000 ^ BASE ^ 0 and 1 * BASE ^ 1 - 0 ^ BASE^1. But, 750000000 is less than 900000000
    //void null(); */

    /// @brief just a method that calls reserve() on the private member data digitsContainer.
    void reserveVectorCapacity(int n);

    /// @brief Helper method for the arithmetic operators.
    ///
    /// As all the arithmetic operators work digit by digit, the result is composed backwards.
    /// For example, If we want BigInt("17 500000") - BigInt("8 300000"), first the operator - calculates
    /// 500000 - 300000 and pushes it at the back of the result Vector (i-th position), and after that calculates 
    /// 17 - 8 and pushes it to the (i - 1 th position).
    /// @param digit - the long long digit pushet at the last non-calculated position of the result Vector.

    void pushLast(long long digit); // pushes a long long to the last free position of the vector
    void push(long long digit);

    /// @brief method that return the length of the BigInt, i.e. its digits count.
    int size() const;
    
    /// @brief getter for the private member data.
    const Vector<long long>& getVector() const;
    
    /// @brief the standart friend function to output a BigInt object to a stream.
    friend std::ostream& operator<<(std::ostream &os, const BigInt &obj);

    /// Operation + : performing addition on two BigInt numbers. Working digit by digit, meaning it sums the long long variables on each
    /// position.
    /// @param obj - the second addend (first one is caller of the method).
    /// @see calculateDigitAddition(const BigInt &obj, int first, int second, long long &rem) const
    /// @see operatorHandlerAddition(const BigInt &obj) const
    /// @return the Result BigInt number.
    BigInt operator+(const BigInt &obj) const;

    /// Operation - : performing subtraction on a Minuend number (the caller of the method) by a subtrahend (parameter).
    /// @param obj - the subtrahend BigInt. (Minuend is caller of the method).
    /// @see calculateDigitSubtraction(const BigInt &obj, int first, int second)
    /// @see operatorHandlerSubtraction(const BigInt &obj) const
    /// @return - the Result BigInt difference.
    BigInt operator-(const BigInt &obj) const;

    /// Operation * : Performing multiplication on two BigInt numbers. Works by multiplying the first one by all
    /// the digits of the second one, which result in a vector of products (BigInts) and then summing that vector
    /// gives the final result.
    /// @param obj - the second multiplier (first one is caller of the method)
    /// @see operatorHandlerMultiplication(const BigInt &obj) const;
    /// @see sumVectorsMultiplication(Vector<BigInt> &obj);
    /// @see multiplyByNum(long long num) const;
    /// @return - the product BigInt.
    BigInt operator*(const BigInt &obj) const;
    
    /// @brief An exponentiation method for BigInt number working on an optimised algorithm.
    ///
    /// This method uses the simple, but powerful algorithm for exponentiation by squaring. It's a recursive algorithm
    /// That simmplifies the task by squaring the argument and halving the power on each recursive call. \n
    /// So x^n = (x^2) ^ n/2 if n is odd \n
    /// or x^n = x * (x^2) ^ n\2
    /// For Example, (in decimal) if we pass 3^13, The function would be evaluated the following way:
    /// This reduces the count of multiplication operations significantly.
    /// @param power - the exponent value (BigInt object)
    /// @return - the caller of the method raised to the *power* argument.
    BigInt fastPow(const BigInt &power) const;
};

inline long long charToll(char character) {

    return (character - '0');
}

inline long long mapStringToNumbers(const String &str, long long (*ptr)(char)) {
    long long num = 0;
    bool isNegative = false;

    int i = 0;
    if (str[0] == '-') {
        i = 1;
        isNegative = true;
    }
    
    for (i; i < str.size(); ++i) {
        num = num * 10 + (*ptr)(str[i]);
    }
    
    if (isNegative) {
        return num - 2 * num;
    }
    return num;
}

#endif