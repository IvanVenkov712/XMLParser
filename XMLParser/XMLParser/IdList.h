#pragma once
#include <sstream>
#include "MyString.h"
#include "OrderedMap.h"

class IdList {
private:
	OrderedMap<MyString, size_t> idMap;
public:
	MyString getId(const MyString& docId);

	MyString getId();
};