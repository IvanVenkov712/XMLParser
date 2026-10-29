#include "XMLElementFactory.h"

OrderedMap<MyString, MyString> XMLElementFactory::parseAttributes(const StringView& v)
{
	OrderedMap<MyString, MyString> attributes;
	size_t pos = 0;
	while (pos < v.length()) {
		int eqPos = v.findFirst(pos, '=');
		if (eqPos < 0) break;

		MyString name = v.substr(pos, eqPos - pos).trim().toString();
		// Attribute values are delimited by double quotes; entities are kept verbatim.
		int quotePos = v.findFirst( eqPos + 1, '"');
		int endQuotePos = v.findFirst(quotePos + 1, '"');

		MyString value = v.substr(quotePos + 1, endQuotePos - quotePos - 1).toString();
		attributes[name] = value;

		pos = endQuotePos + 1;
	}
    // Every parsed element gets an ID, even when the source omitted one.
    if (attributes.exists("id")) {
        attributes["id"] = IdList::getId(attributes["id"]);
    }
    else {
        attributes["id"] = IdList::getId();
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
    // File input may have multiple top-level elements. The console hides this wrapper.
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
        element->setId(IdList::getId());
    }

    int closeTagStart = str.findFirst(openTagEnd + 1, '<');
    if (closeTagStart < 0) {
        return element;
    }
    // The next tag decides between leaf text and child nodes; mixed content is lost.
    if (str[closeTagStart + 1] == '/') {
        size_t closeTagEnd = str.findFirst( closeTagStart, '>');
        element->setText(str.substr(openTagEnd + 1, closeTagStart - openTagEnd - 1).trim().toString());
        pos = closeTagEnd + 1;
    }
    else {
        pos = closeTagStart;
        // Recursive calls advance pos past each child; skip inter-element whitespace.
        // The closing tag's name is not compared with the opening tag's name.
        while (str[pos] != '<' || str[pos + 1] != '/') {
            element->addChild(create(str, pos));
            pos = str.findFirstNotOf(pos, " \n\t\v\r");
        }
        size_t closeTagEnd = str.findFirst(pos, '>');
        pos = closeTagEnd + 1;
    }

    return element;
}
