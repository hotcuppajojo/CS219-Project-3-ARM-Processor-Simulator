/** Project 3 - CS 219
    File: cspr.cpp
    Author: JoJo Petersky
*/
// Include necessary headers
#include "cspr.h"
// Constructor initializes the flags to false
CSPR::CSPR() : nFlag(false), zFlag(false), cFlag(false), vFlag(false) {
}
// Negative flag methods
bool CSPR::getNFlag() const {
    return nFlag;
}
void CSPR::setNFlag(bool flag) {
    nFlag = flag;
}
// Zero flag methods
bool CSPR::getZFlag() const {
    return zFlag;
}
void CSPR::setZFlag(bool flag) {
    zFlag = flag;
}
// Carry flag methods
bool CSPR::getCFlag() const {
    return cFlag;
}
void CSPR::setCFlag(bool flag) {
    cFlag = flag;
}
// Overflow flag methods
bool CSPR::getVFlag() const {
    return vFlag;
}
void CSPR::setVFlag(bool flag) {
    vFlag = flag;
}