#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Iterator

Iterator

The 'iterator' design pattern is used liberally within the STL for traversal of
various containers. The full understanding of this will liberate a developer to
create highly reusable and easily understandable[citation needed] data containers.

The basic idea of the iterator is that it permits the traversal of a container (like
a pointer moving across an array). However, to get to the next element of a container,
you need not know anything about how the container is constructed. This is the iterators
job. By simply using the member functions provided by the iterator, you can move, in
the intended order of the container, from the first element to the last element.

Let us start by considering a traditional single dimensional array with a pointer
moving from the start to the end. This example assumes knowledge of pointer arithmetic.
Note that the use of "it" or "itr," henceforth, is a short version of "iterator". */

void iterator() {
	const int ARRAY_LEN = 42;
	int *myArray = new int[ARRAY_LEN];
	// Set the iterator to point to the first memory location of the array
	int *arrayItr = myArray;
	// Move through each element of the array, setting it equal to its position in the array
	for (int i = 0; i < ARRAY_LEN; ++i)
	{
		// set the value of the current location in the array
		*arrayItr = i;
		// by incrementing the pointer, we move it to the next position in the array.
		// This is easy for a contiguous memory container, since pointer arithmetic 
		// handles the traversal.
		++arrayItr;
	}
	// Do not be messy, clean up after yourself
	delete[] myArray;
}

/* This code works very quickly for arrays, but how would we traverse a linked list,
when the memory is not contiguous? Consider the implementation of a rudimentary linked
list as follows: */

class IteratorCannotMoveToNext {}; // Error class

class MyIntLList {
public:
	// The Node class represents a single element in the linked list. 
	// The node has a next node and a previous node, so that the user 
	// may move from one position to the next, or step back a single 
	// position. Notice that the traversal of a linked list is O(N), 
	// as is searching, since the list is not ordered.
	class Node {
	public:
		Node() :mNextNode(0), mPrevNode(0), mValue(0) {}
		Node *mNextNode;
		Node *mPrevNode;
		int mValue;
	};

	MyIntLList() : mSize(0) {}

	~MyIntLList() {
		while (!Empty())
			pop_front();
	} // See expansion for further implementation;

	int Size() const { return mSize; }

	// Add this value to the end of the list
	void push_back(int value) {
		Node *newNode = new Node;
		newNode->mValue = value;
		newNode->mPrevNode = mTail;
		mTail->mNextNode = newNode;
		mTail = newNode;
		++mSize;
	}
	// Remove the value from the beginning of the list
	void pop_front() {
		if (Empty())
			return;
		Node *tmpnode = mHead;
		mHead = mHead->mNextNode;
		delete tmpnode;
		--mSize;
	}
	bool Empty() {
		return mSize == 0;
	}

	// This is where the iterator definition will go, 
	// but lets finish the definition of the list, first

private:
	Node *mHead;
	Node *mTail;
	int mSize;
};

/* This linked list has non-contiguous memory, and is therefore not a candidate
for pointer arithmetic. And we do not want to expose the internals of the list 
to other developers, forcing them to learn them, and keeping us from changing it.

This is where the iterator comes in. The common interface makes learning the usage
of the container easier, and hides the traversal logic from other developers.

Let us examine the code for the iterator, itself. */
