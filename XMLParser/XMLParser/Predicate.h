#pragma once

/// Read-only boolean test used to select the first matching node in tree searches.
template<typename T>
class Predicate {
public:
	virtual bool operator()(const T& t) const = 0;

	virtual ~Predicate() = default;
};
