#include "XMLElementFactory.h"

IdList XMLElementFactory::list{};

XMLElement* XMLElementFactory::getElement(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open()) {
		return nullptr;
	}
	XMLElement* root = new XMLElement();
	root->setTag("root");
	root->setId("ID_ROOT");
	XMLElement* toRet = getElement(root, ifs);
	ifs.close();
	return toRet;
}

XMLElement* XMLElementFactory::getElement(XMLElement* parent, std::ifstream& ifs){
	MyString txt = "";
	char ch[2] = {0};
	while (true) {
		ch[0] = ifs.get();
		if (ifs.eof()) {
			break;
		}
		if (ch[0] == '<') {
			XMLElement elem;

			MyString tag = "";
			ifs >> tag;


		}
		else {
			txt += ch;
		}
	}
	return parent;
}
