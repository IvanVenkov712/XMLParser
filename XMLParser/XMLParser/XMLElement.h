#pragma once
#include "Polymorphic_Container.h"
#include "OrderedMap.h"
#include "MyString.h"
#include "StringView.h"
#include "Predicate.h"
#include <iostream>

/**
 * An XML node with key-sorted attributes, leaf text, and owned child nodes.
 * Copies clone owned pointers. Child insertion does not populate parent links.
 */
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
	// This is an owning, cloning pointer, not a borrowed parent back-reference.
	// Parsed trees leave it empty; never give it an already-owned parent address.
	ElemPtr parent;
	OrderedMap<MyString, MyString> attributes;
	Vector<ElemPtr> children;
	MyString text = "";
	MyString name = "";

public:

	XMLElement();

	virtual void setParent(const ElemPtr& parent);

	virtual void setParent(ElemPtr&& parent);

	virtual void setId(const MyString& id);

	virtual void setId(MyString&& id);

	virtual void setName(const MyString& name);

	virtual void setName(MyString&& name);

	virtual const MyString& getName() const;

	/// Allocate a copy, including cloned children; the caller owns the result.
	virtual XMLElement* clone() const;

	virtual void setText(const MyString& text);

	virtual void setText(MyString&& text);

	/// Return only this node's stored text, without concatenating descendants.
	virtual const MyString& getText() const;

	virtual const MyString& getId() const;

	virtual bool hasAttribute(const MyString& name) const;

	/// Throw std::invalid_argument when the attribute is absent.
	virtual const MyString& getAttribute(const MyString& name) const;

	virtual void addAttribute(const MyString& name, const MyString& value);

	virtual void setAttribute(const MyString& name, const MyString& value);

	/// Reject removal of "id"; other keys are delegated to OrderedMap::removeAt.
	virtual void removeAttribute(const MyString& key);

	virtual void setAttributes(const OrderedMap<MyString, MyString>& attributes);

	virtual void setAttributes(OrderedMap<MyString, MyString>&& attributes);

	virtual OrderedMap<MyString, MyString>& getAttributes();

	virtual const OrderedMap<MyString, MyString>& getAttributes() const;

	virtual XMLElement* getParent();

	virtual const XMLElement* getParent() const;

	virtual size_t childrenCount() const;

	/// Return a borrowed child pointer; at must be less than childrenCount().
	virtual XMLElement* childAt(size_t at);

	virtual const XMLElement* childAt(size_t at) const;

	/// Return the direct child's zero-based index, or -1 when absent.
	virtual int findChild(const MyString& childId) const;

	/// Search this node, then descendants in preorder; return a borrowed match or null.
	virtual XMLElement* findInTree(const Predicate<XMLElement>& pr);

	virtual const XMLElement* findInTree(const Predicate<XMLElement>& pr) const;

	virtual XMLElement* findInTreeById(const MyString& id);

	virtual const XMLElement* findInTreeById(const MyString& id) const;

	/// Transfer ownership of elem to the children vector; leave parent links unchanged.
	virtual void addChild(ElemPtr&& elem);

	/// Append a clone of elem and its subtree.
	virtual void addChild(const ElemPtr& elem);

	/// Insert before an existing child (at < childrenCount()); use addChild to append.
	virtual void insertChild(size_t at, ElemPtr&& elem);

	virtual void insertChild(size_t at, const ElemPtr& elem);

	virtual ~XMLElement() = default;

	/// Serialize this subtree with four additional spaces per child level; no XML escaping.
	virtual void save(std::ostream& os, unsigned int indentCount = 0) const;

	friend std::ostream& operator<<(std::ostream& os, const XMLElement& elem);
};
