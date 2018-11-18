#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Decorator

Decorator

The decorator pattern helps to attach additional behavior or responsibilities to an
object dynamically. Decorators provide a flexible alternative to subclassing for 
extending functionality. This is also called “Wrapper”.

If your application does some kind of filtering, then Decorator might be good pattern
to consider for the job.*/

#include <string>
#include <iostream>
#include <memory>

// Our Abstract base class
class Car1 {
protected:
	std::string m_str;

public:
	Car1() : m_str("Unknown Car") {};

	virtual std::string getDescription() {
		return m_str;
	}

	virtual double getCost() = 0; // Pure virtual

	virtual ~Car1() {
		std::cout << "~Car()" << std::endl;
	}
};

// Decorator Base class
class OptionsDecorator : public Car1 {
public:

	// virtual std::string getDescription() = 0; // Pure virtual

	virtual ~OptionsDecorator() {
		std::cout << "~OptionsDecorator()" << std::endl;
	}
};


class CarModel1 : public Car1 {
public:
	CarModel1() {
		m_str = "CarModel1";
	}
	
	virtual double getCost() override {
		return 31000.23;
	}

	~CarModel1() {
		std::cout << "~CarModel1()" << std::endl;
	}
};


class Navigation : public OptionsDecorator {
	std::unique_ptr<Car1> m_b;

public:
	Navigation(std::unique_ptr<Car1>&& b) : m_b(std::move(b)) {};
	
	std::string getDescription() {
		return m_b->getDescription() + ", Navigation";
	}

	double getCost() {
		return 300.56 + m_b->getCost();
	}
	~Navigation() {
		std::cout << "~Navigation()" << std::endl;
	}
};

class PremiumSoundSystem : public OptionsDecorator {
	std::unique_ptr<Car1> m_b;
public:
	PremiumSoundSystem(std::unique_ptr<Car1>&& b) : m_b(std::move(b)) {};

	std::string getDescription() {
		return m_b->getDescription() + ", PremiumSoundSystem";
	}

	double getCost(){
		return 0.30 + m_b->getCost();
	}
	~PremiumSoundSystem() {
		std::cout << "~PremiumSoundSystem()" << std::endl;
	}
};

class ManualTransmission : public OptionsDecorator {
	std::unique_ptr<Car1> m_b;
public:
	ManualTransmission(std::unique_ptr<Car1>&& b) : m_b(std::move(b)) {};

	std::string getDescription() {
		return m_b->getDescription() + ", ManualTransmission";
	}

	double getCost() {
		return 0.30 + m_b->getCost();
	}
	~ManualTransmission() {
		std::cout << "~ManualTransmission()" << std::endl;
	}
};

void decorator1() {
	// Create our Car that we want to buy
	std::unique_ptr<Car1> b = std::make_unique<CarModel1>();

	std::cout << "Base model of " << b->getDescription() << " costs $" << b->getCost() << std::endl;

	// Who wants just a base model, let's add some more features!

	b = std::make_unique<Navigation>(std::move(b));
	std::cout << b->getDescription() << " will cost you $" << b->getCost() << std::endl;
	b = std::make_unique<PremiumSoundSystem>(std::move(b));
	b = std::make_unique<ManualTransmission>(std::move(b));
	std::cout << b->getDescription() << " will cost you $" << b->getCost() << std::endl;
}

/* The output of the above program is :

Base model of CarModel1 costs $31000.2
CarModel1, Navigation will cost you $31300.8
CarModel1, Navigation, PremiumSoundSystem, ManualTransmission will cost you $31301.4
~ManualTransmission
~PremiumSoundSystem()
~Navigation()
~CarModel1
~Car()
~OptionsDecorator()
~Car()
~OptionsDecorator()
~Car()
~OptionsDecorator()
~Car()
*/

// Another example(C++14):

class Interface {
public:
	virtual ~Interface() { }
	virtual void write(std::string&) = 0;
};

class Core : public Interface {
public:
	~Core() { std::cout << "Core destructor" << std::endl; }
	virtual void write(std::string& text) override { /* Do nothing*/ }; 
};

class Decorator : public Interface {
	std::unique_ptr<Interface> interface;

public:
	Decorator(std::unique_ptr<Interface> c) { interface = std::move(c); }
	virtual void write(std::string& text) override { interface->write(text); }
};

class MessengerWithSalutation : public Decorator {
	std::string salutation;

public:
	MessengerWithSalutation(std::unique_ptr<Interface> c, const std::string& str)
		: Decorator(std::move(c)), salutation(str) {}

	~MessengerWithSalutation() { std::cout << "Messenger destructor" << std::endl; }
	virtual void write(std::string& text) override {
		text = salutation + "\n" + text;
		Decorator::write(text);
	}
};

class MessengerWithValediction : public Decorator {
	std::string valediction;

public:
	MessengerWithValediction(std::unique_ptr<Interface> c, const std::string& str)
		: Decorator(std::move(c)), valediction(str) {}

	~MessengerWithValediction() { std::cout << "MessengerWithValediction destructor" << std::endl; }
	virtual void write(std::string& text) override {
		Decorator::write(text);
		text += "\n" + valediction;
	}
};

void decorator2() {
	const std::string salutation = "Greetings,";
	const std::string valediction = "Sincerly, Andy";
	std::string message1 = "This message is not decorated.";
	std::string message2 = "This message is decorated with a salutation.";
	std::string message3 = "This message is decorated with a valediction.";
	std::string message4 = "This message is decorated with a salutation and a valediction.";

	std::unique_ptr<Interface> messenger1 = std::make_unique<Core>();
	std::unique_ptr<Interface> messenger2 = std::make_unique<MessengerWithSalutation>(std::make_unique<Core>(), salutation);
	std::unique_ptr<Interface> messenger3 = std::make_unique<MessengerWithValediction>(std::make_unique<Core>(), valediction);
	std::unique_ptr<Interface> messenger4 = std::make_unique<MessengerWithValediction>(std::make_unique<MessengerWithSalutation>
		(std::make_unique<Core>(), salutation), valediction);

	messenger1->write(message1);
	std::cout << message1;
	std::cout << "\n------------------------------\n";

	messenger2->write(message2);
	std::cout << message2;
	std::cout << "\n------------------------------\n";

	messenger3->write(message3);
	std::cout << message3;
	std::cout << "\n------------------------------\n";

	messenger4->write(message4);
	std::cout << message4;
	std::cout << "\n------------------------------\n";
}

/* The output of the program above is:

This message is not decorated.
------------------------------
Greetings,
This message is decorated with a salutation.
------------------------------
This message is decorated with a valediction.
Sincerly, Andy
------------------------------
Greetings,
This message is decorated with a salutation and a valediction.
Sincerly, Andy
------------------------------
MessengerWithValediction destructor
Messenger destructor
Core destructor
MessengerWithValediction destructor
Core destructor
Messenger destructor
Core destructor
Core destructor*/