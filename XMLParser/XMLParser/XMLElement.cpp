#include "XMLElement.h"

void XMLElement::setTag(const MyString& tag)
{
	this->tag = tag;
}

void XMLElement::setTag(MyString&& tag)
{
	this->tag = std::move(tag);
}

const MyString& XMLElement::getTag() const
{
	return tag;
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
	return attributes.exists(name);
}

const MyString& XMLElement::getAttribute(const MyString& name) const
{
	return attributes[name];
}

void XMLElement::addAttribute(const MyString& name, const MyString& value)
{
	attributes[name] = value;
}

void XMLElement::setAttribute(const MyString& name, const MyString& value)
{
	attributes[name] = value;
}

void XMLElement::removeAttribute(const MyString& key)
{
	attributes.removeAt(key);
}

XMLElement::ElemPtr& XMLElement::getParent()
{
	return parent;
}

const XMLElement::ElemPtr& XMLElement::getParent() const
{
	return parent;
}

size_t XMLElement::childrenCount() const
{
	return children.getSize();
}

XMLElement::ElemPtr& XMLElement::childAt(size_t at)
{
	return children[at];
}

const XMLElement::ElemPtr& XMLElement::childAt(size_t at) const
{
	return children[at];
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