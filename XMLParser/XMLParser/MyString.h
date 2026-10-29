#pragma once
#include <iostream>
#include <cstring>

/// Owning null-terminated string; copies duplicate storage and moves transfer it.
class MyString
{
public:
	MyString();
	MyString(const char* data);
	MyString(const char* data, size_t n);

	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;

	MyString& operator=(const MyString& other);

	MyString& operator=(MyString&& other) noexcept;
	~MyString();

	size_t getCapacity() const;
	size_t getSize() const;

	/// Borrow the buffer until mutation or destruction; moved-from storage is null.
	const char* c_str() const;

	void pushBack(char ch);

	MyString& operator+=(const MyString& other);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
	friend std::istream& operator>>(std::istream& is, MyString& ref);
	friend MyString operator+(const MyString& lhs, const MyString& rhs);

private:
	explicit MyString(size_t stringLength);
	void resize(unsigned newAllocatedDataSize);

	void free();
	void copyFrom(const MyString& other);

	void moveFrom(MyString&& other);

	char* _data;
	size_t _size;
	size_t _allocatedDataSize;
};

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);

/// Replace str with characters through delim or EOF; consume but do not store delim.
/// Leading whitespace is preserved, including a newline left by formatted input.
std::istream& myGetLine(std::istream& is, MyString& str, char delim = '\n');
