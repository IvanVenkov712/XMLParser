#include "StringView.h"

StringView::StringView(const char* begin, const char* end) : _begin(begin), _end(end)
{}

StringView::StringView(const char* str) : StringView(str, str + strlen(str)) {}

StringView::StringView(const MyString& str) : StringView(str.c_str()) {}

size_t StringView::length() const
{
	return _end - _begin;
}
char StringView::operator[](size_t index) const
{
	if (index >= length()) {
		throw std::out_of_range("index not less than size");
	}
	return _begin[index];
}

StringView StringView::substr(size_t from, size_t length) const
{
	if (_begin + from + length > _end)
		throw std::length_error("Error, Substr out of range");

	return StringView(_begin + from, _begin + from + length);
}

int StringView::findFirst(size_t offset, char ch) const
{
	for (const char* i = _begin + offset; i < _end; ++i) {
		if (*i == ch) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findLast(size_t offset, char ch) const
{
	for (const char* i = _end - 1 - offset; i >= _begin; --i) {
		if (*i == ch) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findFirst(size_t offset, const StringView& substr) const
{
	size_t substrLen = substr.length();
	if (length() - offset < substrLen) {
		return -1;
	}
	for (const char* i = _begin + offset; i < _end - substrLen; ++i) {
		if (strncmp(i, substr._begin, substrLen) == 0) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findLast(size_t offset, const StringView& substr) const
{
	size_t substrLen = substr.length();
	if (length() - offset < substrLen) {
		return -1;
	}
	for (const char* i = _end - substrLen - 1 - offset; i >= _begin; --i) {
		if (strncmp(i, substr._begin, substrLen) == 0) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findFirstOf(size_t offset, const StringView& chars) const
{
	for (const char* i = _begin + offset; i < _end; ++i) {
		if (chars.findFirst(*i) >= 0) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findLastOf(size_t offset, const StringView& chars) const
{
	for (const char* i = _end - 1 - offset; i >= _begin; --i) {
		if (chars.findFirst(*i) >= 0) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findFirstNotOf(size_t offset, const StringView& chars) const
{
	for (const char* i = _begin + offset; i < _end; ++i) {
		if (chars.findFirst(*i) < 0) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findLastNotOf(size_t offset, const StringView& chars) const
{
	for (const char* i = _end - 1 - offset; i >= _begin; --i) {
		if (chars.findFirst(*i) < 0) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findFirst(char ch) const
{
	return findFirst(0, ch);
}

int StringView::findLast(char ch) const
{
	return findLast(0, ch);
}

int StringView::findFirst(const StringView& substr) const
{
	return findFirst(0, substr);
}

int StringView::findLast(const StringView& substr) const
{
	return findLast(0, substr);
}

int StringView::findFirstOf(const StringView& chars) const
{
	return findFirstOf(0, chars);
}

int StringView::findLastOf(const StringView& chars) const
{
	return findLastOf(0, chars);
}

int StringView::findFirstNotOf(const StringView& chars) const
{
	return findFirstNotOf(0, chars);
}

int StringView::findLastNotOf(const StringView& chars) const
{
	return findLastNotOf(0, chars);
}

StringView StringView::trim() const
{
	return substr(findFirstNotOf(wSpaces), findLastOf(wSpaces));
}

MyString StringView::toString() const
{
	return MyString(_begin, _end - _begin);
}

std::ostream& operator<<(std::ostream& os, const StringView& strView)
{
	const char* iter = strView._begin;

	while (iter != strView._end)
	{
		os << *iter;
		iter++;
	}
	return os;
}


bool operator==(const StringView& lhs, const StringView& rhs)
{
	if (lhs.length() != rhs.length()) {
		return false;
	}
	return std::strncmp(lhs._begin, rhs._begin, lhs.length()) == 0;
}

bool operator!=(const StringView& lhs, const StringView& rhs)
{
	if (lhs.length() != rhs.length()) {
		return true;
	}
	return std::strncmp(lhs._begin, rhs._begin, lhs.length()) != 0;
}

bool operator<(const StringView& lhs, const StringView& rhs)
{
	if (lhs.length() > rhs.length()) {
		return false;
	}
	if (lhs.length() < rhs.length()) {
		return true;
	}
	return std::strncmp(lhs._begin, rhs._begin, lhs.length()) < 0;
}

bool operator<=(const StringView& lhs, const StringView& rhs)
{
	if (lhs.length() > rhs.length()) {
		return false;
	}
	if (lhs.length() < rhs.length()) {
		return true;
	}
	return std::strncmp(lhs._begin, rhs._begin, lhs.length()) <= 0;
}

bool operator>(const StringView& lhs, const StringView& rhs)
{
	if (lhs.length() > rhs.length()) {
		return true;
	}
	if (lhs.length() < rhs.length()) {
		return false;
	}
	return std::strncmp(lhs._begin, rhs._begin, lhs.length()) > 0;
}

bool operator>=(const StringView& lhs, const StringView& rhs)
{
	if (lhs.length() > rhs.length()) {
		return true;
	}
	if (lhs.length() < rhs.length()) {
		return false;
	}
	return std::strncmp(lhs._begin, rhs._begin, lhs.length()) >= 0;
}
