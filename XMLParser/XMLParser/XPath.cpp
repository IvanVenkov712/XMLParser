#include "XPath.h"

Vector<XMLElement::ElemPtr> pathOperator(XMLElement::ElemPtr& rootPtr, const MyString& tag)
{
	Vector<XMLElement::ElemPtr> res;
	pathOperator(rootPtr, tag, res);
	return res;
}

void pathOperator(XMLElement::ElemPtr& rootPtr, const MyString& tag, Vector<XMLElement::ElemPtr>& list)
{
	for (size_t i = 0; i < rootPtr->childrenCount(); ++i) {
		if (rootPtr->childAt(i)->getTag() == tag) {
			//list.pushBack(rootPtr->childAt(i).get());
		}
		pathOperator(rootPtr->childAt(i), tag, list);
	}
}
