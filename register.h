/** Project 3 - CS 219
    File: register.h
    Author: JoJo Petersky
*/
// Header guard to prevent multiple inclusion of the header
#ifndef REGISTER_H
#define REGISTER_H
// Include necessary headers
#include "cspr.h"
#include <bitset>
// Register class representing a 32-bit register
class Register {
    std::bitset<32> value; // holds the value of the register
public:
    // Constructors
    Register();
    Register(const Register& reg);
    Register(const std::bitset<32>& initialValue);
    // Overloaded operators
    Register& operator=(const Register& reg);
    Register operator+(const Register& reg);
    Register operator-(const Register& reg);
    Register operator&(const Register& reg);
    Register operator|(const Register& reg);
    Register operator^(const Register& reg);
    Register& operator>>=(const int shift);
    Register operator>>(const int shiftVal);
    Register operator<<(const int shiftVal);
    // Getter and setter methods
    std::bitset<32> get() const;
    void set(const std::bitset<32>& newValue);
    // Flag-related methods
    bool isNegative() const;
    bool isZero() const;
    bool hasCarry() const;
    bool hasOverflow() const;
};
#include "register.cpp" // Include the implementation file
#endif // End of the header guard