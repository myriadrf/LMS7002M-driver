/**
@file 	CommonUtilities.h
@author Lime Microsystems
@brief 	Header for CommonUtilities.cpp
*/

#ifndef COMMON_UTILITIES_H
#define COMMON_UTILITIES_H

#include <string>
using namespace std;

/** @brief Common utility functions used by logic and GUI
*/

void milSleep(unsigned int miliseconds);
long getMilis();
int hex2int(const string hex);
string short2hex(unsigned short i);
string int2hex(int i, int sizeBytes = 1);
string uint2hex(unsigned int i, int sizeBytes = 1);

int twoComplementToIndex(unsigned int twosCompl, int bitCount);
unsigned int indexToTwoComplement(int index, int bitCount);

#endif // COMMON_UTILITIES_H

