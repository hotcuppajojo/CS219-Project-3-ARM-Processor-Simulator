/** Project 3 - CS 219
    File: armprocessor.h
    Author: JoJo Petersky
*/
// Header guard to prevent multiple inclusion of the header
#ifndef ARMPROCESSOR_H
#define ARMPROCESSOR_H
// Include necessary headers
#include "cspr.h"
#include "register.h"
#include <string>
#include <algorithm>
#include <cctype>
#include <tuple>
#include <functional>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
// ARMProcessor class partially simulates an 32-bit ARM processor
class ARMProcessor {
    // Map to store the registers
    std::map<std::string, Register> registers;
    // Vector to store instructions
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> instructions;
    // Map to store operation functions
    std::map<std::string, std::function<void(const std::string&, const std::string&, const std::string&)>> opFuncs;
    // CSPR object representing the status flags
    CSPR cspr;
public:
    // Constructor
    ARMProcessor();
    // Add an instruction to the instruction list
    void addInstruction(const std::string& opType, const std::string& destReg, const std::string& operand1, const std::string& operand2);
    // Read instructions from a file and populate the instruction list
    void getInstructions(const std::string& fileName);
    // Execute the instructions in the instruction list
    void executeInstructions();
    // Convert a string value to a 32-bit immediate value (bitset)
    std::bitset<32> getImmediateValue(const std::string& value);
    // Print the state of the registers
    void printRegisterState() const;
private:
    // Assembly code op functions
    void mov(const std::string& destReg, const std::string& operand1, const std::string& operand2);
    void add(const std::string& destReg, const std::string& operand1, const std::string& operand2);
    void sub(const std::string& destReg, const std::string& operand1, const std::string& operand2);
    void andOp(const std::string& destReg, const std::string& operand1, const std::string& operand2);
    void orr(const std::string& destReg, const std::string& operand1, const std::string& operand2);
    void xorOp(const std::string& destReg, const std::string& operand1, const std::string& operand2);
    void lsl(const std::string& destReg, const std::string& operand1, const std::string& operand2);
    void lsr(const std::string& destReg, const std::string& operand1, const std::string& operand2);
    void asr(const std::string& destReg, const std::string& operand1, const std::string& operand2);
    // Helper functions
    bool isValidRegister(const std::string& reg) const;
    bool canConvertToInt(const std::string& s) const;
    void updateFlags(const Register& result);
};
#include "armprocessor.cpp" // Include the implementation file
#endif // End of the header guard