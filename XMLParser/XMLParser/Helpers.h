#pragma once
#include "MyString.h"
#include <fstream>

/// Decimal conversion helper; the current num <= 10 branch rejects 10 via toChar.
MyString toString(size_t num);

/// Legacy helper: counts divisions until a trailing zero is reached (zero returns 1).
size_t digsCount(size_t num);

/// Convert one decimal digit in [0, 9]; throw std::invalid_argument otherwise.
char toChar(size_t digit);

/// Read to EOF, then clear stream flags and restore the original get position.
MyString readAll(std::ifstream& ifs);
