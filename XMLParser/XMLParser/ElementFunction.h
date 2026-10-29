#pragma once
#include "XMLElement.h"

/// Polymorphic callback applied to nodes during a read-only tree traversal.
class ElementFunction {
public:
	/// Visit elem before its children, in child order. elem must be non-null.
	static void traverseElementTree(const XMLElement* elem, ElementFunction& traversalFunction);

	virtual void operator()(const XMLElement* elem) = 0;

	virtual ElementFunction* clone() const = 0;

	virtual ~ElementFunction() = default;

};

/// Adapt a non-null free-function pointer to the traversal callback interface.
class FunWrapper : public ElementFunction {
	void (*funPtr)(const XMLElement* elem);

public:
	FunWrapper(void (*funPtr)(const XMLElement* elem));

	void operator()(const XMLElement* elem) override;

	ElementFunction* clone() const override;
};

/// Query base whose string results accumulate until explicitly cleared or destroyed.
class XPathQuery : public ElementFunction {
protected:
	Vector<MyString> _result;

public:

	Vector<MyString>& result();

	const Vector<MyString>& result() const;
};

/// Collect text from named direct children of nodes matching parentName.
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

/// Collect an attribute value from each node matching elemName.
class AttribQuery : public XPathQuery {
	MyString elemName;
	MyString attribName;

public:

	AttribQuery(const MyString& elemName, const MyString& attribName);

	void operator()(const XMLElement* elem) override;

	ElementFunction* clone() const override;
};

/// Select child text when a sibling with the requested name and text exists.
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
