#pragma once
#include "OrderedMap.h"
#include "MyString.h"



class IXMLElement {
public:
	virtual IXMLElement* clone() const = 0;

	virtual bool hasAttribute(const MyString& name) const = 0;

	virtual const MyString& getAttribute(const MyString& name) const = 0;



};