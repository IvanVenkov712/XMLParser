#pragma once
#include <sstream>
#include "MyString.h"
#include "OrderedMap.h"
#include "Helpers.h"

class IdList {
private:
	static OrderedMap<MyString, size_t> idMap;
public:
	static MyString getId(const MyString& docId);

	static MyString getId();
};