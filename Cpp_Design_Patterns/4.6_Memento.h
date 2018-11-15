#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Memento

Memento

Without violating encapsulation the Memento Pattern will capture and externalize
an object’s internal state so that the object can be restored to this state later.
Though the Gang of Four uses friend as a way to implement this pattern it is not
the best design[citation needed]. It can also be implemented using PIMPL (pointer
to implementation or opaque pointer). Best Use case is 'Undo-Redo' in an editor.

The Originator (the object to be saved) creates a snap-shot of itself as a Memento
object, and passes that reference to the Caretaker object. The Caretaker object
keeps the Memento until such a time as the Originator may want to revert to a
previous state as recorded in the Memento object.

See memoize for an old-school example of this pattern. */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

const std::string NAME = "Object";

template <typename T>
std::string toString(const T& t) {
	std::stringstream ss;
	ss << t;
	return ss.str();
}

class Memento; // Forward declaration

class Object {
	int value;
	std::string name;
	double decimal;  // and suppose there are loads of other data members
public:
	Object(int newValue) : value(newValue), name(NAME + toString(value)), decimal((float)value / 100) {}
	void doubleValue() { value = 2 * value;  name = NAME + toString(value);  decimal = (float)value / 100; }
	void increaseByOne() { value++;  name = NAME + toString(value);  decimal = (float)value / 100; }
	int getValue() const { return value; }
	std::string getName() const { return name; }
	double getDecimal() const { return decimal; }
	Memento* createMemento() const;
	void reinstateMemento(Memento* mem);
};

class Memento {
	Object object;
public:
	Memento(const Object& obj) : object(obj) {}
	Object snapshot() const { return object; }  // want a snapshot of Object itself because of its many data members
};

Memento* Object::createMemento() const {
	return new Memento(*this);
}

void Object::reinstateMemento(Memento* mem) {
	*this = mem->snapshot();
}

class Command {

	typedef void (Object::*Action)();
	Object* receiver;
	Action action;
	static std::vector<Command*> commandList;
	static std::vector<Memento*> mementoList;
	static int numCommands;
	static int maxCommands;
public:
	Command(Object *newReceiver, Action newAction) : receiver(newReceiver), action(newAction) {}
	virtual void execute() {
		if (mementoList.size() < numCommands + 1)
			mementoList.resize(numCommands + 1);
		mementoList[numCommands] = receiver->createMemento();  // saves the last value
		if (commandList.size() < numCommands + 1)
			commandList.resize(numCommands + 1);
		commandList[numCommands] = this;  // saves the last command
		if (numCommands > maxCommands)
			maxCommands = numCommands;
		numCommands++;
		(receiver->*action)();
	}
	static void undo() {
		if (numCommands == 0)
		{
			std::cout << "There is nothing to undo at this point." << std::endl;
			return;
		}
		commandList[numCommands - 1]->receiver->reinstateMemento(mementoList[numCommands - 1]);
		numCommands--;
	}
	void static redo() {
		if (numCommands > maxCommands)
		{
			std::cout << "There is nothing to redo at this point." << std::endl;
			return;
		}
		Command* commandRedo = commandList[numCommands];
		(commandRedo->receiver->*(commandRedo->action))();
		numCommands++;
	}
};

std::vector<Command*> Command::commandList;
std::vector<Memento*> Command::mementoList;
int Command::numCommands = 0;
int Command::maxCommands = 0;

void memento() {
	int i;
	std::cout << "Please enter an integer: ";
	std::cin >> i;
	Object *object = new Object(i);

	Command *commands[3];
	commands[1] = new Command(object, &Object::doubleValue);
	commands[2] = new Command(object, &Object::increaseByOne);

	std::cout << "0.Exit,  1.Double,  2.Increase by one,  3.Undo,  4.Redo: ";
	std::cin >> i;

	while (i != 0)
	{
		if (i == 3)
			Command::undo();
		else if (i == 4)
			Command::redo();
		else if (i > 0 && i <= 2)
			commands[i]->execute();
		else
		{
			std::cout << "Enter a proper choice: ";
			std::cin >> i;
			continue;
		}
		std::cout << "   " << object->getValue() << "  " << object->getName() << "  " << object->getDecimal() << std::endl;
		std::cout << "0.Exit,  1.Double,  2.Increase by one,  3.Undo,  4.Redo: ";
		std::cin >> i;
	}
}