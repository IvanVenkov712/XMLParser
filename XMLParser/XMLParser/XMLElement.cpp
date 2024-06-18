#include "XMLElement.h"


void XMLElement::pathOperator(const MyString& parentTag, const MyString& childTag, Vector<XMLElement*>& list)
{
	if (getName() == parentTag) {
		for (size_t i = 0; i < childrenCount(); ++i) {
			if (childAt(i)->getName() == childTag) {
				list.pushBack(childAt(i));
			}
		}
	}
	for (size_t i = 0; i < childrenCount(); ++i) {
		childAt(i)->pathOperator(parentTag, childTag, list);
	}
}

void XMLElement::pathOperator(const MyString& parentTag, const MyString& childTag, Vector<const XMLElement*>& list) const
{
	if (getName() == parentTag) {
		for (size_t i = 0; i < childrenCount(); ++i) {
			if (childAt(i)->getName() == childTag) {
				list.pushBack(childAt(i));
			}
		}
	}
	for (size_t i = 0; i < childrenCount(); ++i) {
		childAt(i)->pathOperator(parentTag, childTag, list);
	}
}

void XMLElement::operatorAt(const MyString& name, const MyString& attrib, Vector<MyString>& list) const
{
	if (getName() == name) {
		list.pushBack(getAttribute(attrib));
	}
	for (size_t i = 0; i < childrenCount(); ++i) {
		childAt(i)->operatorAt(name, attrib, list);
	}
}

void XMLElement::comparisonOperator(const MyString& childName, const MyString& childValue, const MyString& childToSelect, Vector<XMLElement*> list)
{
	bool found = false;
	for (size_t i = 0; i < childrenCount(); ++i) {
		if (childAt(i)->getName() == childName && childAt(i)->getText() == childValue) {
			found = true;
			break;
		}
	}
	if (found) {
		for (size_t i = 0; i < childrenCount(); ++i) {
			if (childAt(i)->getName() == childToSelect) {
				list.pushBack(childAt(i));
			}
		}
	}
	for (size_t i = 0; i < childrenCount(); ++i) {
		childAt(i)->comparisonOperator(childName, childValue, childToSelect, list);
	}
}

void XMLElement::comparisonOperator(const MyString& childName, const MyString& childValue, const MyString& childToSelect, Vector<const XMLElement*> list) const
{
	bool found = false;
	for (size_t i = 0; i < childrenCount(); ++i) {
		if (childAt(i)->getName() == childName && childAt(i)->getText() == childValue) {
			found = true;
			break;
		}
	}
	if (found) {
		for (size_t i = 0; i < childrenCount(); ++i) {
			if (childAt(i)->getName() == childToSelect) {
				list.pushBack(childAt(i));
			}
		}
	}
	for (size_t i = 0; i < childrenCount(); ++i) {
		childAt(i)->comparisonOperator(childName, childValue, childToSelect, list);
	}
}

Vector<XMLElement*> XMLElement::pathOperator(const MyString& parentTag, const MyString& childTag)
{
	Vector<XMLElement*> res;
	pathOperator(parentTag, childTag, res);
	return res;
}

Vector<const XMLElement*> XMLElement::pathOperator(const MyString& parentTag, const MyString& childTag) const
{
	Vector<const XMLElement*> res;
	pathOperator(parentTag, childTag, res);
	return res;
}

Vector<MyString> XMLElement::operatorAt(const MyString& name, const MyString& attrib) const
{
	Vector<MyString> res;
	operatorAt(name, attrib, res);
	return res;
}

Vector<XMLElement*> XMLElement::comparisonOperator(const MyString& childName, const MyString& childValue, const MyString& childToSelect)
{
	Vector<XMLElement*> res;
	comparisonOperator(childName, childValue, childToSelect, res);
	return res;
}

Vector<const XMLElement*> XMLElement::comparisonOperator(const MyString& childName, const MyString& childValue, const MyString& childToSelect) const
{
	Vector<const XMLElement*> res;
	comparisonOperator(childName, childValue, childToSelect, res);
	return res;
}

Vector<XMLElement*> XMLElement::executeXPath(const MyString& query)
{
	Vector<XMLElement*> res;

}

Vector<const XMLElement*> XMLElement::executeXPath(const MyString query) const
{
	return Vector<const XMLElement*>();
}


void XMLElement::setTag(const MyString& name)
{
	this->name = name;
}

void XMLElement::setTag(MyString&& name)
{
	this->name = std::move(name);
}

const MyString& XMLElement::getName() const
{
	return name;
}

void XMLElement::setParent(const ElemPtr& parent)
{
	this->parent = parent;
}

void XMLElement::setParent(ElemPtr&& parent)
{
	this->parent = std::move(parent);
}

void XMLElement::setId(const MyString& id)
{
	this->id = id;
}

void XMLElement::setId(MyString&& id)
{
	this->id = std::move(id);
}

XMLElement* XMLElement::clone() const
{
	return new XMLElement(*this);
}

void XMLElement::setText(const MyString& text)
{
	this->text = text;
}

void XMLElement::setText(MyString&& text)
{
	this->text = std::move(text);
}

const MyString& XMLElement::getText() const
{
	return text;
}

const MyString& XMLElement::getId() const
{
	return id;
}

bool XMLElement::hasAttribute(const MyString& name) const
{
	return attributes.exists(name) || name == "id";
}

const MyString& XMLElement::getAttribute(const MyString& name) const
{
	if (name == "id") {
		return id;
	}
	return attributes[name];
}

void XMLElement::addAttribute(const MyString& name, const MyString& value)
{
	if (name == "id") {
		id = value;
	}
	else {
		attributes[name] = value;
	}
}

void XMLElement::setAttribute(const MyString& name, const MyString& value)
{
	if (name == "id") {
		id = value;
	}
	else {
		attributes[name] = value;
	}
}

void XMLElement::removeAttribute(const MyString& key)
{
	if (key == "id") {
		throw std::invalid_argument("You are trying to remove the id");
	}
	attributes.removeAt(key);
}

XMLElement* XMLElement::getParent()
{
	return parent.get();
}

const XMLElement* XMLElement::getParent() const
{
	return parent.get();
}

size_t XMLElement::childrenCount() const
{
	return children.getSize();
}

XMLElement* XMLElement::childAt(size_t at)
{
	return children[at].get();
}

const XMLElement* XMLElement::childAt(size_t at) const
{
	return children[at].get();
}

int XMLElement::findChild(const MyString& childId) const
{
	for (int i = 0; i < children.getSize(); ++i) {
		if (children[i]->getId() == childId) {
			return i;
		}
	}
	return -1;
}

void XMLElement::addChild(ElemPtr&& elem)
{
	children.pushBack(std::move(elem));
}

void XMLElement::addChild(const ElemPtr& elem)
{
	children.pushBack(elem);
}

void XMLElement::insertChild(size_t at, ElemPtr&& elem)
{
	children.insert(std::move(elem), at);
}

void XMLElement::insertChild(size_t at, const ElemPtr& elem)
{
	children.insert(elem, at);
}