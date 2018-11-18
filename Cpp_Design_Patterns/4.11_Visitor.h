#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Visitor

Visitor

The Visitor Pattern will represent an operation to be performed on the elements of an
object structure by letting you define a new operation without changing the classes
of the elements on which it operates. */

#include <string>
#include <iostream>
#include <vector>

class Wheel;
class Engine;
class Body;
class Car;

// Interface to all car 'parts'
class CarElementVisitor {
public:
	virtual void visit(Wheel& wheel) const = 0;
	virtual void visit(Engine& engine) const = 0;
	virtual void visit(Body& body) const = 0;

	virtual void visitCar(Car& car) const = 0;

	virtual ~CarElementVisitor() = default;
};

// Interface to one part
class CarElement {
public:
	virtual void accept(const CarElementVisitor& visitor) = 0; // Pure virtual
	virtual ~CarElement() = default;
};

// There are four wheels with unique names
class Wheel : public CarElement {
	std::string m_name;

public:
	explicit Wheel(const std::string& name) :m_name(name) {}

	const std::string& getName() const {
		return m_name;
	}
	void accept(const CarElementVisitor& visitor) override {
		visitor.visit(*this);
	}
};

class Engine : public CarElement {
public:
	void accept(const CarElementVisitor& visitor) override  {
		visitor.visit(*this);
	}
};

class Body : public CarElement {
public:
	void accept(const CarElementVisitor& visitor) override  {
		visitor.visit(*this);
	}
};

// Car - all car elements (parts) together
class Car {
	std::vector<std::unique_ptr<CarElement> > elements;

public:
	std::vector<std::unique_ptr<CarElement> >& getElements() {
		return elements;
	}

	Car() {
		// Assume that neither emplace_back nor Wheel(const string&) emit exceptions
		elements.emplace_back(std::make_unique<Wheel>("front left"));
		elements.emplace_back(std::make_unique<Wheel>("front right"));
		elements.emplace_back(std::make_unique<Wheel>("back left"));
		elements.emplace_back(std::make_unique<Wheel>("back right"));
		elements.emplace_back(std::make_unique<Body>());
		elements.emplace_back(std::make_unique<Engine>());
	}
};

// CarElementPrintVisitor and CarElementDoVisitor show via different implementations
// that the Car class is unchanged.
class CarElementPrintVisitor : public CarElementVisitor {
public:
	// These are specific implementations added to the original object
	// without modifying the original class
	void visit(Wheel& wheel) const {
		std::cout << "Visiting " << wheel.getName() << " wheel" << std::endl;
	}
	void visit(Engine& engine) const {
		std::cout << "Visiting engine" << std::endl;
	}
	void visit(Body& body) const {
		std::cout << "Visiting body" << std::endl;
	}

	void visitCar(Car& car) const {
		std::cout << "Visiting car" << std::endl;
		for (auto it = car.getElements().begin(); it != car.getElements().end(); ++it) {
			(*it)->accept(*this);	// this issues the callback i.e. to this from the element  
		}
		std::cout << "Visited car" << std::endl;
	}
};

class CarElementDoVisitor : public CarElementVisitor {
public:
	void visit(Wheel& wheel) const {
		std::cout << "Kicking my " << wheel.getName() << " wheel" << std::endl;
	}
	void visit(Engine& engine) const {
		std::cout << "Starting my engine" << std::endl;
	}
	void visit(Body& body) const {
		std::cout << "Moving my body" << std::endl;
	}

	void visitCar(Car& car) const {
		std::cout << std::endl << "Starting my car" << std::endl;
		for (auto it = car.getElements().begin(); it != car.getElements().end(); ++it) {
			(*it)->accept(*this);	// this issues the callback i.e. to this from the element  
		}
		std::cout << "Started car" << std::endl;
	}
};

void visitor() {
	Car car;
	CarElementPrintVisitor printVisitor;
	CarElementDoVisitor doVisitor;

	printVisitor.visitCar(car);
	doVisitor.visitCar(car);
}