#include "Helpers.h"

MyString toString(size_t num)
{
	char dig[2] = { 0 };
	if (num <= 10) {
		dig[0] = toChar(num);
		return MyString(dig);
	}
	MyString res;
	while (num > 0) {
		dig[0] = toChar(num % 10);
		res = MyString(dig) + res;
		num /= 10;
	}
	return res;
}

size_t digsCount(size_t num)
{
	if (num == 0) {
		return 1;
	}
	size_t n = 0;
	while (num % 10 != 0) {
		++n;
		num /= 10;
	}
	return n;
}

char toChar(size_t digit)
{
	if (digit >= 0 && digit <= 9) {
		return digit + '0';
	}
	throw std::invalid_argument("digit out of range");
}

MyString readAll(std::ifstream& ifs)
{
	MyString res;
	size_t currPos = ifs.tellg();
	char c = '\0';
	while (true) {
		c = ifs.get();
		if (ifs.eof()) {
			break;
		}
		res.pushBack(c);
	}
	ifs.clear();
	ifs.seekg(currPos);
	return res;
}
