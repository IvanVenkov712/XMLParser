#pragma once
#include <sstream>
#include "MyString.h"
#include "OrderedMap.h"
#include "Helpers.h"

/**
 * Process-wide counters for ID bases; opening a new file does not reset them.
 * Suffixes are not reserved as bases, so pre-suffixed input can still collide.
 */
class IdList {
private:
	static OrderedMap<MyString, size_t> idMap;
public:
	/// Return docId on first use, then docId_1, docId_2, etc. (subject to toString).
	static MyString getId(const MyString& docId);

	/// Allocate from the "Unnamed" base for elements lacking an explicit ID.
	static MyString getId();
};
