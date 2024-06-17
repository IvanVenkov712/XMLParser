#pragma once
#include "Polymorphic_Container.h"
#include "OrderedMap.h"
#include "MyString.h"

class XMLElement {
public:
	using ElemPtr = Polymorphic_Ptr<XMLElement>;

protected:
	ElemPtr parent;
	MyString id = "";
	OrderedMap<MyString, MyString> attributes;
	Vector<ElemPtr> children;
	MyString text = "";

	virtual void setParent(const ElemPtr& parent);

	virtual void setParent(ElemPtr&& parent);

	virtual void setId(const MyString& id);

	virtual void setId(MyString&& id);

public:
	virtual XMLElement* clone() const;

	virtual const MyString& getId() const;

	virtual bool hasAttribute(const MyString& name) const;

	virtual const MyString& getAttribute(const MyString& name) const;

	virtual void addAttribute(const MyString& name, const MyString& value);

	virtual void setAttribute(const MyString& name, const MyString& value);

	virtual ElemPtr& getParent();

	virtual const ElemPtr& getParent() const;

	virtual size_t childrenCount() const;

	virtual ElemPtr& childAt(size_t at);

	virtual const ElemPtr& childAt(size_t at) const;

	virtual int findChild(const MyString& childId) const;

	virtual void addChild(ElemPtr&& elem);

	virtual void addChild(const ElemPtr& elem);

	virtual void insertChild(size_t at, ElemPtr&& elem);

	virtual void insertChild(size_t at, const ElemPtr& elem);

	virtual ~XMLElement() = default;
};