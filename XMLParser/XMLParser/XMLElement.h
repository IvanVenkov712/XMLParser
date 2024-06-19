#pragma once
#include "Polymorphic_Container.h"
#include "OrderedMap.h"
#include "MyString.h"
#include "StringView.h"
#include <iostream>

class XMLElement {
public:
	using ElemPtr = Polymorphic_Ptr<XMLElement>;

protected:
	ElemPtr parent;
	MyString id = "";
	OrderedMap<MyString, MyString> attributes;
	Vector<ElemPtr> children;
	MyString text = "";
	MyString name = "";

public:

	virtual void setParent(const ElemPtr& parent);

	virtual void setParent(ElemPtr&& parent);

	virtual void setId(const MyString& id);

	virtual void setId(MyString&& id);

	virtual void setTag(const MyString& name);

	virtual void setTag(MyString&& name);

	virtual const MyString& getName() const;

	virtual XMLElement* clone() const;

	virtual void setText(const MyString& text);

	virtual void setText(MyString&& text);

	const MyString& getText() const;

	virtual const MyString& getId() const;

	virtual bool hasAttribute(const MyString& name) const;

	virtual const MyString& getAttribute(const MyString& name) const;

	virtual void addAttribute(const MyString& name, const MyString& value);

	virtual void setAttribute(const MyString& name, const MyString& value);

	virtual void removeAttribute(const MyString& key);

	virtual XMLElement* getParent();

	virtual const XMLElement* getParent() const;

	virtual size_t childrenCount() const;

	virtual XMLElement* childAt(size_t at);

	virtual const XMLElement* childAt(size_t at) const;

	virtual int findChild(const MyString& childId) const;

	virtual void addChild(ElemPtr&& elem);

	virtual void addChild(const ElemPtr& elem);

	virtual void insertChild(size_t at, ElemPtr&& elem);

	virtual void insertChild(size_t at, const ElemPtr& elem);

	virtual ~XMLElement() = default;

	virtual void save(std::ostream& os, unsigned int indentCount) const;

	friend std::ostream& operator<<(std::ostream& os, const XMLElement& elem);
};