# CS219-Project-3-ARM-Processor-Simulator

This project is an ARM processor simulator implemented in C++ that allows for the execution of ARM instructions and tracking of seven register states. It provides a practical tool to understand and simulate the behavior of an ARM processor with seven registers.

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

The ARM Processor Simulation project aims to simulate the execution of ARM instructions and track the state of seven registers during the execution process. It is implemented in C++ and provides a command-line interface to interact with the simulation.

## Features

- Parsing and execution of various ARM instructions
- Tracking and updating the state of seven registers
- Error handling for invalid instructions, registers, and operands

## Getting Started

To get started with the ARM Processor Simulator, follow these steps:

1. Clone the repository:

   ```shell
   git clone https://github.com/hotcuppajojo/CS219-Project-3-ARM-Processor-Simulator.git
   ```
   
2. Navigate into the project directory:

   ```shell
   cd CS219-Project-3-ARM-Processor-Simulator
   ```


3. Compile the source code using the provided Makefile:

   ```shell
   make
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
MOV R1, #0X72DF9901
MOV R2, #0X2E0B484A
ADD R3, R1, R2
```

Example output:

```
MOV R1, #0X72DF9901
Register state:
CSPR: N=0 Z=0 C=0 V=0
R0: 0x00000000
R1: 0x72DF9901
R2: 0x00000000
R3: 0x00000000
R4: 0x00000000
R5: 0x00000000
R6: 0x00000000
R7: 0x00000000

MOV R2, #0X2E0B484A
Register state:
CSPR: N=0 Z=0 C=0 V=0
R0: 0x00000000
R1: 0x72DF9901
R2: 0x2E0B484A
R3: 0x00000000
R4: 0x00000000
R5: 0x00000000
R6: 0x00000000
R7: 0x00000000

ADD R3, R1, R2
Register state:
CSPR: N=1 Z=0 C=1 V=0
R0: 0x00000000
R1: 0x72DF9901
R2: 0x2E0B484A
R3: 0xA0EAE14B
R4: 0x00000000
R5: 0x00000000
R6: 0x00000000
R7: 0x00000000
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

This project is developed as part of the CS 219 course for project 3. The goal is to simulate the execution of ARM instructions using a custom ARM processor implementation with seven registers.

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

The ARM processor simulator is a practical tool designed to execute ARM instructions and provide a clear view of the internal workings of an ARM processor. Given a file with ARM instructions, the simulator executes these instructions in sequence, updating and displaying the state of seven registers after each operation.

To use the simulator, simply follow the provided usage instructions. The simulator can handle a variety of ARM instructions, including MOV, ADD, SUB, AND, ORR, XOR, LSL, LSR, and ASR. The software efficiently updates the register values and status flags (N, Z, C, V) in response to each instruction, providing a comprehensive view of the execution process.

Developed using C++, the simulator leverages the power of object-oriented programming. The `ARMProcessor` class serves as the core, handling the processor's functionalities. The `CSPR` and `Register` classes manage the Current Program Status Register and seven general-purpose registers, respectively.

The development process was anchored on a set of specific assignment requirements. These included parsing instructions from a file, validating the registers and operands, executing the operations, updating the register values and status flags, and displaying the register state after each instruction.

The simulator places a high emphasis on error handling. Invalid instructions, registers, or operands are identified, and the user is informed through clear error messages. This focus on error handling enhances the reliability and stability of the simulator.

The simulator was tested extensively using various sets of ARM instructions. This testing process verified the accuracy and reliability of the simulator by ensuring that the register state after each instruction execution matched expected outcomes.

The project adheres to good coding practices such as modular design, encapsulation, and code reusability. The code is organized into separate files based on functionality, facilitating maintainability and readability. Comments are incorporated throughout the code to provide context and explain functionality.

In conclusion, the ARM processor simulator is a useful tool for understanding the execution of ARM instructions. It is suitable for educational use or as a reference for studying processor architectures. The simulator demonstrates the parsing of instructions, execution of operations, and updating of register states, all while maintaining high coding standards and robust error handling.
