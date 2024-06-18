#pragma once
#include "XMLElement.h"

Vector<XMLElement::ElemPtr> pathOperator(XMLElement::ElemPtr& rootPtr, const MyString& tag);

void pathOperator(XMLElement::ElemPtr& rootPtr, const MyString& tag, Vector<XMLElement::ElemPtr>& list);