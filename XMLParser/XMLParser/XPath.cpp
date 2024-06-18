#include "XPath.h"

Vector<XMLElement*> pathOperator(XMLElement* rootPtr, const MyString& parentTag, const MyString& childTag)
{
	Vector<XMLElement*> res;
	pathOperator(rootPtr, parentTag, childTag, res);
	return res;
}

void pathOperator(XMLElement* rootPtr, const MyString& parentTag, const MyString& childTag, Vector<XMLElement*>& list)
{
	if (rootPtr->getTag() == parentTag) {
		for (size_t i = 0; i < rootPtr->childrenCount(); ++i) {
			if (rootPtr->childAt(i)->getTag() == childTag) {
				list.pushBack(rootPtr->childAt(i).get());
			}
		}
	}
	for (size_t i = 0; i < rootPtr->childrenCount(); ++i) {
		pathOperator(rootPtr->childAt(i).get(), parentTag, childTag, list);
	}
}


Vector<const XMLElement*> pathOperator(const XMLElement* rootPtr, const MyString& parentTag, const MyString& childTag)
{
	Vector<const XMLElement*> res;
	pathOperator(rootPtr, parentTag, childTag, res);
	return res;
}

void pathOperator(const XMLElement* rootPtr, const MyString& parentTag, const MyString& childTag, Vector<const XMLElement*>& list)
{
	if (rootPtr->getTag() == parentTag) {
		for (size_t i = 0; i < rootPtr->childrenCount(); ++i) {
			if (rootPtr->childAt(i)->getTag() == childTag) {
				list.pushBack(rootPtr->childAt(i).get());
			}
		}
	}
	for (size_t i = 0; i < rootPtr->childrenCount(); ++i) {
		pathOperator(rootPtr->childAt(i).get(), parentTag, childTag, list);
	}
}

Vector<MyString> operatorAt(const XMLElement* root, const MyString& tag, const MyString& attrib)
{
	Vector<MyString> res;
	operatorAt(root, tag, attrib, res);
	return res;

}

void operatorAt(const XMLElement* root, const MyString& tag, const MyString& attrib, Vector<MyString>& list)
{
	if (root->getTag() == tag) {
		list.pushBack(root->getAttribute(attrib));
	}
	for (size_t i = 0; i < root->childrenCount(); ++i) {
		operatorAt(root->childAt(i).get(), tag, attrib);
	}
}
