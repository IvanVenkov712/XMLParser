#pragma once
#include <iostream>

template<typename KeyT, typename ValueT>
class OrderedMap {
public:
	struct Pair {
		KeyT key;
		ValueT value;
	};

private:
	static constexpr size_t min_cap = 16;
	static constexpr size_t growth = 2;

	Pair* data = nullptr;
	size_t capacity = min_cap;
	size_t count = 0;

	void free();

	void copyFrom(const OrderedMap& other);

	void moveFrom(OrderedMap&& other);

	void resize(size_t newCap);

	int find(const KeyT& key) const;

	int getIndexToInsertAt(const KeyT& key) const;

	void insert(int at, const KeyT& key);

	void insert(int at, KeyT&& key);

	int insertSorted(const KeyT& key);

	int insertSorted(KeyT&& key);

	OrderedMap(size_t startCapacity);

public:

	OrderedMap();

	OrderedMap(const OrderedMap& other);

	OrderedMap(OrderedMap&& other);

	OrderedMap& operator=(const OrderedMap& other);

	OrderedMap& operator=(OrderedMap&& other);

	~OrderedMap();

	bool exists(const KeyT& key) const;

	const ValueT& operator[](const KeyT& key) const;

	const ValueT& operator[](KeyT&& key) const;

	ValueT& operator[](const KeyT& key);

	ValueT& operator[](KeyT&& key);

	void removeAt(const KeyT& key);

	size_t getCapacity() const;

	size_t getCount() const;

	Pair& getPair(size_t at);

	const Pair& getPair(size_t at) const;
};

template<typename KeyT, typename ValueT>
void OrderedMap<KeyT, ValueT>::free() {
	delete[] data;
	data = nullptr;
}

template<typename KeyT, typename ValueT>
void OrderedMap<KeyT, ValueT>::copyFrom(const OrderedMap& other) {
	capacity = other.capacity;
	count = other.count;
	data = new Pair[capacity];
	for (size_t i = 0; i < count; ++i) {
		data[i] = other.data[i];
	}
}

template<typename KeyT, typename ValueT>
void OrderedMap<KeyT, ValueT>::moveFrom(OrderedMap&& other) {
	count = other.count;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
	other.count = 0;
	other.capacity = 0;
}

template<typename KeyT, typename ValueT>
void OrderedMap<KeyT, ValueT>::resize(size_t newCap) {
	Pair* tmp = new Pair[newCap];
	for (size_t i = 0; i < count; ++i) {
		tmp[i] = std::move(data[i]);
	}
	capacity = newCap;
	delete[] data;
	data = tmp;
}

template<typename KeyT, typename ValueT>
int OrderedMap<KeyT, ValueT>::find(const KeyT& key) const {
	int left = 0;
	int right = (int)count - 1;
	while (left <= right) {
		int middle = (right - left) / 2 + left;
		if (data[middle].key == key) {
			return middle;
		}
		else if (key > data[middle].key) {
			left = middle + 1;
		}
		else {
			right = middle - 1;
		}
	}
	return -1;
}

template<typename KeyT, typename ValueT>
int OrderedMap<KeyT, ValueT>::getIndexToInsertAt(const KeyT& key) const {
	for (int i = 0; i < count; ++i) {
		if (key < data[i].key) {
			return i;
		}
	}
	return count;
}

template<typename KeyT, typename ValueT>
void OrderedMap<KeyT, ValueT>::insert(int at, const KeyT& key) {
	if (count >= capacity) {
		resize(capacity * growth);
	}
	for (int i = (int)count - 1; i >= at; --i) {
		data[i + 1] = std::move(data[i]);
	}
	data[at] = { key, ValueT() };
	++count;
}

template<typename KeyT, typename ValueT>
void OrderedMap<KeyT, ValueT>::insert(int at, KeyT&& key) {
	if (count >= capacity) {
		resize(capacity * growth);
	}
	for (int i = (int)count - 1; i >= at; --i) {
		data[i + 1] = std::move(data[i]);
	}
	data[at] = { std::move(key), ValueT() };
	++count;
}

