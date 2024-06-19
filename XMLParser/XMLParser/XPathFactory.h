#pragma once
#include "ElementFunction.h"
#include "MyString.h"

class XPathFactory {
public:
	static XPathQuery* create(const MyString& queryString);
};