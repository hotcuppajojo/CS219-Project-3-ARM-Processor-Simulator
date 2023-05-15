# Project 3 - CS 219
# File: Makefile
# Author: JoJo Petersky

# Target: Proj3
# Compile and link 'main.o' into an executable named 'Proj3'.
Proj3: main.o
	g++ -o Proj3 main.o

# Target: main.o
# Compile 'main.cpp' into an object file named 'main.o'.
# Dependencies: 'main.cpp' and 'armprocessor.h'.
main.o: main.cpp armprocessor.h
	g++ -c main.cpp -std=c++17

# Target: clean
# Remove all object files and the executable 'Proj3'.
clean:
	rm *.o Proj3