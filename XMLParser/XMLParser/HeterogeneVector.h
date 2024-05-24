#pragma once

#include <iostream>
#include <iostream>

template<typename T>
class HeterogeneVector {
protected:
	static constexpr size_t min_cap = 16;
	static constexpr size_t growth = 2;
	size_t capacity = min_cap;
	size_t count = 0;
	T** data = nullptr;

	void free();

	void copyFrom(const HeterogeneVector<T>& other);

	void moveFrom(HeterogeneVector<T>&& other);

	void resize(size_t newCap);

	HeterogeneVector(size_t startCapacity);

	void push_back(T* elemPtr);

	void insert(size_t at, T* elemPtr);

public:
	HeterogeneVector();

	HeterogeneVector(const HeterogeneVector<T>& other);

	HeterogeneVector(HeterogeneVector<T>&& other);

	HeterogeneVector<T>& operator=(const HeterogeneVector<T>& other);

	HeterogeneVector<T>& operator=(HeterogeneVector<T>&& other);

	~HeterogeneVector();

	void push_back(const T& elem);

	void push_back(T&& elem);

	void insert(size_t at, const T& elem);

	void insert(size_t at, T&& elem);

	void remove(size_t at);

	const T& operator[](size_t at) const;

	T& operator[](size_t at);
};

template<typename T>
void HeterogeneVector<T>::free() {
	for (size_t i = 0; i < count; ++i) {
		delete data[i];
	}
	delete[] data;
	data = nullptr;
}

template<typename T>
void HeterogeneVector<T>::copyFrom(const HeterogeneVector<T>& other) {
	capacity = other.capacity;
	count = other.count;
	data = new T * [capacity];
	for (size_t i = 0; i < count; ++i) {
		data[i] = other.data[i]->clone();
	}
}

template<typename T>
void HeterogeneVector<T>::moveFrom(HeterogeneVector<T>&& other) {
	capacity = other.capacity;
	count = other.count;
	data = other.data;
	other.data = nullptr;
	other.count = 0;
	other.capacity = 0;
}

template<typename T>
void HeterogeneVector<T>::resize(size_t newCap) {
	if (newCap == capacity) {
		return;
	}
	T** tmp = new T * [newCap];
	for (size_t i = 0; i < count; ++i) {
		tmp[i] = data[i];
	}
	delete[] data;
	data = tmp;
	capacity = newCap;
}

template<typename T>
HeterogeneVector<T>::HeterogeneVector(size_t startCapacity) {
	capacity = std::max(startCapacity, min_cap);
	data = new T * [capacity] {nullptr};
	count = 0;
}


template<typename T>
void HeterogeneVector<T>::push_back(T* elemPtr) {
	if (count >= capacity) {
		resize(capacity * growth);
	}
	data[count++] = elemPtr;
}

template<typename T>
void HeterogeneVector<T>::insert(size_t at, T* elemPtr) {
	if (at > count) {
		throw std::out_of_range("HeterogeneVector::Insert index bigger than count");
	}
	if (count >= capacity) {
		resize(capacity * 2);
	}
	for (int i = (int)count - 1; i >= (int)at; --i) {
		data[i + 1] = data[i];
	}
	data[at] = elemPtr;
	++count;
}

template<typename T>
HeterogeneVector<T>::HeterogeneVector() : HeterogeneVector(0) {}

template<typename T>
HeterogeneVector<T>::HeterogeneVector(const HeterogeneVector<T>& other) {
	copyFrom(other);
}

template<typename T>
HeterogeneVector<T>::HeterogeneVector(HeterogeneVector<T>&& other) {
	moveFrom(std::move(other));
}

template<typename T>
HeterogeneVector<T>& HeterogeneVector<T>::operator=(const HeterogeneVector<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
HeterogeneVector<T>& HeterogeneVector<T>::operator=(HeterogeneVector<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
HeterogeneVector<T>::~HeterogeneVector() {
	free();
}

template <typename T>
void HeterogeneVector<T>::push_back(const T& elem) {
	push_back(elem.clone());
}

template <typename T>
void HeterogeneVector<T>::push_back(T&& elem) {
	push_back(elem.clone());
}

template<typename T>
void HeterogeneVector<T>::insert(size_t at, const T& elem) {
	insert(at, elem.clone());
}

template<typename T>
void HeterogeneVector<T>::insert(size_t at, T&& elem) {
	insert(at, elem.clone());
}

template<typename T>
void HeterogeneVector<T>::remove(size_t at) {
	if (at >= count) {
		throw std::out_of_range("HeterogeneVector::Not a valid index");
	}
	delete data[at];
	for (size_t i = at; i < count - 1; ++i) {
		data[i] = data[i + 1];
	}
	--count;
	if (count <= capacity / (growth * growth)) {
		resize(std::max(capacity / growth, min_cap));
	}
}

template <typename T>
const T& HeterogeneVector<T>::operator[](size_t at) const {
	if (at >= count) {
		throw std::out_of_range("HeterogeneVector::Not a valid index");
	}
	return *data[at];
}

template <typename T>
T& HeterogeneVector<T>::operator[](size_t at) {
	if (at >= count) {
		throw std::out_of_range("HeterogeneVector::Not a valid index");
	}
	return *data[at];
}

