#include <iostream>
#include "XMLElementFactory.h"
#include "XPathFactory.h"
#include <string>

MyString currFile = "";
XMLElement* rootElem = nullptr;
bool hasUnsaved = false;

MyString readCommand();

void runMainLoop();

void executeOpenCommand();

void executeOpenCommandHard();

void executePrintCommand();

void executeCloseCommand();

void executeSaveCommand();

void executeSaveAsCommand();

void executeHelpCommand();

void executeSetCommand();

void executeSelectCommand();

void executeChildrenCommand();

void executeChildCommand();

void executeTextCommand();

void executeDeleteCommand();

void executeNewchildCommand();

void executeXpathCommand();

XMLElement* getElementById();

int main() {
	try {
		runMainLoop();
	}
	catch (const std::exception& e) {
		std::cout << "An error occurred: " << e.what() << std::endl;
	}
	return 0;
}

MyString readCommand()
{
	std::cout << "Enter command: ";
	MyString command;
	myGetLine(std::cin, command);
	return command;
}

void runMainLoop()
{
	MyString command;
	while (true) {
		command = readCommand();
		if (command == "exit") {
			break;
		}
		if (command == "open") {
			executeOpenCommand();
		}
		else if (command == "print") {
			executePrintCommand();
		}
		else if (command == "save") {
			executeSaveCommand();
		}
		else if (command == "save as") {
			executeSaveAsCommand();
		}
		else if (command == "close") {
			executeCloseCommand();
		}
		else if (command == "help") {
			executeHelpCommand();
		}
		else if (command == "select") {
			executeSelectCommand();
		}
		else if (command == "set") {
			executeSetCommand();
		}
		else if (command == "children") {
			executeChildrenCommand();
		}
		else if (command == "child") {
			executeChildCommand();
		}
		else if (command == "text") {
			executeTextCommand();
		}
		else if (command == "delete") {
			executeDeleteCommand();
		}
		else if (command == "newchild") {
			executeNewchildCommand();
		}
		else if (command == "xpath") {
			executeXpathCommand();
		}
		else {
			throw std::exception("Unrecognised command");
		}
	}
	executeCloseCommand();
	delete rootElem;
}

void executeOpenCommand()
{
	if (rootElem) {
		executeCloseCommand();
	}
	executeOpenCommandHard();
}

void executeOpenCommandHard()
{
	delete rootElem;
	std::cout << "Enter file path: ";
	MyString path;
	myGetLine(std::cin, path);
	rootElem = XMLElementFactory::create(path.c_str());
	if (!rootElem) {
		throw std::exception("Element could not be created!");
	}
	currFile = path;
}

void executePrintCommand()
{
	if (!rootElem) {
		throw std::exception("There is no open xml file!");
	}
	for (size_t i = 0; i < rootElem->childrenCount(); ++i) {
		std::cout << *(rootElem->childAt(i)) << std::endl;
	}
	
}

void executeCloseCommand()
{
	if (rootElem && hasUnsaved) {
		std::cout << "Do you want to save your work?: ";
		MyString resp;
		std::cin >> resp;
		if (resp == "yes") {
			executeSaveCommand();
		}
		else if (resp != "no") {
			throw std::exception("Invalid input");
		}
		delete rootElem;
		rootElem = nullptr;
		currFile = "";
	}
	hasUnsaved = false;
}

void executeSaveCommand()
{
	if (!rootElem) {
		throw std::exception("There is no open file");
	}
	std::ofstream ofs(currFile.c_str());
	if (!ofs.is_open()) {
		throw std::exception("Could not save into current");
	}
	for (size_t i = 0; i < rootElem->childrenCount(); ++i) {
		ofs << *(rootElem->childAt(i)) << std::endl;
	}
	ofs.close();
	hasUnsaved = false;
}

void executeSaveAsCommand()
{
	if (!rootElem) {
		throw std::exception("There is no open file");
	}
	std::cout << "Enter destination path: ";
	MyString dest;
	myGetLine(std::cin, dest);
	std::ofstream ofs(dest.c_str());
	if (!ofs.is_open()) {
		throw std::exception("Could not open destination for writing");
	}
	for (size_t i = 0; i < rootElem->childrenCount(); ++i) {
		ofs << *(rootElem->childAt(i)) << std::endl;
	}
	ofs.close();
	currFile = dest;
	hasUnsaved = false;
}

