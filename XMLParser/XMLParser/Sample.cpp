#include <iostream>
#include <string>
#include <map>
#include <vector>

// Structure to hold an XML attribute
struct XMLAttribute {
    std::string name;
    std::string value;
};

// Structure to hold an XML element
struct XMLElement {
    std::string name;
    std::map<std::string, std::string> attributes;
    std::vector<XMLElement> children;
    std::string text;
};

// Function to trim whitespace from a string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// Function to parse attributes from a string
std::map<std::string, std::string> parseAttributes(const std::string& str) {
    std::map<std::string, std::string> attributes;
    size_t pos = 0;
    while (pos < str.length()) {
        size_t eqPos = str.find('=', pos);
        if (eqPos == std::string::npos) break;

        std::string name = str.substr(pos, eqPos - pos);
        size_t quotePos = str.find('"', eqPos + 1);
        size_t endQuotePos = str.find('"', quotePos + 1);

        std::string value = str.substr(quotePos + 1, endQuotePos - quotePos - 1);
        attributes[trim(name)] = value;

        pos = endQuotePos + 1;
    }
    return attributes;
}

// Function to parse an XML element
XMLElement parseElement(const std::string& str, size_t& pos) {
    XMLElement element;

    size_t openTagStart = str.find('<', pos);
    size_t openTagEnd = str.find('>', openTagStart);
    std::string tagContent = str.substr(openTagStart + 1, openTagEnd - openTagStart - 1);

    size_t spacePos = tagContent.find(' ');
    if (spacePos != std::string::npos) {
        element.name = tagContent.substr(0, spacePos);
        std::string attributesStr = tagContent.substr(spacePos + 1);
        element.attributes = parseAttributes(attributesStr);
    }
    else {
        element.name = tagContent;
    }

    size_t closeTagStart = str.find('<', openTagEnd + 1);
    if (str[closeTagStart + 1] == '/') {
        size_t closeTagEnd = str.find('>', closeTagStart);
        element.text = trim(str.substr(openTagEnd + 1, closeTagStart - openTagEnd - 1));
        pos = closeTagEnd + 1;
    }
    else {
        pos = openTagEnd + 1;
        while (str[pos] != '<' || str[pos + 1] != '/') {
            element.children.push_back(parseElement(str, pos));
        }
        size_t closeTagEnd = str.find('>', pos);
        pos = closeTagEnd + 1;
    }

    return element;
}

// Function to parse an XML string
XMLElement parseXML(const std::string& str) {
    size_t pos = 0;
    return parseElement(str, pos);
}

// Function to print an XML element (for testing purposes)
void printElement(const XMLElement& element, int indent = 0) {
    std::string indentation(indent, ' ');
    std::cout << indentation << "<" << element.name;

    for (const auto& attribute : element.attributes) {
        std::cout << " " << attribute.first << "=\"" << attribute.second << "\"";
    }

    if (element.children.empty() && element.text.empty()) {
        std::cout << " />\n";
    }
    else {
        std::cout << ">\n";
        if (!element.text.empty()) {
            std::cout << indentation << "  " << element.text << "\n";
        }
        for (const auto& child : element.children) {
            printElement(child, indent + 2);
        }
        std::cout << indentation << "</" << element.name << ">\n";
    }
}

int main() {
    std::string xmlData = R"(
        <note>
            <to>Tove</to>
            <from>Jani</from>
            <heading>Reminder</heading>
            <body>Don't forget me this weekend!</body>
        </note>
    )";

    XMLElement root = parseXML(xmlData);
    printElement(root);

    return 0;
}
