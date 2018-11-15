#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Factory

Factory

Definition: A utility class that creates an instance of a class from a family of
derived classes

Abstract Factory

Definition: A utility class that creates an instance of several families of classes.
It can also return a factory for a certain group.

The Factory Design Pattern is useful in a situation that requires the creation of many
different types of objects, all derived from a common base type. The Factory Method
defines a method for creating the objects, which subclasses can then override to specify
the derived type that will be created. Thus, at runtime, the Factory Method can be passed
a description of a desired object (e.g., a string read from user input) and return a base
class pointer to a new instance of that object. The pattern works best when a well-designed
interface is used for the base class, so there is no need to cast the returned object.

Problem

We want to decide at runtime what object is to be created based on some configuration or
application parameter. When we write the code, we do not know what class should be instantiated.

Solution

Define an interface for creating an object, but let subclasses decide which class to instantiate.
Factory Method lets a class defer instantiation to subclasses.

In the following example, a factory method is used to create laptop or desktop computer objects
at runtime.

Let's start by defining Computer, which is an abstract base class (interface) and its derived
classes: Laptop and Desktop.*/

#include <string>

class Computer {
public:
	virtual void Run() = 0; // Pure virtual
	virtual void Stop() = 0; // Pure virtual

	virtual ~Computer() {};
};

class Laptop : public Computer {
	bool m_Hibernating; // Whether or not the machine is hibernating

public:
	void Run() override { m_Hibernating = false; };
	void Stop() override { m_Hibernating = true; };

	virtual ~Laptop() {};
};

class Desktop : public Computer {
	bool m_On; // Whether or not the machine has been turned on

public:
	void Run() override { m_On = true; };
	void Stop() override { m_On = false; };

	virtual ~Desktop() {};
};

// The actual ComputerFactory class returns a Computer, given a real world description of the object.
class ComputerFactory {
public:
	static Computer* NewComputer(const std::string &description) {
		if (description == "laptop")
			return new Laptop;
		if (description == "desktop")
			return new Desktop;
		return nullptr;
	}
};

/* Let's analyze the benefits of this design. First, there is a compilation benefit. If we
move the interface Computer into a separate header file with the factory, we can then move
the implementation of the NewComputer() function into a separate implementation file. Now
the implementation file for NewComputer() is the only one that requires knowledge of the
derived classes. Thus, if a change is made to any derived class of Computer, or a new Computer
subtype is added, the implementation file for NewComputer() is the only file that needs to be
recompiled. Everyone who uses the factory will only care about the interface, which should
remain consistent throughout the life of the application.

Also, if there is a need to add a class, and the user is requesting objects through a user
interface, no code calling the factory may be required to change to support the additional
computer type. The code using the factory would simply pass on the new string to the factory,
and allow the factory to handle the new types entirely.

Imagine programming a video game, where you would like to add new types of enemies in the future,
each of which has different AI functions and can update differently. By using a factory method,
the controller of the program can call to the factory to create the enemies, without any dependency
or knowledge of the actual types of enemies. Now, future developers can create new enemies, with
new AI controls and new drawing member functions, add it to the factory, and create a level which
calls the factory, asking for the enemies by name. Combine this method with an XML description of
levels, and developers could create new levels without having to recompile their program. All this,
thanks to the separation of creation of objects from the usage of objects.

Another example:*/

#include <stdexcept>
#include <iostream>
#include <memory>

class Pizza2_2 {
public:
	virtual int getPrice() const = 0; // Pure virtual
	virtual ~Pizza2_2() {};
};

class HamAndMushroomPizza : public Pizza2_2 {
public:
	virtual int getPrice() const { return 850; };
	virtual ~HamAndMushroomPizza() {};
};

class DeluxePizza : public Pizza2_2 {
public:
	virtual int getPrice() const { return 1050; };
	virtual ~DeluxePizza() {};
};

class HawaiianPizza : public Pizza2_2 {
public:
	virtual int getPrice() const { return 1150; };
	virtual ~HawaiianPizza() {};
};

class PizzaFactory {
public:
	enum PizzaType {
		HamMushroom,
		Deluxe,
		Hawaiian
	};

	static std::unique_ptr<Pizza2_2> createPizza(PizzaType pizzaType) {
		switch (pizzaType) {
		case HamMushroom: return std::make_unique<HamAndMushroomPizza>();
		case Deluxe:      return std::make_unique<DeluxePizza>();
		case Hawaiian:    return std::make_unique<HawaiianPizza>();
		}
		throw "invalid pizza type";
	}
};