#include "XMLElementFactory.h"

XMLElement* XMLElementFactory::getElement(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open()) {
		return nullptr;
	}
	XMLElement* root = new XMLElement();
	root->setTag("root");



	return root;
}

XMLElement* XMLElementFactory::getElement(XMLElement* parent, std::ifstream& ifs)
{
	return nullptr;
}
