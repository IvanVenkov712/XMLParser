#include "IdList.h"

OrderedMap<MyString, size_t> IdList::idMap{};

MyString IdList::getId(const MyString& docId)
{
    if (idMap.exists(docId)) {
        idMap[docId]++;
        return docId + "_" + toString(idMap[docId]);
    }
    idMap[docId] = 0;
    return docId;
}

MyString IdList::getId()
{
    return getId("Unnamed");
}
