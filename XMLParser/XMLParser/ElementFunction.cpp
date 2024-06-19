#include "ElementFunction.h"

FunWrapper::FunWrapper(void(*funPtr)(const XMLElement* elem)) :
	funPtr(funPtr)
{}

void FunWrapper::operator()(const XMLElement * elem)
{
	return funPtr(elem);
}

ElementFunction* FunWrapper::clone() const
{
	return new FunWrapper(*this);
}

Vector<MyString>& XPathQuery::result()
{
	return _result;
}

const Vector<MyString>& XPathQuery::result() const
{
	return _result;
}

PathQuery::PathQuery(const MyString& parentName, const MyString& childName) :
	parentName(parentName), childName(childName)
{
}

PathQuery::PathQuery(MyString&& parentName, const MyString& childName) :
	parentName(std::move(parentName)), childName(childName)
{
}

PathQuery::PathQuery(const MyString& parentName, MyString&& childName) :
	parentName(parentName), childName(std::move(childName))
{
}

PathQuery::PathQuery(MyString&& parentName, MyString&& childName) :
	parentName(std::move(parentName)), childName(std::move(childName))
{
}

void PathQuery::operator()(const XMLElement* elem)
{
	if (elem->getName() == parentName) {
		for (size_t i = 0; i < elem->childrenCount(); ++i) {
			if (elem->childAt(i)->getName() == childName) {
				_result.pushBack(elem->childAt(i)->getText());
			}
		}
	}
}

ElementFunction* PathQuery::clone() const
{
	return new PathQuery(*this);
}

AttribQuery::AttribQuery(const MyString& elemName, const MyString& attribName) :
	elemName(elemName), attribName(attribName)
{}

void AttribQuery::operator()(const XMLElement * elem)
{
	if (elem->getName() == elemName && elem->hasAttribute(attribName)) {
		_result.pushBack(elem->getAttribute(attribName));
	}
}

ElementFunction* AttribQuery::clone() const
{
	return new AttribQuery(*this);
}

ComparisonQuery::ComparisonQuery(const MyString& elemName, const MyString& childName, const MyString& childValue, const MyString& childToSelect) :
	elemName(elemName), childName(childName), childValue(childValue), childToSelect(childToSelect)
{
}

void ComparisonQuery::operator()(const XMLElement* elem)
{
	bool found = false;
	if (elem->getName() == elemName) {
		for (size_t i = 0; i < elem->childrenCount(); ++i) {
			if (elem->childAt(i)->getName() == childName && elem->childAt(i)->getText() == childValue) {
				found = true;
				break;
			}
		}
		if (found) {
			for (size_t i = 0; i < elem->childrenCount(); ++i) {
				if (elem->childAt(i)->getName() == childToSelect) {
					_result.pushBack(elem->childAt(i)->getText());
				}
			}
		}
	}
	
}

ElementFunction* ComparisonQuery::clone() const
{
	return new ComparisonQuery(*this);
}

void ElementFunction::traverseElementTree(const XMLElement* elem, ElementFunction& traversalFunction)
{
	traversalFunction(elem);
	for (size_t i = 0; i < elem->childrenCount(); ++i) {
		traverseElementTree(elem->childAt(i), traversalFunction);
	}
}
