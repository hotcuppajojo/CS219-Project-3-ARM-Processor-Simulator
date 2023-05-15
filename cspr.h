/** Project 3 - CS 219
    File: cspr.h
    Author: JoJo Petersky
*/
// Header guard to prevent multiple inclusion of the header
#ifndef CSPR_H
#define CSPR_H
// CSPR class representing the status flags
class CSPR {
private:
    bool nFlag;  // Negative flag
    bool zFlag;  // Zero flag
    bool cFlag;  // Carry flag
    bool vFlag;  // Overflow flag
public:
    // Constructor
    CSPR();
    // Negative flag methods
    bool getNFlag() const;
    void setNFlag(bool flag);
    // Zero flag methods
    bool getZFlag() const;
    void setZFlag(bool flag);
    // Carry flag methods
    bool getCFlag() const;
    void setCFlag(bool flag);
    // Overflow flag methods
    bool getVFlag() const;
    void setVFlag(bool flag);
};
#include "cspr.cpp" // Include the implementation file
#endif // End of the header guard