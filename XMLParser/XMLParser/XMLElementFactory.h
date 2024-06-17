#pragma once

#include <fstream>
#include "XMLElement.h"

class XMLElementFactory {
public:
	static XMLElement* getElement(const char* fileName);

	static XMLElement* getElement(XMLElement* parent, std::ifstream& ifs);
};