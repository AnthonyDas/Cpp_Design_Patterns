#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Iterator

Iterator

The 'iterator' design pattern is used liberally within the STL for traversal of
various containers. The full understanding of this will liberate a developer to
create highly reusable and easily understandable data containers.

The basic idea of the iterator is that it permits the traversal of a container (like
a pointer moving across an array). However, to get to the next element of a container,
you need not know anything about how the container is constructed. This is the iterators
job. By simply using the member functions provided by the iterator, you can move, in
the intended order of the container, from the first element to the last element.

Let us start by considering a traditional single dimensional array with a pointer
moving from the start to the end. This example assumes knowledge of pointer arithmetic.
Note that the use of "it" or "itr," henceforth, is a short version of "iterator". */

void iterator1() {
	constexpr int ARRAY_LEN = 42;
	int *myArray = new int[ARRAY_LEN];

	// Set the iterator to point to the first memory location of the array
	int *arrayItr = myArray;
	
	// Move through each element of the array, setting it equal to its position in the array
	for (int i = 0; i < ARRAY_LEN; ++i){
		*arrayItr = i;
		
		// By incrementing the pointer, we move it to the next position in the array.
		// This is easy for a contiguous memory container, since pointer arithmetic 
		// handles the traversal.
		++arrayItr;
	}
	
	delete[] myArray;
}

/* This code works very quickly for arrays, but how would we traverse a linked list,
where the memory is not contiguous? Consider the implementation of a rudimentary linked
list which is not a candidate for pointer arithmetic. We do not want to expose the
internals of the list to other developers, forcing them to learn them, and keeping us
from changing it.

This is where the iterator comes in. The common interface makes learning the usage
of the container easier, and hides the traversal logic from other developers. */

class MyIntLList {
	// The Node class represents a single element in the linked list. 
	// The node has a next node and a previous node, so that the user 
	// may move forward one position to the next node, or step backward
	// single position to the previous node. Notice that the traversal
	// of a linked list is O(N), as is searching, since the list is not ordered.
	class Node {
	public:
		Node *mNextNode;
		Node *mPrevNode;
		int mValue;

		Node() : mNextNode(nullptr), mPrevNode(nullptr), mValue(0) {}

		Node(Node * prv, Node * nxt, int val) : mNextNode(nxt), mPrevNode(prv), mValue(val) {}
	};

	Node *mHead;
	Node *mTail;
	size_t mSize;

public:

	MyIntLList() : mHead(nullptr), mTail(nullptr), mSize(0) {}

	~MyIntLList() {
		while (!isEmpty())
			pop_front();
	}

	size_t Size() const { return mSize; }

	// Add this value to the end of the list
	void push_back(int value) {
		Node *newNode = new Node(mTail, nullptr, value); // prv, nxt, val
		if (mHead == nullptr) {
			mHead = mTail = newNode;
		}
		else /*if (mTail != nullptr)*/ {
			mTail->mNextNode = newNode;
		}
		mTail = newNode;
		++mSize;
	}

	// Remove the value from the beginning of the list
	void pop_front() {
		if (mHead == nullptr) {
			return;
		}
		else {
			Node *temp = mHead;
			mHead = mHead->mNextNode;
			delete temp;
			--mSize;
		}
	}

	bool isEmpty() {
		return mSize == 0;
	}

	/* The iterator class knows the internals of the linked list, so that it
	may move from one element to the next. In this implementation, we have
	chosen the classic traversal method of overloading the increment
	operators. More thorough implementations of a bi-directional linked
	list would include decrement operators so that the iterator may move
	in the opposite direction. */
	class MyIterator {
		Node *mCurrNode;

	public:
		MyIterator(Node *position) : mCurrNode(position) {}

		// Prefix increment
		const MyIterator &operator++() {
			if (mCurrNode == nullptr) {
				throw std::runtime_error("IteratorCannotMoveToNext");
			}
			mCurrNode = mCurrNode->mNextNode;
			return *this;
		}

		// Postfix increment
		MyIterator operator++(int) { // Dummy int variable to indicate prefix vs postfix
			MyIterator temp = *this;
			operator++();
			return temp;
		}

		// Dereferencing operator returns the current node, which should then 
		// be dereferenced for the underlying int.
		Node* operator*() {
			return mCurrNode;
		}

		bool operator==(const MyIterator &other) {
			return mCurrNode == other.mCurrNode;
		}

		bool operator!=(const MyIterator &other) {
			return !operator==(other);
		}
	};

	// Starting position should be the first element in the container.
	MyIterator Begin() { return MyIterator(mHead); }

	// Ending position should be one past the last element in the container.
	MyIterator End() { return MyIterator(nullptr); }
};


/* With this implementation, it is now possible, without knowledge of the size
of the container or how its data is organized, to move through each element in
order, manipulating or simply accessing the data. This is done through the
accessors in the MyIntLList class, Begin() and End(). */

void iterator2() {
	MyIntLList myList;

	// Add some items to the list
	for (int i = 0; i < 10; ++i)
		myList.push_back(i);

	// Move through the list, adding 42 to each item.
	for (MyIntLList::MyIterator it = myList.Begin(); it != myList.End(); ++it)
		(*it)->mValue += 42;
}


#include <iostream>
#include <string>
#include "4.4.1_Aggregate.h"

class Money {
	int m_data;

public:
	Money(int a = 0) : m_data(a) {}

	void SetMoney(int a) {
		m_data = a;
	}

	int GetMoney() {
		return m_data;
	}
};

class Name {
	std::string m_name;

public:
	Name(std::string name) : m_name(name) {}

	const std::string &GetName() const {
		return m_name;
	}

	friend std::ostream &operator<<(std::ostream& out, Name name) {
		out << name.GetName();
		return out;
	}
};

struct NameLessComparator {
	bool operator()(const Name &lhs, const Name &rhs) const {
		return (lhs.GetName() < rhs.GetName());
	}
};

void iterator3() {
	// Sample 1
	std::cout << "________________Iterator with int______________________________________" << std::endl;
	aggregate<int> agg;

	for (int i = 0; i < 10; ++i)
		agg.add(i);

	Iterator<int, aggregate<int> > *it = agg.create_iterator();
	for (it->first(); !it->isDone(); it->next())
		std::cout << *(it->current()) << std::endl;

	delete it;

	// Sample 2
	aggregate<Money> agg2;
	agg2.add(Money(100));
	agg2.add(Money(100));
	agg2.add(Money(10000));

	std::cout << "________________Iterator with Class Money______________________________" << std::endl;
	Iterator<Money, aggregate<Money> > *it2 = agg2.create_iterator();
	for (it2->first(); !it2->isDone(); it2->next())
		std::cout << it2->current()->GetMoney() << std::endl;

	delete it2;

	// Sample 3
	std::cout << "________________Set Iterator with Class Name______________________________" << std::endl;

	aggregateSet<Name, NameLessComparator> aset;
	aset.add(Name("Qmt"));
	aset.add(Name("Bmt"));
	aset.add(Name("Cmt"));
	aset.add(Name("Amt"));

	setIterator<Name, NameLessComparator, aggregateSet<Name, NameLessComparator> > *it3 = aset.create_iterator();
	for (it3->first(); !it3->isDone(); it3->next())
		std::cout << *(it3->current()) << std::endl;

	delete it3;
}

/* Console output:

________________Iterator with int______________________________________
0
1
2
3
4
5
6
7
8
9
________________Iterator with Class Money______________________________
100
1000
10000
________________Set Iterator with Class Name___________________________
Amt
Bmt
Cmt
Qmt
*/