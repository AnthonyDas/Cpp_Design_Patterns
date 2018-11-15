#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Command

Command

Command pattern is an object behavioral pattern that decouples sender and receiver
by encapsulating a request as an object, thereby letting you parameterize clients
with different requests, queue or log requests, and support undo-able operations.
It can also be thought of as an object orientated equivalent of call back method.

Call Back: It is a function that is registered to be called at some later point in
time based on the user's actions. */

#include <iostream>

// The Command interface
class Command {
public:
	virtual void execute() = 0; // Pure virtual
};

// Receiver class
class Light {
public:
	Light() {}

	void turnOn() {
		std::cout << "The light is on" << std::endl;
	}

	void turnOff() {
		std::cout << "The light is off" << std::endl;
	}
};

// Command for turning on the light
class FlipUpCommand : public Command {
	Light& theLight;

public:

	FlipUpCommand(Light& light) : theLight(light) {}

	virtual void execute() override {
		theLight.turnOn();
	}
};

// Command for turning off the light
class FlipDownCommand : public Command {
	Light& theLight;

public:
	FlipDownCommand(Light& light) : theLight(light) {}

	virtual void execute() override {
		theLight.turnOff();
	}
};

class Switch {
	Command& flipUpCommand;
	Command& flipDownCommand;

public:
	Switch(Command& flipUpCmd, Command& flipDownCmd)
		: flipUpCommand(flipUpCmd), flipDownCommand(flipDownCmd) {}

	void flipUp() {
		flipUpCommand.execute();
	}

	void flipDown() {
		flipDownCommand.execute();
	}
};
