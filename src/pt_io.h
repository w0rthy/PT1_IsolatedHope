#pragma once

#include <iostream>
#include <fstream>

int readCmpInt(std::istream* str);
void writeCmpInt(std::ostream* str, int num);

double readCmpFlt(std::istream* str);
void writeCmpFlt(std::ostream* str, double num);

char* readString(std::istream* str);
void writeString(std::ostream* str, char* s);