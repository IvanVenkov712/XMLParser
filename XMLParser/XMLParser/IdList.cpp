#include "IdList.h"

MyString IdList::getId(const MyString& docId)
{
    if (idMap.exists(docId)) {
        idMap[docId]++;
        return docId + "_" + idMap[docId];
    }
    idMap[docId] = 0;
    return docId;
}

MyString IdList::getId()
{
    return getId("Unnamed");
}
