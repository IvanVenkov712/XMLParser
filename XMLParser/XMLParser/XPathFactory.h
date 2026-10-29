#pragma once
#include "ElementFunction.h"
#include "MyString.h"

/// Parse the small XPath-style syntax described in README.md, not general XPath.
class XPathFactory {
public:
	/// Return a caller-owned query, or nullptr when the expression is rejected.
	static XPathQuery* create(const MyString& queryString);
};
