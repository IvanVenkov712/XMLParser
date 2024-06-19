#include "XPathFactory.h"

XPathQuery* XPathFactory::create(const MyString& queryString)
{
    try {
        StringView view(queryString);
        int to = view.findFirstOf("/[");
        MyString elemName = view.substr(0, to).toString();
        if (view[to] == '/') {
            int childBegin = to + 1;
            int childEnd = view.findFirst(childBegin, '[');
            if (childEnd < 0) {
                childEnd = view.length();
                MyString childName = view.substr(childBegin, childEnd - childBegin).toString();
                return new PathQuery(elemName, childName);
            }
        }
        else if (view[to] == '[') {
            if (view[to + 1] == '@') {
                int attribEnd = view.findFirst(']');
                MyString attribName = view.substr(to + 1, attribEnd - to - 1).toString();
                return new AttribQuery(elemName, attribName);
            }
            else {
                MyString cmpChildName = view.substr(to + 1, view.findFirst('=') - to - 1)
                    .trim().toString();
                int vStart = view.findFirst('"') + 1;
                MyString cmpChildValue = view.substr(vStart, view.findLast('"') - vStart)
                    .trim().toString();

                int sStart = view.findFirst('/');
                int sLen = view.length() - sStart;
                MyString selectChildName = view.substr(sStart, sLen).trim().toString();
                return new ComparisonQuery(elemName, cmpChildName, cmpChildValue, selectChildName);
            }
        }
    }
    catch (...) {
        return nullptr;
    }
}
