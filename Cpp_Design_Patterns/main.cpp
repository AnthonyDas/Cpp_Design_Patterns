#include <iostream>

#include "2.1_Builder.h"
#include "2.2_Factory.h"
#include "2.3_Prototype.h"
#include "2.4_Singleton.h"

#include "3.1_Adapter.h"
#include "3.2_Bridge.h"
#include "3.3_Composite.h"
#include "3.3.1_Decorator.h"

void builder() {
	HawaiianPizzaBuilder hawaiianPizzaBuilder;
	SpicyPizzaBuilder    spicyPizzaBuilder;

	Pizza2_1* pizza1 = hawaiianPizzaBuilder.createPizza();
	pizza1->print();

	Pizza2_1* pizza2 = spicyPizzaBuilder.createPizza();
	pizza2->print();
};

// Create all available pizzas and print their prices
void pizza_information(PizzaFactory::PizzaType pizzatype) {
	std::unique_ptr<Pizza2_2> pizza = PizzaFactory::createPizza(pizzatype);
	std::cout << "Price of " << pizzatype << " is " << pizza->getPrice() << std::endl;
}

void factory() {
	pizza_information(PizzaFactory::PizzaType::HamMushroom);
	pizza_information(PizzaFactory::PizzaType::Deluxe);
	pizza_information(PizzaFactory::PizzaType::Hawaiian);
}

void prototype() {
	RecordFactory recordFactory;

	auto record = recordFactory.createRecord(CAR);
	record->print();

	record = recordFactory.createRecord(BIKE);
	record->print();

	record = recordFactory.createRecord(PERSON);
	record->print();
}

/* A client of one of the concrete monster classes only needs a reference (pointer)
to a CPrototypeMonster class object to be able to call the �Clone� function and
create copies of that object. The function below demonstrates this concept: */

#include <cassert>

void DoSomeStuffWithAMonster(const CPrototypeMonster* originalMonster) {
	CPrototypeMonster* newMonster = originalMonster->Clone();
	assert(newMonster);

	newMonster->Name("MyOwnMonster");
	// Add code doing all sorts of cool stuff with the monster.
	delete newMonster;
}

/* Now originalMonster can be passed as a pointer to CGreenMonster, CPurpleMonster
or CBellyMonster. */

void singleton() {
	Singleton& singleton = Singleton::GetInstance();
	std::cout << "The value of the singleton: " << singleton.m_a << std::endl;
}

int main() {

	builder();
	factory();
	prototype();
	singleton();

	adapter();
	bridge();
	composite();
	decorator1();
	decorator2();

	std::cout << "Finished - please type something to quit";
	int dummy;
	std::cin >> dummy;
	return EXIT_SUCCESS;
}