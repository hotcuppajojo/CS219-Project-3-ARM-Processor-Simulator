/** Project 3 - CS 219
    File: armprocessor.cpp
    Author: JoJo Petersky
*/
// Include necessary headers
#include "armprocessor.h"
// Constructor
ARMProcessor::ARMProcessor() {
    // Initializes the register state by creating instances of Register objects for each register
    // Also initializes the op function map by binding each op name to the corresponding member function
    // Initialize the register states:
    registers["R0"] = Register();
    registers["R1"] = Register();
    registers["R2"] = Register();
    registers["R3"] = Register();
    registers["R4"] = Register();
    registers["R5"] = Register();
    registers["R6"] = Register();
    registers["R7"] = Register();
    registers["CSPR"] = Register();
    // Initialize the operation function map:
    opFuncs["MOV"] = std::bind(&ARMProcessor::mov, this, std::placeholders::_1, std::placeholders::_2, std::string());
    opFuncs["ADD"] = std::bind(&ARMProcessor::add, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    opFuncs["SUB"] = std::bind(&ARMProcessor::sub, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    opFuncs["AND"] = std::bind(&ARMProcessor::andOp, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    opFuncs["ORR"] = std::bind(&ARMProcessor::orr, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    opFuncs["EOR"] = std::bind(&ARMProcessor::eor, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    opFuncs["XOR"] = std::bind(&ARMProcessor::xorOp, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    opFuncs["LSL"] = std::bind(&ARMProcessor::lsl, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    opFuncs["LSR"] = std::bind(&ARMProcessor::lsr, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    opFuncs["ASR"] = std::bind(&ARMProcessor::asr, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}
void ARMProcessor::addInstruction(const std::string& opType, const std::string& destReg, const std::string& operand1, const std::string& operand2) {
    // Add an instruction to the instruction list
    // Parameters:
    // - opType: The operation type of the instruction
    // - destReg: The destination register of the instruction
    // - operand1: The first operand of the instruction
    // - operand2: The second operand of the instruction (optional)
    instructions.emplace_back(opType, destReg, operand1, operand2);
    // Emplace a tuple representing the instruction into the instructions vector
    // The tuple consists of the operation type, destination register, operand1, and operand2 (if provided)
}
void ARMProcessor::getInstructions(const std::string& fileName) {
    // Read instructions from a file and populate the instruction list
    // Parameters:
    // - fileName: The name of the file containing the instructions
    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line)) {
        // Read each line from the file and process the instructions
        // Skip blank lines and comments
        // Check if the line is empty or starts with "//" (comment) or consists only of whitespace
        if (line.empty() || line.find("//") == 0 || std::all_of(line.begin(), line.end(), isspace)) {
            continue;
        }
        std::istringstream iss(line);
        std::string opType, destReg, operand1, operand2;
        // Extract opType
        if (!(iss >> opType)) {
            std::cerr << "Invalid instruction format: " << line << std::endl;
            continue;
        }
        // Extract destReg
        if (!(iss >> destReg)) {
            std::cerr << "Invalid instruction format: " << line << std::endl;
            continue;
        }
        // Remove extra comma
        if (!destReg.empty() && destReg.back() == ',') {
            destReg.pop_back();
        }
        // Extract operand1
        if (!(iss >> operand1)) {
            std::cerr << "Invalid instruction format: " << line << std::endl;
            continue;
        }
        // Remove extra comma
        if (!operand1.empty() && operand1.back() == ',') {
            operand1.pop_back();
        }
        // Operand2 is optional
        if (iss >> operand2) {
            // Remove extra comma
            if (!operand2.empty() && operand2.back() == ',') {
                operand2.pop_back();
            }
        }
        // Add the parsed instruction to the instruction list
        addInstruction(opType, destReg, operand1, operand2);
    }
}
void ARMProcessor::executeInstructions() {
    // Iterate over each instruction in the instruction list
    for (const auto& instruction : instructions) {
        const std::string& opType = std::get<0>(instruction);
        const std::string& destReg = std::get<1>(instruction);
        const std::string& operand1 = std::get<2>(instruction);
        const std::string& operand2 = std::get<3>(instruction);
        // Convert the operation type, destination register, and operands to uppercase
        std::string capitalizedOpType = opType;
        std::transform(capitalizedOpType.begin(), capitalizedOpType.end(), capitalizedOpType.begin(), ::toupper); // Convert opType to uppercase
        std::string capitalizedDestReg = destReg;
        std::transform(capitalizedDestReg.begin(), capitalizedDestReg.end(), capitalizedDestReg.begin(), ::toupper); // Convert destReg to uppercase
        std::string capitalizedOperand1 = operand1;
        std::transform(capitalizedOperand1.begin(), capitalizedOperand1.end(), capitalizedOperand1.begin(), ::toupper); // Convert operand1 to uppercase
        std::string capitalizedOperand2 = operand2;
        std::transform(capitalizedOperand2.begin(), capitalizedOperand2.end(), capitalizedOperand2.begin(), ::toupper); // Convert operand2 to uppercase
        // Print the capitalized instruction
        std::cout << capitalizedOpType << " " << capitalizedDestReg << ", " << capitalizedOperand1 << ", " << capitalizedOperand2 << std::endl;
        // Call the mov function with the capitalized registers and operands
        if (capitalizedOpType == "MOV") {
            mov(capitalizedDestReg, capitalizedOperand1, capitalizedOperand2);
        } else if (opFuncs.find(capitalizedOpType) != opFuncs.end()) {
            try {
                if (capitalizedOpType == "ASR" || capitalizedOpType == "LSR" || capitalizedOpType == "LSL") {
                    // Extract the immediate shift value from the operand2
                    std::string shiftValue = capitalizedOperand2.substr(1); // Remove the '#' symbol
                    // Call the corresponding op function with the capitalized registers and operands
                    opFuncs[capitalizedOpType](capitalizedDestReg, capitalizedOperand1, shiftValue);
                } else {
                    // Call the corresponding op function with the capitalized registers and operands
                    opFuncs[capitalizedOpType](capitalizedDestReg, capitalizedOperand1, capitalizedOperand2);
                }
            } catch (const std::out_of_range& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Unsupported operation: " << capitalizedOpType << std::endl;
        }
        // Print the register state
        printRegisterState();
        std::cout << "----------------------------" << std::endl;
    }
}
std::bitset<32> ARMProcessor::getImmediateValue(const std::string& value) {
    std::bitset<32> immValue;
    // Check if the value is in hexadecimal format (starts with "0X")
    if (value.substr(0, 2) == "0X") {
        std::string hexValue = value.substr(2); // Remove the "0X" prefix
        // Convert the hexadecimal value to an unsigned long integer and assign it to the bitset
        immValue = std::bitset<32>(std::stoul(hexValue, nullptr, 16));
    } else {
        // The value is in decimal format
        // Convert the decimal value to an integer and assign it to the bitset
        immValue = std::bitset<32>(std::stoi(value, nullptr, 10));
    }
    return immValue;
}
void ARMProcessor::printRegisterState() const {
    std::cout << "Register state:" << std::endl;
    // Set the uppercase flag for hex numbers
    std::cout << std::uppercase;
    // Print the status flags (CSPR)
    std::cout << "CSPR: N=" << cspr.getNFlag()
              << " Z=" << cspr.getZFlag()
              << " C=" << cspr.getCFlag()
              << " V=" << cspr.getVFlag() << std::endl;
    // Iterate over the registers and print their values
    for (const auto& registerPair : registers) {
        std::string registerKey = registerPair.first;
        std::transform(registerKey.begin(), registerKey.end(), registerKey.begin(), ::toupper);  // Convert to uppercase
        // Skip printing the CSPR register separately
        if (registerKey != "CSPR") {  // Skip printing CSPR separately
            // Print the register key and its value in hexadecimal format
            std::cout << registerKey << ": 0x" << std::hex << std::setfill('0') << std::setw(8) << std::uppercase << registerPair.second.get().to_ulong() << std::dec << std::endl;
        }
    }
    std::cout << std::nouppercase;  // Unset the uppercase flag
    std::cout << std::endl;  // Add an extra line for clarity
}
bool ARMProcessor::isValidRegister(const std::string& reg) const {
    // Convert the register name to uppercase for consistency
    std::string uppercaseReg = reg;
    std::transform(uppercaseReg.begin(), uppercaseReg.end(), uppercaseReg.begin(), ::toupper);
    // Check if the register starts with '#' (immediate value indicator)
    if (!uppercaseReg.empty() && uppercaseReg[0] == '#') {
        return false; // Register cannot start with '#'
    }
    // Check if the uppercase register exists in the registers map
    // If it is found (not equal to registers.end()), the register is considered valid
    return registers.find(uppercaseReg) != registers.end();
}
bool ARMProcessor::canConvertToInt(const std::string& str) const {
    // Check if the string starts with '#0x' indicating a hexadecimal value
    if (str.length() > 2 && str[0] == '#' && str[1] == '0' && str[2] == 'x') {
        // Extract the hexadecimal part of the string
        std::string hexPart = str.substr(3);
        // Return false if the extracted part is empty or contains non-hexadecimal characters
        return !hexPart.empty() && std::all_of(hexPart.begin(), hexPart.end(), [](unsigned char c) { return std::isxdigit(c); });
    }
    try {
        // Try converting the string to an integer using std::stoi
        std::stoi(str);
        return true; // If successful, return true
    } catch (...) {
        return false; // If an exception is caught, return false indicating conversion failure
    }
}
void ARMProcessor::updateFlags(const Register& result) {
    // Update the flags based on the result
    // Set the Negative (N) flag based on whether the result is negative
    cspr.setNFlag(result.isNegative());
    // Set the Zero (Z) flag based on whether the result is zero
    cspr.setZFlag(result.isZero());
    // Set the Carry (C) flag based on whether the result has a carry
    cspr.setCFlag(result.hasCarry());
    // Set the Overflow (V) flag based on whether the result has an overflow
    cspr.setVFlag(result.hasOverflow());
}
void ARMProcessor::mov(const std::string& destReg, const std::string& operand1, const std::string& operand2) {
    // Move an immediate value or the value of another register into the destination register
    // Parameters:
    // - destReg: The destination register to store the value
    // - operand1: The first operand (immediate value or source register)
    // - operand2: The second operand (source register) - optional

    // Check if the destination register is valid
    if (isValidRegister(destReg)) {
        std::bitset<32> immValue;
        try {
            // Determine the immediate value based on the operands
            if (operand1[0] == '#') {
                immValue = getImmediateValue(operand1.substr(1)); // Remove the '#' symbol
            } else {
                immValue = getImmediateValue(operand2.substr(1)); // Remove the '#' symbol
            }
            // Set the value of the destination register
            registers.at(destReg).set(immValue);
            // Update the status flags based on the new register value
            updateFlags(registers.at(destReg));
            // Catch an out-of-range exception if the destination register is not found in the map
        } catch (const std::out_of_range& e) {
            // Output the error message obtained from the exception
            std::cerr << "Error: " << e.what() << std::endl;
            // Catch an invalid_argument exception if an invalid immediate value is provided
        } catch (const std::invalid_argument& e) {
            // Output the error message obtained from the exception
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } else {
        // Output an error message if the destination register is invalid
        std::cerr << "Invalid destination register: " << destReg << std::endl;
    }
}
void ARMProcessor::add(const std::string& destReg, const std::string& operand1, const std::string& operand2) {
    // Perform addition operation between two source registers and store the result in the destination register
    // Parameters:
    // - destReg: The destination register to store the result
    // - operand1: The first source register
    // - operand2: The second source register

    // Check if all registers are valid
    if (isValidRegister(destReg) && isValidRegister(operand1) && isValidRegister(operand2)) {
        // Retrieve the values of operand1 and operand2 from the registers map
        Register result = registers.at(operand1) + registers.at(operand2);
        // Store the result in the destination register
        registers[destReg] = result;
        // Update the status flags based on the result
        updateFlags(result);
    } else {
        // Print an error message if any of the registers are invalid
        std::cerr << "Invalid registers: " << destReg << ", " << operand1 << ", " << operand2 << std::endl;
    }
}
void ARMProcessor::sub(const std::string& destReg, const std::string& operand1, const std::string& operand2) {
    // Subtract the value of one register from another and store the result in the destination register
    // Parameters:
    // - destReg: The destination register to store the result
    // - operand1: The first operand register
    // - operand2: The second operand register

    // Check if the destination register and operand registers are valid
    if (isValidRegister(destReg) && isValidRegister(operand1) && isValidRegister(operand2)) {
        // Subtract the value of operand2 from operand1 and store the result in result
        Register result = registers.at(operand1) - registers.at(operand2);
        // Assign the result to the destination register
        registers[destReg] = result;
        // Update the status flags based on the new register value
        updateFlags(result);
    } else {
        // Output an error message if any of the registers are invalid
        std::cerr << "Invalid registers: " << destReg << ", " << operand1 << ", " << operand2 << std::endl;
    }
}
void ARMProcessor::andOp(const std::string& destReg, const std::string& operand1, const std::string& operand2) {
    // Perform the bitwise AND operation between two registers and store the result in the destination register
    // Parameters:
    // - destReg: The destination register to store the result
    // - operand1: The first operand register
    // - operand2: The second operand register
    // Convert operand1 and operand2 to uppercase for consistency
    std::string upperOperand1 = operand1;
    std::transform(upperOperand1.begin(), upperOperand1.end(), upperOperand1.begin(), ::toupper);
    std::string upperOperand2 = operand2;
    std::transform(upperOperand2.begin(), upperOperand2.end(), upperOperand2.begin(), ::toupper);
    // Check if the destination register and operand registers are valid
    if (isValidRegister(destReg) && isValidRegister(upperOperand1) && isValidRegister(upperOperand2)) {
        // Perform the bitwise AND operation between operand1 and operand2 and store the result in result
        Register result = registers.at(upperOperand1) & registers.at(upperOperand2);
        // Assign the result to the destination register
        registers.at(destReg) = result;
        // Update the status flags based on the new register value
        updateFlags(result);
    } else {
        // Output an error message if any of the registers are invalid
        std::cerr << "Invalid registers: " << destReg << ", " << operand1 << ", " << operand2 << std::endl;
    }
}
void ARMProcessor::orr(const std::string& destReg, const std::string& operand1, const std::string& operand2) {
    // Perform the bitwise OR operation between two registers and store the result in the destination register
    // Parameters:
    // - destReg: The destination register to store the result
    // - operand1: The first operand register
    // - operand2: The second operand register
    // Convert operand1 and operand2 to uppercase for consistency
    std::string upperOperand1 = operand1;
    std::transform(upperOperand1.begin(), upperOperand1.end(), upperOperand1.begin(), ::toupper);
    std::string upperOperand2 = operand2;
    std::transform(upperOperand2.begin(), upperOperand2.end(), upperOperand2.begin(), ::toupper);
    // Check if the destination register and operand registers are valid
    if (isValidRegister(destReg) && isValidRegister(upperOperand1) && isValidRegister(upperOperand2)) {
        // Perform the bitwise OR operation between operand1 and operand2 and store the result in result
        Register result = registers.at(upperOperand1) | registers.at(upperOperand2);
        // Assign the result to the destination register
        registers.at(destReg) = result;
        // Update the status flags based on the new register value
        updateFlags(result);
    } else {
        // Output an error message if any of the registers are invalid
        std::cerr << "Invalid registers: " << destReg << ", " << operand1 << ", " << operand2 << std::endl;
    }
}
void ARMProcessor::eor(const std::string& destReg, const std::string& operand1, const std::string& operand2) {
    // Perform the bitwise XOR operation between two registers and store the result in the destination register
    // Parameters:
    // - destReg: The destination register to store the result
    // - operand1: The first operand register
    // - operand2: The second operand register
    // Check if the destination register and operand registers are valid
    if (isValidRegister(destReg) && isValidRegister(operand1) && isValidRegister(operand2)) {
        // Perform the bitwise XOR operation between operand1 and operand2 and store the result in result
        Register result = registers.at(operand1) ^ registers.at(operand2);
        // Assign the result to the destination register
        registers[destReg] = result;
        // Update the status flags based on the new register value
        updateFlags(result);
    } else {
        // Output an error message if any of the registers are invalid
        std::cerr << "Invalid registers: " << destReg << ", " << operand1 << ", " << operand2 << std::endl;
    }
}
void ARMProcessor::xorOp(const std::string& destReg, const std::string& operand1, const std::string& operand2) {
    // Perform the bitwise XOR operation between two registers and store the result in the destination register
    // Parameters:
    // - destReg: The destination register to store the result
    // - operand1: The first operand register
    // - operand2: The second operand register
    // Check if the destination register and operand registers are valid
    if (isValidRegister(destReg) && isValidRegister(operand1) && isValidRegister(operand2)) {
        // Perform the bitwise XOR operation between operand1 and operand2 and store the result in result
        Register result = registers.at(operand1) ^ registers.at(operand2);
        // Assign the result to the destination register
        registers[destReg] = result;
        // Update the status flags based on the new register value
        updateFlags(result);
    } else {
        // Output an error message if any of the registers are invalid
        std::cerr << "Invalid registers: " << destReg << ", " << operand1 << ", " << operand2 << std::endl;
    }
}
void ARMProcessor::lsl(const std::string& destReg, const std::string& operand1, const std::string& operand2) {
    // Perform the logical left shift operation on a register by a specified number of bits
    // Parameters:
    // - destReg: The destination register to store the result
    // - operand1: The operand register to be shifted
    // - operand2: The number of bits to shift by
    // Check if the destination register, operand register, and shift value are valid
    if (isValidRegister(destReg) && isValidRegister(operand1) && canConvertToInt(operand2)) {
        // Perform the logical left shift operation on operand1 by the specified number of bits
        Register result = registers.at(operand1) << std::stoi(operand2);
        // Assign the result to the destination register
        registers[destReg] = result;
        // Update the status flags based on the new register value
        updateFlags(result);
    } else {
        // Output an error message if any of the registers are invalid or the shift value is not a valid integer
        std::cerr << "Invalid registers: " << destReg << ", " << operand1 << ", " << operand2 << std::endl;
    }
}
void ARMProcessor::lsr(const std::string& destReg, const std::string& operand1, const std::string& operand2) {
    // Perform the logical right shift operation on a register by a specified number of bits
    // Parameters:
    // - destReg: The destination register to store the result
    // - operand1: The operand register to be shifted
    // - operand2: The number of bits to shift by
    // Check if the destination register, operand register, and shift value are valid
    if (isValidRegister(destReg) && isValidRegister(operand1) && canConvertToInt(operand2)) {
        // Perform the logical right shift operation on operand1 by the specified number of bits
        Register result = registers.at(operand1) >> std::stoi(operand2);
        // Assign the result to the destination register
        registers[destReg] = result;
        // Update the status flags based on the new register value
        updateFlags(result);
    } else {
        // Output an error message if any of the registers are invalid or the shift value is not a valid integer
        std::cerr << "Invalid registers: " << destReg << ", " << operand1 << ", " << operand2 << std::endl;
    }
}
void ARMProcessor::asr(const std::string& destReg, const std::string& operand1, const std::string& operand2) {
    // Perform the arithmetic right shift operation on a register by a specified number of bits
    // Parameters:
    // - destReg: The destination register to store the result
    // - operand1: The operand register to be shifted
    // - operand2: The number of bits to shift by
    // Check if the destination register, operand register, and shift value are valid
    if (isValidRegister(destReg) && isValidRegister(operand1) && canConvertToInt(operand2)) {
        // Perform the arithmetic right shift operation on operand1 by the specified number of bits
        Register result = registers.at(operand1) >> std::stoi(operand2);
        // Assign the result to the destination register
        registers[destReg] = result;
        // Update the status flags based on the new register value
        updateFlags(result);
    } else {
        // Output an error message if any of the registers are invalid or the shift value is not a valid integer
        std::cerr << "Invalid registers: " << destReg << ", " << operand1 << ", " << operand2 << std::endl;
    }
}