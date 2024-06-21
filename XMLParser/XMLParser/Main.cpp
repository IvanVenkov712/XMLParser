#include <iostream>
#include "XMLElementFactory.h"
#include "XPathFactory.h"
#include <string>

MyString currFile = "";
XMLElement* currElem = nullptr;

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
	while (command != "exit") {
		command = readCommand();
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
		else {
			throw std::exception("Unrecognised command");
		}
	}
	executeCloseCommand();
	delete currElem;
}

void executeOpenCommand()
{
	if (currElem) {
		std::cout << "Do you want to save your work?: ";
		MyString resp;
		std::cin >> resp;
		if(resp == "yes") {
			executeSaveCommand();
		}
		else if (resp != "no") {
			throw std::exception("Invalid input");
		}
	}
	executeOpenCommandHard();
}

void executeOpenCommandHard()
{
	delete currElem;
	std::cout << "Enter file path: ";
	MyString path;
	myGetLine(std::cin, path);
	currElem = XMLElementFactory::create(path.c_str());
	if (!currElem) {
		throw std::exception("Element could not be created!");
	}
	currFile = path;
}

void executePrintCommand()
{
	if (!currElem) {
		throw std::exception("There is no open xml file!");
	}
	std::cout << *currElem << std::endl;
}

void executeCloseCommand()
{
	if (currElem) {
		std::cout << "Do you want to save your work?: ";
		MyString resp;
		std::cin >> resp;
		if (resp == "yes") {
			executeSaveCommand();
		}
		else if (resp != "no") {
			throw std::exception("Invalid input");
		}
		currElem = nullptr;
		currFile = "";
	}
}

void executeSaveCommand()
{
	if (!currElem) {
		throw std::exception("There is no open file");
	}
	std::ofstream ofs(currFile.c_str());
	if (!ofs.is_open()) {
		throw std::exception("Could not save into current");
	}
	ofs << *currElem;
	ofs.close();
}

void executeSaveAsCommand()
{
	if (!currElem) {
		throw std::exception("There is no open file");
	}
	std::cout << "Enter destination path: ";
	MyString dest;
	myGetLine(std::cin, dest);
	std::ofstream ofs(dest.c_str());
	if (!ofs.is_open()) {
		throw std::exception("Could not open destination for writing");
	}
	ofs << *currElem;
	ofs.close();
	currFile = dest;
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
	std::cout << "Enter element id: ";
	MyString id;
	myGetLine(std::cin, id);
	XMLElement* elem = currElem->findInTreeById(id);
	if (!elem) {
		throw std::exception("there is no element with this id");
	}
	std::cout << "Enter attribute name: ";
	MyString attribName;
	myGetLine(std::cin, attribName);
	std::cout << "Enter attribute new value: ";
	MyString value;
	myGetLine(std::cin, value);
	elem->setAttribute(attribName, value);
}

void executeSelectCommand()
{
	std::cout << "Enter element id: ";
	MyString id;
	myGetLine(std::cin, id);
	const XMLElement* elem = currElem->findInTreeById(id);
	if (!elem) {
		throw std::exception("there is no element with this id");
	}
	std::cout << "Enter attribute name: ";
	MyString attribName;
	myGetLine(std::cin, attribName);
	std::cout << elem->getAttribute(attribName) << std::endl;
}
