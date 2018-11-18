#ifndef MY_ITERATOR_HEADER
#define MY_ITERATOR_HEADER

#include <iterator>
#include <vector>
#include <set>

// The following program gives the implementation of an iterator design
// pattern with a generic template:
template<class T, class U>
class Iterator {
	using iter_type = typename std::vector<T>::iterator;

	U *m_pData;
	iter_type m_it;

public:
	Iterator(U *pData) : m_pData(pData) {
		m_it = m_pData->m_data.begin();
	}

	void first() {
		m_it = m_pData->m_data.begin();
	}

	void next() {
		++m_it;
	}

	bool isDone() {
		return (m_it == m_pData->m_data.end());
	}

	iter_type current() {
		return m_it;
	}
};

template<class T, class U, class A>
class setIterator {
	using iter_type = typename std::set<T, U>::iterator;

	A *m_pData;
	iter_type m_it;

public:

	setIterator(A *pData) : m_pData(pData) {
		m_it = m_pData->m_data.begin();
	}

	void first() {
		m_it = m_pData->m_data.begin();
	}

	void next() {
		++m_it;
	}

	bool isDone() {
		return (m_it == m_pData->m_data.end());
	}

	iter_type current() {
		return m_it;
	}
};

#endif