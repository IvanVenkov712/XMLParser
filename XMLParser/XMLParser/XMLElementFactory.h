#pragma once

#include <fstream>
#include "XMLElement.h"
#include "IdList.h"

class XMLElementFactory {
	static IdList list;

	static OrderedMap<MyString, MyString> parseAttributes(const StringView& v);
public:
	static XMLElement* create(const char* fileName);

	static XMLElement* create(std::ifstream& ifs);

	static XMLElement* create(const MyString& str);

	static XMLElement* create(const StringView& str);

	static XMLElement* create(const StringView& str, size_t& pos);
};