#include "XMLElementFactory.h"

OrderedMap<MyString, MyString> XMLElementFactory::parseAttributes(const StringView& v)
{
	OrderedMap<MyString, MyString> attributes;
	size_t pos = 0;
	while (pos < v.length()) {
		int eqPos = v.findFirst(pos, '=');
		if (eqPos < 0) break;

		MyString name = v.substr(pos, eqPos - pos).trim().toString();
		int quotePos = v.findFirst( eqPos + 1, '"');
		int endQuotePos = v.findFirst(quotePos + 1, '"');

		MyString value = v.substr(quotePos + 1, endQuotePos - quotePos - 1).toString();
		attributes[name] = value;

		pos = endQuotePos + 1;
	}
	return attributes;
}

XMLElement* XMLElementFactory::create(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open()) {
		return nullptr;
	}
	XMLElement* res = create(ifs);
	ifs.close();
	return res;
}

XMLElement* XMLElementFactory::create(std::ifstream& ifs)
{
	MyString str = readAll(ifs);
    str = "<root id=\"ROOT\">" + str + "</root>";
	return create(str);
}

XMLElement* XMLElementFactory::create(const MyString& str)
{
	StringView view(str);
	return create(view);
}

XMLElement* XMLElementFactory::create(const StringView& str)
{
	size_t pos = 0;
	return create(str, pos);
}

XMLElement* XMLElementFactory::create(const StringView& str, size_t& pos)
{
    XMLElement* element = new XMLElement();
    size_t openTagStart = str.findFirst(pos, '<');
    size_t openTagEnd = str.findFirst(openTagStart, '>');
    StringView tagContent = str.substr(openTagStart + 1, openTagEnd - openTagStart - 1);

    int spacePos = tagContent.findFirst(' ');
    if (spacePos >= 0) {
        element->setName(tagContent.substr(0, spacePos).toString());
        StringView attributesStr = tagContent.substr(spacePos + 1, tagContent.length() - spacePos - 1);
        element->setAttributes(parseAttributes(attributesStr));
    }
    else {
        element->setName(tagContent.toString());
    }

    int closeTagStart = str.findFirst(openTagEnd + 1, '<');
    if (closeTagStart < 0) {
        return element;
    }
    if (str[closeTagStart + 1] == '/') {
        size_t closeTagEnd = str.findFirst( closeTagStart, '>');
        element->setText(str.substr(openTagEnd + 1, closeTagStart - openTagEnd - 1).trim().toString());
        pos = closeTagEnd + 1;
    }
    else {
        pos = closeTagStart;
        while (str[pos] != '<' || str[pos + 1] != '/') {
            element->addChild(create(str, pos));
            pos = str.findFirstNotOf(pos, " \n\t\v\r");
        }
        size_t closeTagEnd = str.findFirst(pos, '>');
        pos = closeTagEnd + 1;
    }

    return element;
}