void executeHelpCommand()
{
	std::cout << "List of commands:" << std::endl;
	std::cout << "open: opens a new file" << std::endl;
	std::cout << "print: prints the open file content" << std::endl;
	std::cout << "save: saves the open file" << std::endl;
	std::cout << "save as: saves the open file with a new name" << std::endl;
	std::cout << "close: closes the open file" << std::endl;
	std::cout << "select <id> <key>: prints the value of the attribute with key <key> of the element with id <id>" << std::endl;
	std::cout << "set <id> <key> <value>: sets the value of attribute" << std::endl;
	std::cout << "children <id>: lists the attributes of the children of an element" << std::endl;
	std::cout << "child <id> <n>: prints the nth child of an element" << std::endl;
	std::cout << "text <id>: prints the text of an element" << std::endl;
	std::cout << "delete <id> <key>: deletes an attribute of an element" << std::endl;
	std::cout << "newchild <id>: creates a new child of an element" << std::endl;
	std::cout << "xpath <XPath>: executes xpath queries" << std::endl;
}

void executeSetCommand()
{
	XMLElement* elem = getElementById();
	std::cout << "Enter attribute name: ";
	MyString attribName;
	myGetLine(std::cin, attribName);
	std::cout << "Enter attribute new value: ";
	MyString value;
	myGetLine(std::cin, value);
	elem->setAttribute(attribName, value);
	hasUnsaved = true;
}

void executeSelectCommand()
{
	XMLElement* elem = getElementById();
	std::cout << "Enter attribute name: ";
	MyString attribName;
	myGetLine(std::cin, attribName);
	std::cout << elem->getAttribute(attribName) << std::endl;
}

void executeChildrenCommand()
{
	XMLElement* elem = getElementById();
	std::cout << "Element children: " << std::endl;
	for (size_t i = 0; i < elem->childrenCount(); ++i) {
		std::cout << elem->childAt(i)->getName() << ":" << std::endl;
		const OrderedMap<MyString, MyString>& attribs = elem->childAt(i)->getAttributes();
		for (size_t j = 0; j < attribs.getCount(); ++j) {
			std::cout << "    " << attribs.getPair(j).key << "=" << attribs.getPair(j).value << std::endl;
		}
	}
}

void executeChildCommand()
{
	XMLElement* elem = getElementById();
	size_t n;
	std::cout << "Enter child position: ";
	std::cin >> n;
	std::cout << *(elem->childAt(n)) << std::endl;
}

void executeTextCommand()
{
	XMLElement* elem = getElementById();
	std::cout << elem->getText() << std::endl;
}

void executeDeleteCommand()
{
	XMLElement* elem = getElementById();
	std::cout << "Enter attribute key: ";
	MyString key;
	myGetLine(std::cin, key);
	elem->removeAttribute(key);
	hasUnsaved = true;
}

void executeNewchildCommand()
{
	XMLElement* elem = getElementById();
	MyString childId;
	std::cout << "Enter child id: ";
	myGetLine(std::cin, childId);
	XMLElement* child = new XMLElement();
	child->setId(IdList::getId(childId));
	elem->addChild(child);
	hasUnsaved = true;
}

void executeXpathCommand()
{
	std::cout << "Enter xpath query: ";
	MyString xpath;
	myGetLine(std::cin, xpath);
	XPathQuery* query = XPathFactory::create(xpath);
	ElementFunction::traverseElementTree(rootElem, *query);
	std::cout << query->result().getSize() << " extracted: " << std::endl;
	std::cout << "[";
	const Vector<MyString>& res = query->result();
	if (res.getSize() > 0) {
		for (size_t i = 0; i < res.getSize() - 1; ++i) {
			std::cout << "\"" << res[i] << "\"" << ", ";
		}
		std::cout << "\"" << res[res.getSize() - 1] << "\"";
	}
	std::cout << "]" << std::endl;
	delete query;
}

XMLElement* getElementById()
{
	if (!rootElem) {
		throw std::exception("There is no open file!");
	}
	MyString id;
	std::cout << "Enter element id: ";
	myGetLine(std::cin, id);
	XMLElement* elem = rootElem->findInTreeById(id);
	if (!elem) {
		throw std::exception("There is no element with this id!");
	}
	return elem;
}