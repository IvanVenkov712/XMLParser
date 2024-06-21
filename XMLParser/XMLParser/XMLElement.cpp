#include "XMLElement.h"

//Vector<MyString> XMLElement::executeXPath(const MyString& query)
//{
//	Vector<MyString> res;
//	StringView view(query);
//	int to = view.findFirstOf("/[");
//	MyString elemName = view.substr(0, to).toString();
//	if (view[to] == '/') {
//		int childBegin = to + 1;
//		int childEnd = view.findFirst(childBegin, '[');
//		if (childEnd < 0) {
//			childEnd = view.length();
//			MyString childName = view.substr(childBegin, childEnd - childBegin).toString();
//		}
//	}
//	return res;
//
//}
//
//Vector<const XMLElement*> XMLElement::executeXPath(const MyString query) const
//{
//	return Vector<const XMLElement*>();
//}


void XMLElement::setName(const MyString& name)
{
	this->name = name;
}

void XMLElement::setName(MyString&& name)
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

void XMLElement::setAttributes(const OrderedMap<MyString, MyString>& attributes)
{
	this->attributes = attributes;
}

void XMLElement::setAttributes(OrderedMap<MyString, MyString>&& attributes)
{
	this->attributes = std::move(attributes);
}

OrderedMap<MyString, MyString>& XMLElement::getAttributes()
{
	return attributes;
}

const OrderedMap<MyString, MyString>& XMLElement::getAttributes() const
{
	return attributes;
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

XMLElement* XMLElement::findInTree(const Predicate<XMLElement>& pr)
{
	if (pr(*this)) {
		return this;
	}
	for (size_t i = 0; i < childrenCount(); ++i) {
		XMLElement* res = childAt(i)->findInTree(pr);
		if (res) {
			return res;
		}
	}
	return nullptr;
}

const XMLElement* XMLElement::findInTree(const Predicate<XMLElement>& pr) const
{
	if (pr(*this)) {
		return this;
	}
	for (size_t i = 0; i < childrenCount(); ++i) {
		const XMLElement* res = childAt(i)->findInTree(pr);
		if (res) {
			return res;
		}
	}
	return nullptr;
}

XMLElement* XMLElement::findInTreeById(const MyString& id)
{
	return findInTree(IdPredicate(id));
}

const XMLElement* XMLElement::findInTreeById(const MyString& id) const
{
	return findInTree(IdPredicate(id));
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

void XMLElement::save(std::ostream& os, unsigned int indentCount) const
{
	MyString indent;
	for (unsigned i = 0; i < indentCount; ++i) {
		indent += " ";
	}
	os << indent << "<" << name;
	if (attributes.getCount() > 0) {
		for (size_t i = 0; i < attributes.getCount(); ++i) {
			const OrderedMap<MyString, MyString>::Pair& p = attributes.getPair(i);
			os << " " << p.key << "=" << "\"" << p.value << "\"";
		}
	}
	os << ">" << std::endl;

	os << indent << text << std::endl;
	for (size_t i = 0; i < children.getSize(); ++i) {
		childAt(i)->save(os, indentCount + 4);
	}
	os << indent << "</" << name << ">" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const XMLElement& elem)
{
	elem.save(os, 0);
	return os;
}

XMLElement::IdPredicate::IdPredicate(const MyString& id) : id(id)
{}

XMLElement::IdPredicate::IdPredicate(MyString&& id) : id(std::move(id))
{}

bool XMLElement::IdPredicate::operator()(const XMLElement& elem) const
{
	return id == elem.getId();
}
