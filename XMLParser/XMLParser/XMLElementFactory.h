#pragma once

#include <fstream>
#include "XMLElement.h"
#include "IdList.h"

class XMLElementFactory {
	static IdList list;
public:
	static XMLElement* getElement(const char* fileName);

	static XMLElement* getElement(XMLElement* parent, std::ifstream& ifs);
};