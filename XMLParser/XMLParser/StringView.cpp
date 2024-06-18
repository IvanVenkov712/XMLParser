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
	return _begin[index];
}

StringView StringView::substr(size_t from, size_t length) const
{
	if (_begin + from + length > _end)
		throw std::length_error("Error, Substr out of range");

	return StringView(_begin + from, _begin + from + length);
}

int StringView::findFirst(char ch) const
{
	for (const char* i = _begin; i < _end; ++i) {
		if (*i == ch) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findLast(char ch) const
{
	for (const char* i = _end - 1; i >= _begin; --i) {
		if (*i == ch) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findFirst(const StringView& substr) const
{
	size_t substrLen = substr.length();
	if (length() < substrLen) {
		return -1;
	}
	for (const char* i = _begin; i < _end - substrLen; ++i) {
		if (strncmp(i, substr._begin, substrLen) == 0) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findLast(const StringView& substr) const
{
	size_t substrLen = substr.length();
	if (length() < substrLen) {
		return -1;
	}
	for (const char* i = _end - substrLen - 1; i >= _begin; --i) {
		if (strncmp(i, substr._begin, substrLen) == 0) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findFirstOf(const StringView& chars) const
{
	for (const char* i = _begin; i < _end; ++i) {
		if (chars.findFirst(*i) >= 0) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findLastOf(const StringView& chars) const
{
	for (const char* i = _end - 1; i < _begin; --i) {
		if (chars.findFirst(*i) >= 0) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findFirstNotOf(const StringView& chars) const
{
	for (const char* i = _begin; i < _end; ++i) {
		if (chars.findFirst(*i) < 0) {
			return i - _begin;
		}
	}
	return -1;
}

int StringView::findLastNotOf(const StringView& chars) const
{
	for (const char* i = _end - 1; i < _begin; --i) {
		if (chars.findFirst(*i) < 0) {
			return i - _begin;
		}
	}
	return -1;
}

StringView StringView::trim() const
{
	return substr(findFirstNotOf(wSpaces), findLastOf(wSpaces));
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
