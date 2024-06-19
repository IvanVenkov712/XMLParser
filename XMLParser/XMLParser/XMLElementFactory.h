#pragma once

#include <fstream>
#include "XMLElement.h"
#include "IdList.h"

class XMLElementFactory {
	static IdList list;
public:
	static XMLElement* create(const char* fileName);

	static XMLElement* create(XMLElement* parent, std::ifstream& ifs);
};