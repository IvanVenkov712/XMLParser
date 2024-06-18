#pragma once
#include <fstream>
#include "MyString.h"
class StringView
{
	static constexpr const char* wSpaces = " \t\n\r\v\f";

	const char* _begin;
	const char* _end; //1 element after the final char;

public:
	StringView(const char* begin, const char* end);
	StringView(const char* str); //terminatedString
	StringView(const MyString& string);

	size_t length() const;
	char operator[](size_t ind) const;

	StringView substr(size_t from, size_t length) const;

	int findFirst(char ch) const;

	int findLast(char ch) const;

	int findFirst(const StringView& substr) const;

	int findLast(const StringView& substr) const;

	int findFirstOf(const StringView& chars) const;

	int findLastOf(const StringView& chars) const;

	int findFirstNotOf(const StringView& chars) const;

	int findLastNotOf(const StringView& chars) const;

	StringView trim() const;

	friend bool operator==(const StringView& lhs, const StringView& rhs);

	friend bool operator!=(const StringView& lhs, const StringView& rhs);

	friend bool operator<(const StringView& lhs, const StringView& rhs);

	friend bool operator<=(const StringView& lhs, const StringView& rhs);

	friend bool operator>(const StringView& lhs, const StringView& rhs);

	friend bool operator>=(const StringView& lhs, const StringView& rhs);

	friend std::ostream& operator<<(std::ostream&, const StringView& strView);

};
