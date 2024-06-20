#pragma once

template<typename T>
class Predicate {
public:
	virtual bool operator()(const T& t) const = 0;

	virtual bool operator()(const T& t) = 0;

	virtual ~Predicate() = default;
};