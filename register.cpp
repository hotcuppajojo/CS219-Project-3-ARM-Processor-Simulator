/** Project 3 - CS 219
    File: register.cpp
    Author: JoJo Petersky
*/
// Include necessary headers
#include "register.h"
// Default constructor
Register::Register() : value(0) {
}
// Copy constructor
Register::Register(const Register& reg) : value(reg.value) {
}
// Constructor with initial value
Register::Register(const std::bitset<32>& initialValue) : value(initialValue) {
}
// Set the value of the register
void Register::set(const std::bitset<32>& newValue) {
    value = newValue;
}
// Get the value of the register
std::bitset<32> Register::get() const {
    return value;
}
// Assignment operator
Register& Register::operator=(const Register& reg) {
    if (this != &reg) {
        value = reg.value;
    }
    return *this;
}
// Addition operator
Register Register::operator+(const Register& reg) {
    std::bitset<32> result;
    bool carry = false;
    for (int i = 0; i < 32; ++i) {
        bool sum = value[i] ^ reg.value[i] ^ carry;
        carry = (value[i] && reg.value[i]) || (value[i] && carry) || (reg.value[i] && carry);
        result[i] = sum;
    }
    Register res(result);
    return res;
}
// Subtraction operator
Register Register::operator-(const Register& reg) {
    std::bitset<32> result;
    bool borrow = false;
    for (int i = 31; i >= 0; i--) {
        bool a = value[i];
        bool b = reg.value[i];
        bool diff = a ^ b ^ borrow;
        result[i] = diff;
        borrow = (a && !b) || ((a ^ b) && borrow);
    }
    Register res(result);
    return res;
}
// Bitwise AND operator
Register Register::operator&(const Register& reg) {
    std::bitset<32> result = value & reg.value;
    Register res(result);
    return res;
}
// Bitwise OR operator
Register Register::operator|(const Register& reg) {
    std::bitset<32> result = value | reg.value;
    Register res(result);
    return res;
}
// Bitwise XOR operator
Register Register::operator^(const Register& reg) {
    std::bitset<32> result = value ^ reg.value;
    Register res(result);
    return res;
}
// Arithmetic right shift operator
Register& Register::operator>>=(const int shift) {
    value >>= shift;
    return *this;
}
// Logical Left shift operator
Register Register::operator<<(const int shiftVal) {
    std::bitset<32> result = value << shiftVal;
    Register res(result);
    return res;
}
// Logical Right shift operator
Register Register::operator>>(const int shiftVal) {
    std::bitset<32> result = value >> shiftVal;
    Register res(result);
    return res;
}
// Check if the register value is negative
bool Register::isNegative() const {
    return value[31];  // Get the most significant bit (bit 31)
}
// Check if the register value is zero
bool Register::isZero() const {
    return value.none();  // Check if all bits are zero
}
// Check if the register has a carry flag
bool Register::hasCarry() const {
    return value[32 - 1]; // The carry flag is set if the most significant bit is shifted out (bit 31)
}
// Check if the register has an overflow flag
bool Register::hasOverflow() const {
    // The overflow flag is set if there is a signed arithmetic overflow
    // This can be detected by comparing the sign bits of the operands and the result
    bool operand1Sign = value[31];
    bool operand2Sign = value[31];
    bool resultSign = (*this).isNegative();
    // Overflow occurs if the sign of the operands is different, but the sign of the result is the same
    return (operand1Sign != operand2Sign) && (operand1Sign == resultSign);
}