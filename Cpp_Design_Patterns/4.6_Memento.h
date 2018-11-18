#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Memento

Memento

Without violating encapsulation the Memento Pattern will capture and externalize
an object’s internal state so that the object can be restored to this state later.
Though the Gang of Four uses friend as a way to implement this pattern it is not
the best design. It can also be implemented using PIMPL (pointer to implementation
or opaque pointer). Best Use case is 'Undo-Redo' in an editor.

The Originator (the object to be saved) creates a snap-shot of itself as a Memento
object, and passes that reference to the Caretaker object. The Caretaker object
keeps the Memento until such a time as the Originator may want to revert to a
previous state as recorded in the Memento object.

See memoize for an old-school example of this pattern. */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

template <typename T>
std::string toString(const T& t) {
	std::stringstream ss;
	ss << t;
	return ss.str();
}

class Memento; // Forward declaration

class Object {
	int value;
	std::string base_name;
	double decimal;  
	// ... and suppose there are loads of other data members

public:
	Object(int v) : value(v), base_name("Object: "), decimal((double)value / 100) {}

	void doubleValue() {
		value = 2 * value;
		decimal = (double)value / 100;
	}

	void increaseByOne() { 
		++value;
		decimal = (double)value / 100;
	}
	
	int getValue() const { return value; }
	std::string getName() const { return base_name + toString(value); }
	double getDecimal() const { return decimal; }

	std::unique_ptr<Memento> createMemento() const {
		return std::make_unique<Memento>(*this);
	}

	// Defined later as Memento an incomplete type here
	void reinstateMemento(Memento* );
};

class Memento {
	Object object;

public:
	Memento(const Object& obj) : object(obj) {}

	// Want a snapshot of Object itself because of its many data members
	const Object& snapshot() const { return object; }
};

// Memento now a complete type
void Object::reinstateMemento(Memento* mem) {
	*this = mem->snapshot();
}

class Command2 {

	// Function pointer - function on Object which takes no params and returns void
	using Action = void (Object::*)();

	std::shared_ptr<Object> receiver;
	Action action;

	static std::vector<Command2*> commands;
	static std::vector<std::unique_ptr<Memento> > mementos;
	static size_t numCommands;
	static size_t maxCommands;

public:
	Command2(std::shared_ptr<Object> rec, Action act) : receiver(rec), action(act) {}

	virtual void execute() {
		// saves the last value
		if (mementos.size() < numCommands + 1)
			mementos.resize(numCommands + 1);
		mementos[numCommands] = receiver->createMemento();  

		// saves the last command
		if (commands.size() < numCommands + 1)
			commands.resize(numCommands + 1);
		commands[numCommands] = this;  

		if (numCommands > maxCommands)
			maxCommands = numCommands;
		++numCommands;

		(receiver.get()->*action)();
	}

	static void undo() {
		if (numCommands == 0) {
			std::cout << "There is nothing to undo" << std::endl;
			return;
		}
		commands[numCommands - 1]->receiver->reinstateMemento(mementos[numCommands - 1].get());
		--numCommands;
	}

	void static redo() {
		if (numCommands > maxCommands) {
			std::cout << "There is nothing to redo" << std::endl;
			return;
		}
		Command2* commandRedo = commands[numCommands];
		(commands[numCommands]->receiver.get()->*(commandRedo->action))();
		++numCommands;
	}
};

std::vector<Command2*> Command2::commands;
std::vector<std::unique_ptr<Memento> > Command2::mementos;
size_t Command2::numCommands = 0;
size_t Command2::maxCommands = 0;

void memento() {
	int i;
	std::cout << "Memento Test: Please enter an integer: ";
	std::cin >> i;

	std::shared_ptr<Object> object = std::make_shared<Object>(i);

	Command2 double_command(object, &Object::doubleValue);
	Command2 increment_command(object, &Object::increaseByOne);

	std::cout << "0.Exit,  1.Double,  2.Increase by one,  3.Undo,  4.Redo: ";
	std::cin >> i;

	while (i) {
		if (i == 1)
			double_command.execute();
		else if (i == 2)
			increment_command.execute();
		else if (i == 3)
			Command2::undo();
		else if (i == 4)
			Command2::redo();
		else {
			std::cout << "Invalid choice. Please try again: ";
			std::cin >> i;
			continue;
		}

		std::cout << " " << object->getValue() << "  " << object->getName() << "  " << object->getDecimal() << std::endl;
		std::cout << "0.Exit,  1.Double,  2.Increase by one,  3.Undo,  4.Redo: ";
		std::cin >> i;
	}
}