#pragma once
#include "Polymorphic_Container.h"
#include "OrderedMap.h"
#include "MyString.h"
#include "StringView.h"
#include "Predicate.h"
#include <iostream>

class XMLElement {
public:
	class IdPredicate : public Predicate<XMLElement> {
		MyString id;
	public:
		IdPredicate(const MyString& id);

		IdPredicate(MyString&& id);

		bool operator()(const XMLElement& elem) const override;
	};
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

	virtual void setName(const MyString& name);

	virtual void setName(MyString&& name);

	virtual const MyString& getName() const;

	virtual XMLElement* clone() const;

	virtual void setText(const MyString& text);

	virtual void setText(MyString&& text);

	virtual const MyString& getText() const;

	virtual const MyString& getId() const;

	virtual bool hasAttribute(const MyString& name) const;

	virtual const MyString& getAttribute(const MyString& name) const;

	virtual void addAttribute(const MyString& name, const MyString& value);

	virtual void setAttribute(const MyString& name, const MyString& value);

	virtual void removeAttribute(const MyString& key);

	virtual void setAttributes(const OrderedMap<MyString, MyString>& attributes);

	virtual void setAttributes(OrderedMap<MyString, MyString>&& attributes);

	virtual OrderedMap<MyString, MyString>& getAttributes();

	virtual const OrderedMap<MyString, MyString>& getAttributes() const;

	virtual XMLElement* getParent();

	virtual const XMLElement* getParent() const;

	virtual size_t childrenCount() const;

	virtual XMLElement* childAt(size_t at);

	virtual const XMLElement* childAt(size_t at) const;

	virtual int findChild(const MyString& childId) const;

	virtual XMLElement* findInTree(const Predicate<XMLElement>& pr);

	virtual const XMLElement* findInTree(const Predicate<XMLElement>& pr) const;

	virtual XMLElement* findInTreeById(const MyString& id);

	virtual const XMLElement* findInTreeById(const MyString& id) const;

	virtual void addChild(ElemPtr&& elem);

	virtual void addChild(const ElemPtr& elem);

	virtual void insertChild(size_t at, ElemPtr&& elem);

	virtual void insertChild(size_t at, const ElemPtr& elem);

	virtual ~XMLElement() = default;

	virtual void save(std::ostream& os, unsigned int indentCount = 0) const;

	friend std::ostream& operator<<(std::ostream& os, const XMLElement& elem);
};