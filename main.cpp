/** Project 3 - CS 219
    File: main.cpp
    Author: JoJo Petersky
*/
// Include necessary headers
#include "armprocessor.h"
// Start main program
int main(int argc, char* argv[]) {
    // Check if the input file is missing
    if (argc < 2) {
        // Display an error message indicating the missing input file
        std::cout << "Error: Missing input file." << std::endl;
        std::cout << "Usage: ./Proj3 filename" << std::endl;
        std::cout << "  - filename: The name of the file containing the ARM instructions." << std::endl;
        std::cout << "               Each instruction should be on a separate line." << std::endl;
        return 1;
    }
    try {
        // Extract the filename from the command-line arguments
        std::string fileName = argv[1];
        // Create an instance of the ARMProcessor class
        ARMProcessor processor;
        // Read and parse the instructions from the input file
        processor.getInstructions(fileName);
        // Execute the instructions
        processor.executeInstructions();
        // Print the state of the registers after execution
        processor.printRegisterState();
    } catch (const std::exception& e) {
        // Catch any exceptions thrown during execution and display an error message
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}