template<typename KeyT, typename ValueT>
int OrderedMap<KeyT, ValueT>::insertSorted(const KeyT& key) {
	int at = getIndexToInsertAt(key);
	insert(at, std::move(key));
	return at;
}

template<typename KeyT, typename ValueT>
int OrderedMap<KeyT, ValueT>::insertSorted(KeyT&& key) {
	int at = getIndexToInsertAt(key);
	insert(at, std::move(key));
	return at;
}

template<typename KeyT, typename ValueT>
OrderedMap<KeyT, ValueT>::OrderedMap(size_t startCapacity) {
	capacity = std::max(startCapacity, min_cap);
	data = new Pair[capacity];
}

template<typename KeyT, typename ValueT>
OrderedMap<KeyT, ValueT>::OrderedMap() : OrderedMap(min_cap) {
}

template<typename KeyT, typename ValueT>
OrderedMap<KeyT, ValueT>::OrderedMap(const OrderedMap& other) {
	copyFrom(other);
}

template<typename KeyT, typename ValueT>
OrderedMap<KeyT, ValueT>::OrderedMap(OrderedMap&& other) {
	moveFrom(std::move(other));
}

template<typename KeyT, typename ValueT>
OrderedMap<KeyT, ValueT>& OrderedMap<KeyT, ValueT>::operator=(const OrderedMap& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename KeyT, typename ValueT>
OrderedMap<KeyT, ValueT>& OrderedMap<KeyT, ValueT>::operator=(OrderedMap&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename KeyT, typename ValueT>
OrderedMap<KeyT, ValueT>::~OrderedMap() {
	free();
	count = 0;
	capacity = 0;
}

template<typename KeyT, typename ValueT>
bool OrderedMap<KeyT, ValueT>::exists(const KeyT& key) const {
	return find(key >= 0);
}

template<typename KeyT, typename ValueT>
const ValueT& OrderedMap<KeyT, ValueT>::operator[](const KeyT& key) const {
	int index = find(key);
	if (index < 0) {
		throw std::invalid_argument("That key does not exist");
	}
	return data[index].value;
}


template<typename KeyT, typename ValueT>
const ValueT& OrderedMap<KeyT, ValueT>::operator[](KeyT&& key) const {
	int index = find(key);
	if (index < 0) {
		throw std::invalid_argument("That key does not exist");
	}
	return data[index].value;
}

template<typename KeyT, typename ValueT>
ValueT& OrderedMap<KeyT, ValueT>::operator[](const KeyT& key) {
	int index = find(key);
	if (index < 0) {
		index = insertSorted(key);
	}
	return data[index].value;
}

template<typename KeyT, typename ValueT>
ValueT& OrderedMap<KeyT, ValueT>::operator[](KeyT&& key) {
	int index = find(key);
	if (index < 0) {
		index = insertSorted(std::move(key));
	}
	return data[index].value;
}

template<typename KeyT, typename ValueT>
void OrderedMap<KeyT, ValueT>::removeAt(const KeyT& key) {
	int index = find(key);
	if (index < 0) {
		return;
	}
	for (int i = index; i < (int)count - 1; ++i) {
		data[i] = std::move(data[i + 1]);
	}
}

template<typename KeyT, typename ValueT>
size_t OrderedMap<KeyT, ValueT>::getCapacity() const {
	return capacity;
}

template<typename KeyT, typename ValueT>
size_t OrderedMap<KeyT, ValueT>::getCount() const {
	return count;
}

template<typename KeyT, typename ValueT>
typename OrderedMap<KeyT, ValueT>::Pair& OrderedMap<KeyT, ValueT>::getPair(size_t at) {
	if (at >= count) {
		throw std::out_of_range("At not a valid index");
	}
	return data[at];
}

template<typename KeyT, typename ValueT>
const typename OrderedMap<KeyT, ValueT>::Pair& OrderedMap<KeyT, ValueT>::getPair(size_t at) const {
	if (at >= count) {
		throw std::out_of_range("At not a valid index");
	}
	return data[at];
}