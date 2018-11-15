#pragma once

/* 
https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Curiously_Recurring_Template 
https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern

The curiously recurring template pattern (CRTP) is an idiom in C++ in which
a class X derives from a class template instantiation using X itself as a
template argument. */

// The Curiously Recurring Template Pattern (CRTP)
template<class T>
class Base {
	// methods within Base can use template to access members of Derived
};

class Derived : public Base<Derived> {
	// ...
};

/* Object counter

The main purpose of an object counter is retrieving statistics of object creation
and destruction for a given class. This can be easily solved using CRTP as show below.

Each time an object of class X is created, the constructor of counter<X> is called,
incrementing both the created and alive count. Each time an object of class X is
destroyed, the alive count is decremented. It is important to note that counter<X>
and counter<Y> are two separate classes and this is why they will keep separate
counts of X's and Y's. In this example of CRTP, this distinction of classes is the
only use of the template parameter (T in counter<T>) and the reason why we cannot
use a simple un-templated base class. */

template <typename T>
struct counter {
	static int objects_created;
	static int objects_alive;

	counter() {
		++objects_created;
		++objects_alive;
	}

	counter(const counter&) {
		++objects_created;
		++objects_alive;
	}

protected:
	// objects should never be removed through pointers of this type
	~counter() {
		--objects_alive;
	}
};

template <typename T>
int counter<T>::objects_created(0);

template <typename T>
int counter<T>::objects_alive(0);

class X : counter<X> {
	// ...
};

class Y : counter<Y> {
	// ...
};