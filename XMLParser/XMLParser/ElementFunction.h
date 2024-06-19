#pragma once
#include "XMLElement.h"

class ElementFunction {
public:
	static void traverseElementTree(const XMLElement* elem, ElementFunction& traversalFunction);

	virtual void operator()(const XMLElement* elem) = 0;

	virtual ElementFunction* clone() const = 0;

	virtual ~ElementFunction() = default;

};

class FunWrapper : public ElementFunction {
	void (*funPtr)(const XMLElement* elem);

public:
	FunWrapper(void (*funPtr)(const XMLElement* elem));

	void operator()(const XMLElement* elem) override;

	ElementFunction* clone() const override;
};

class XPathQuery : public ElementFunction {
protected:
	Vector<MyString> _result;

public:

	Vector<MyString>& result();

	const Vector<MyString>& result() const;

};

class PathQuery : public XPathQuery {
	MyString parentName;
	MyString childName;

public:
	PathQuery(const MyString& parentName, const MyString& childName);

	PathQuery(MyString&& parentName, const MyString& childName);

	PathQuery(const MyString& parentName, MyString&& childName);

	PathQuery(MyString&& parentName, MyString&& childName);

	void operator()(const XMLElement* elem) override;

	ElementFunction* clone() const override;
};

class AttribQuery : public XPathQuery {
	MyString elemName;
	MyString attribName;

public:

	AttribQuery(const MyString& elemName, const MyString& attribName);

	void operator()(const XMLElement* elem) override;

	ElementFunction* clone() const override;
};

class ComparisonQuery : public XPathQuery {
	MyString elemName;
	MyString childName;
	MyString childValue;
	MyString childToSelect;

public:
	ComparisonQuery(const MyString& elemName, const MyString& childName, const MyString& childValue, const MyString& childToSelect);

	void operator()(const XMLElement* elem) override;

	ElementFunction* clone() const override;
};
