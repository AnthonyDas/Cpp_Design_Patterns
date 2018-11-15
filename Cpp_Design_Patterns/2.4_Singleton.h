#pragma once;

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Singleton

Singleton

The Singleton pattern ensures that a class has only one instance and provides a global
point of access to that instance. It is named after the singleton set, which is defined
to be a set containing one element. This is useful when exactly one object is needed
to coordinate actions across the system.

Check list:

- Define a private static attribute in the "single instance" class.
- Define a public static accessor function in the class.
- Do "lazy initialization" (creation on first use) in the accessor function.
- Define all constructors to be protected or private.
- Clients may only use the accessor function to manipulate the Singleton.

Let's take a look at how a Singleton differs from other variable types.

Like a global variable, the Singleton exists outside of the scope of any functions.
Traditional implementation uses a static member function of the Singleton class, which
will create a single instance of the Singleton class on the first call, and forever
return that instance. The following code example illustrates the elements of a C++
singleton class, that simply stores a single string. */

#include <string>
#include <memory>

class StringSingleton {
	// private data for an instance of this class
	std::string m_string;

public:
	// Some accessor functions for the class, itself
	std::string getString() const {
		return m_string;
	}
	void setString(const std::string &newStr) {
		m_string = newStr;
	}

	// Function which allows access to the instance of the class from anywhere
	// Call: StringSingleton::Instance();
	static StringSingleton &Instance() {
		// This line only runs once, thus creating the only instance in existence
		static std::unique_ptr<StringSingleton> instance = std::make_unique<StringSingleton>();

		// dereferencing the variable here, saves the caller from having to use 
		// the arrow operator, and removes temptation to try and delete the 
		// returned instance.
		return *instance; // always returns the same instance
	}

	// Disallow copy constructor and assignment operator
	StringSingleton(const StringSingleton &) = delete;
	const StringSingleton &operator=(const StringSingleton &) = delete;

	StringSingleton() {};

	~StringSingleton() {};

private:
	// Default constructor available only to members or friends of this class
	// StringSingleton() {}; 

	// Although this should be allowed, some compilers may not implement
	// private destructors. This prevents others from deleting our one single
	// instance, which was otherwise created on the heap
	// ~StringSingleton() {};
};

/* Applications of Singleton Class:

One common use of the singleton design pattern is for application configurations.
Configurations may need to be accessible globally, and future expansions to the
application configurations may be needed. The subset C's closest alternative would
be to create a single global struct. This had the lack of clarity as to where this
object was instantiated, as well as not guaranteeing the existence of the object.

Take, for example, the situation of another developer using your singleton inside
the constructor of their object. Then, yet another developer decides to create an
instance of the second class in the global scope. If you had simply used a global
variable, the order of linking would then matter. Since your global will be accessed,
possibly before main begins executing, there is no definition as to whether the global
is initialized, or the constructor of the second class is called first. This behavior
can then change with slight modifications to other areas of code, which would change
order of global code execution. Such an error can be very hard to debug. But, with
use of the singleton, the first time the object is accessed, the object will also 
be created. You now have an object which will always exist, in relation to being used,
and will never exist if never used.

A second common use of this class is in updating old code to work in a new architecture.
Since developers may have used globals liberally, moving them into a single class and
making it a singleton, can be an intermediary step to bring the program inline to
stronger object oriented structure.

In the next example, the first call to Singleton::GetInstance will initialize the singleton
instance. This example is for illustrative purposes only; for anything but a trivial
example program, this code contains errors.*/

#include <iostream>
#include <mutex>

class Singleton {
	
	static std::mutex m;

public:

	static Singleton& GetInstance() {
		std::lock_guard<std::mutex> lck(m);

		std::cout << "Get Instance" << std::endl;

		// Initialized during first access
		static Singleton inst(1);

		return inst;
	}

	int m_a;

	~Singleton() { std::cout << "In Destructor" << std::endl; }

	// Prevent copying
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:

	Singleton(int a) : m_a(a) { std::cout << "In Constructor" << std::endl; }
};
