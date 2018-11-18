#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Strategy

Strategy

Defines a family of algorithms, encapsulates each one, and make them interchangeable.
Strategy lets the algorithm vary independently from clients who use it. */

#include <iostream>

class StrategyInterface {
public:
	virtual void execute() const = 0; // Pure virtual
};

class ConcreteStrategyA : public StrategyInterface {
public:
	void execute() const override {
		std::cout << "Called ConcreteStrategyA execute method" << std::endl;
	}
};

class ConcreteStrategyB : public StrategyInterface {
public:
	void execute() const override {
		std::cout << "Called ConcreteStrategyB execute method" << std::endl;
	}
};

class ConcreteStrategyC : public StrategyInterface {
public:
	void execute() const override {
		std::cout << "Called ConcreteStrategyC execute method" << std::endl;
	}
};

class Context {
	StrategyInterface * m_strategy;

public:
	explicit Context(StrategyInterface *strategy) : m_strategy(strategy) {}

	void set_strategy(StrategyInterface *strategy) {
		m_strategy = strategy;
	}

	void execute() const {
		m_strategy->execute();
	}
};

void strategy() {
	ConcreteStrategyA concreteStrategyA;
	ConcreteStrategyB concreteStrategyB;
	ConcreteStrategyC concreteStrategyC;

	Context contextA(&concreteStrategyA);
	Context contextB(&concreteStrategyB);
	Context contextC(&concreteStrategyC);

	contextA.execute(); // output: "Called ConcreteStrategyA execute method"
	contextB.execute(); // output: "Called ConcreteStrategyB execute method"
	contextC.execute(); // output: "Called ConcreteStrategyC execute method"

	contextA.set_strategy(&concreteStrategyB);
	contextA.execute(); // output: "Called ConcreteStrategyB execute method"
	contextA.set_strategy(&concreteStrategyC);
	contextA.execute(); // output: "Called ConcreteStrategyC execute method"
}