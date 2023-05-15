# CS219-Project-3-ARM-Processor-Simulator

This project is an ARM processor simulator implemented in C++ that allows for the execution of ARM instructions and tracking of register states. It provides a practical tool to understand and simulate the behavior of an ARM processor.

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)
- [Assignment Details](#assignment-details)
- [Result and Working Process](#result-and-working-process)

## Description

The ARM Processor Simulation project aims to simulate the execution of ARM instructions and track the register states during the execution process. It is implemented in C++ and provides a command-line interface to interact with the simulation.

## Features

- Parsing and execution of various ARM instructions
- Tracking and updating register states
- Error handling for invalid instructions, registers, and operands

## Getting Started

To get started with the ARM Processor Simulator, follow these steps:

1. Clone the repository:

   ```shell
   git clone https://github.com/your-username/arm-processor-simulation.git
   ```

2. Compile the source code:

   ```shell
   g++ -o Proj3 main.cpp
   ```

3. Run the simulation:

   ```shell
   ./Proj3 input.txt
   ```

   Replace `input.txt` with the name of the file containing the ARM instructions.

## Usage

The ARM Processor Simulator requires an input file containing the ARM instructions. Each instruction should be on a separate line. After executing the instructions, the simulation will display the register states.

Example input file (input.txt):

```
MOV R1, #10
ADD R2, R1, #20
SUB R3, R2, R1
```

Example output:

```
MOV R1, #10
Register state:
R1: 0x0000000A

ADD R2, R1, #20
Register state:
R1: 0x0000000A
R2: 0x0000001E

SUB R3, R2, R1
Register state:
R1: 0x0000000A
R2: 0x0000001E
R3: 0x00000014
```

## Contributing

Contributions to the ARM Processor Simulator are welcome! If you would like to contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch.
3. Make your changes.
4. Commit your changes.
5. Push your changes to your forked repository.
6. Submit a pull request.

## License

The ARM Processor Simulator is licensed under the MIT License. See [LICENSE](LICENSE) for more information.

## Contact

For any questions or inquiries, please contact the author:

Author: JoJo Petersky
Email: jpetersky@nevada.unr.edu

## Assignment Details

This project is developed as part of the CS 219 course project. The goal is to simulate the execution of ARM instructions using a custom ARM processor implementation.

The project consists of the following files:

- `armprocessor.h`: Header file that defines the `ARMProcessor` class.
- `armprocessor.cpp`: Implementation file that contains the member function definitions of the `ARMProcessor` class.
- `cspr.h`: Header file that defines the `CSPR` class, representing the Current Program Status Register.
- `cspr.cpp`: Implementation file that contains themember function definitions of the `CSPR` class.
- `register.h`: Header file that defines the `Register` class, representing a general-purpose register.
- `register.cpp`: Implementation file that contains the member function definitions of the `Register` class.
- `main.cpp`: The main program that interacts with the `ARMProcessor` class to simulate the execution of ARM instructions.
- `makefile`: Makefile to compile and link the source files into an executable.

## Result and Working Process

The ARM processor simulator allows the execution of ARM instructions. Upon running the program with a file containing ARM instructions, the program will read the instructions, execute them one by one, and display the register state after each instruction.

To use the simulator, follow the usage instructions mentioned above. The simulator supports various ARM instructions, such as MOV, ADD, SUB, AND, ORR, EOR, XOR, LSL, LSR, and ASR. Each instruction can have operands and produces results that affect the register state. The simulator updates the register values and the status flags (N, Z, C, V) accordingly.

During the development process, the ARM processor simulator was implemented using the C++ programming language. The `ARMProcessor` class represents the processor and contains member functions to execute different types of ARM instructions. Additional classes, such as `CSPR` and `Register`, were created to handle the Current Program Status Register and general-purpose registers, respectively.

The implementation followed the assignment requirements and involved parsing the instructions from a file, validating the registers and operands, performing the corresponding operations, updating the register values and status flags, and displaying the register state after each instruction.

Throughout the development process, proper error handling and exception handling were implemented to ensure the stability and reliability of the simulator. Invalid instructions, registers, or operands are detected, and appropriate error messages are displayed.

The simulator was tested with various sets of ARM instructions to verify its correctness and accuracy. The register state was carefully tracked after each instruction execution to ensure that the results match the expected behavior.

The project followed good coding practices, including modular design, encapsulation, and code reusability. The code is organized into separate files based on their functionality, promoting maintainability and readability. Comments are included throughout the code to explain the purpose and functionality of the different sections.

In conclusion, this ARM processor simulator provides a practical tool to understand and simulate the execution of ARM instructions. It can be used for educational purposes or as a reference for understanding processor architectures. The simulator demonstrates the process of parsing instructions, executing operations, and updating register states, while adhering to good coding practices and error handling techniques.
