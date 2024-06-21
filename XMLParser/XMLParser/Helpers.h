#pragma once
#include "MyString.h"
#include <fstream>

MyString toString(size_t num);

size_t digsCount(size_t num);

char toChar(size_t digit);

MyString readAll(std::ifstream& ifs);