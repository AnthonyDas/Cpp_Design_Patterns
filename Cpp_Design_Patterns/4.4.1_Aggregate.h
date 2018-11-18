#ifndef MY_DATACOLLECTION_HEADER
#define MY_DATACOLLECTION_HEADER

#include "4.4.1_IteratorTemplate.h"

template <class T>
class aggregate {
	friend class Iterator<T, aggregate>;

	std::vector<T> m_data;

public:
	void add(T a) {
		m_data.push_back(a);
	}

	Iterator<T, aggregate> *create_iterator() {
		return new Iterator<T, aggregate>(this);
	}
};

template <class T, class U>
class aggregateSet {
	friend class setIterator<T, U, aggregateSet>;

	std::set<T, U> m_data;

public:
	void add(T a) {
		m_data.insert(a);
	}

	setIterator<T, U, aggregateSet> *create_iterator() {
		return new setIterator<T, U, aggregateSet>(this);
	}

	void Print() {
		copy(m_data.begin(), m_data.end(), std::ostream_iterator<T>(std::cout, "\n"));
	}
};

#endif