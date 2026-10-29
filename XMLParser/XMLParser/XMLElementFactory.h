#pragma once

#include <fstream>
#include "XMLElement.h"
#include "IdList.h"

/**
 * Recursive parser for explicit paired tags and double-quoted attributes.
 * Successful create calls return caller-owned trees. Malformed XML is not
 * comprehensively validated and may throw; see README.md for supported input.
 */
class XMLElementFactory {
	static IdList list;

	static OrderedMap<MyString, MyString> parseAttributes(const StringView& v);
public:
	/// Load a file, adding a synthetic root; return nullptr if the file cannot open.
	static XMLElement* create(const char* fileName);

	/// Parse the remaining stream under a synthetic root, restoring the stream position.
	static XMLElement* create(std::ifstream& ifs);

	/// Parse XML text as one element, without adding the file-loading wrapper.
	static XMLElement* create(const MyString& str);

	/// Parse borrowed XML text; the returned tree stores owning strings.
	static XMLElement* create(const StringView& str);

	/// Parse at pos and advance it past the closing tag of a complete element.
	static XMLElement* create(const StringView& str, size_t& pos);
};
