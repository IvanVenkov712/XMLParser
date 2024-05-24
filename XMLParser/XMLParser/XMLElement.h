#pragma once
#include "OrderedMap.h"
#include "MyString.h"



class IXMLElement {
protected:
	virtual void setParent(IXMLElement* parent) = 0;

public:
	virtual const MyString& getId() const = 0;

	virtual IXMLElement* clone() const = 0;

	virtual bool hasAttribute(const MyString& name) const = 0;

	virtual const MyString& getAttribute(const MyString& name) const = 0;

	virtual void addAttribute(const MyString& name, const MyString& value) = 0;

	virtual void setAttribute(const MyString& name, const MyString& value) = 0;

	virtual IXMLElement* getParent() = 0;

	virtual const IXMLElement* getParent() const = 0;

	virtual IXMLElement* childAt() = 0;

	virtual const IXMLElement* childAt() const = 0;

	virtual void addChild(IXMLElement* elem) = 0;

	virtual void insertChild(size_t at, IXMLElement* elem) = 0;

	virtual ~IXMLElement() = default;
};