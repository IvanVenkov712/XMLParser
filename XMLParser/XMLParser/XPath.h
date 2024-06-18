#pragma once
#include "XMLElement.h"

Vector<XMLElement*> pathOperator(XMLElement* rootPtr, const MyString& parentTag, const MyString& childTag);

void pathOperator(XMLElement* rootPtr, const MyString& parentTag, const MyString& childTag, Vector<XMLElement*>& list);

Vector<const XMLElement*> pathOperator(const XMLElement* rootPtr, const MyString& parentTag, const MyString& childTag);

void pathOperator(const XMLElement* rootPtr, const MyString& parentTag, const MyString& childTag, Vector<const XMLElement*>& list);

Vector<MyString> operatorAt(const XMLElement* root, const MyString& tag, const MyString& attrib);

void operatorAt(const XMLElement* root, const MyString& tag, const MyString& attrib, Vector<MyString>& list);
