#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Builder

Builder

The Builder Creational Pattern is used to separate the construction of a complex
object from its representation so that the same construction process can create
different objects representations.

Problem

We want to construct a complex object, however we do not want to have a complex
constructor member or one that would need many arguments.

Solution

Define an intermediate object whose member functions define the desired object part
by part before the object is available to the client.Builder Pattern lets us defer
the construction of the object until all the options for creation have been specified.*/

#include <string>
#include <iostream>
#include <memory>

// "Product"
class Pizza2_1 {
	std::string m_dough;
	std::string m_sauce;
	std::string m_topping;

public:
	void setDough(const std::string& dough) {
		m_dough = dough;
	}
	void setSauce(const std::string& sauce) {
		m_sauce = sauce;
	}
	void setTopping(const std::string& topping) {
		m_topping = topping;
	}
	void print() const {
		std::cout << "Pizza with " << m_dough << " dough, " << m_sauce << " sauce and "
			<< m_topping << " topping. Mmm." << std::endl;
	}
};

// "Abstract Builder"
class PizzaBuilder {
public:
	virtual ~PizzaBuilder() {};

	Pizza2_1* createPizza() {
		m_pizza = std::make_unique<Pizza2_1>();
		buildDough();
		buildSauce();
		buildTopping();
		return m_pizza.release();
	}

	virtual void buildDough() = 0; // Pure virtual
	virtual void buildSauce() = 0; // Pure virtual
	virtual void buildTopping() = 0; // Pure virtual

protected:
	std::unique_ptr<Pizza2_1> m_pizza;
};

//----------------------------------------------------------------

class HawaiianPizzaBuilder : public PizzaBuilder {
public:
	virtual ~HawaiianPizzaBuilder() {};

	virtual void buildDough() {
		m_pizza->setDough("cross");
	}
	virtual void buildSauce() {
		m_pizza->setSauce("mild");
	}
	virtual void buildTopping() {
		m_pizza->setTopping("ham+pineapple");
	}
};

class SpicyPizzaBuilder : public PizzaBuilder {
public:
	virtual ~SpicyPizzaBuilder() {};

	virtual void buildDough() {
		m_pizza->setDough("pan baked");
	}
	virtual void buildSauce() {
		m_pizza->setSauce("hot");
	}
	virtual void buildTopping() {
		m_pizza->setTopping("pepperoni+salami");
	}
};
