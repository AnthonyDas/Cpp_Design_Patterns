#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Mediator

Mediator

Define an object that encapsulates how a set of objects interact. Mediator promotes
loose coupling by keeping objects from referring to each other explicitly, and it
lets you vary their interaction independently. */

#include <iostream>
#include <string>
#include <list>
#include <array>
#include <memory>

class ColleagueInterface; // Forward declaration

class MediatorInterface {
	std::list<std::shared_ptr<ColleagueInterface> > colleagueList;

public:

	virtual void distributeMessage(const ColleagueInterface*, const std::string&) const = 0; // Pure virtual

	virtual void registerColleague(std::shared_ptr<ColleagueInterface> colleague) {
		colleagueList.emplace_back(colleague);
	}

protected:
	const std::list<std::shared_ptr<ColleagueInterface> >& getColleagueList() const {
		return colleagueList;
	}
};

class ColleagueInterface {
	std::string name;

public:
	ColleagueInterface(const std::string& newName) : name(newName) {}
	std::string getName() const { return name; }

	virtual void sendMessage(const MediatorInterface&, const std::string&) const = 0; // Pure virtual
	virtual void receiveMessage(const ColleagueInterface*, const std::string&) const = 0; // Pure virtual
};

class Colleague : public ColleagueInterface {
public:

	Colleague(const std::string& newName) : ColleagueInterface(newName) {};

	virtual void sendMessage(const MediatorInterface& mediator, const std::string& message) const override {
		mediator.distributeMessage(this, message);
	}

	virtual void receiveMessage(const ColleagueInterface* sender, const std::string& message) const override {
		std::cout << getName() << " received the message from " << sender->getName() << ": " << message << std::endl;
	}
};


class Mediator : public MediatorInterface {

	void distributeMessage(const ColleagueInterface* sender, const std::string& message) const override {
		for (const std::shared_ptr<ColleagueInterface> x : getColleagueList())
			if (x.get() != sender)  // Do not send the message back to the sender
				x->receiveMessage(sender, message);
	}
};

void mediator() {
	std::shared_ptr<ColleagueInterface> bob = std::make_shared<Colleague>("Bob");
	std::shared_ptr<ColleagueInterface> sam = std::make_shared<Colleague>("Sam");
	std::shared_ptr<ColleagueInterface> frank = std::make_shared<Colleague>("Frank");
	std::shared_ptr<ColleagueInterface> tom = std::make_shared<Colleague>("Tom");

	std::array<std::shared_ptr<ColleagueInterface>, 4> staff = { bob, sam, frank, tom };

	Mediator mediatorStaff;
	for (std::shared_ptr<ColleagueInterface> x : staff)
		mediatorStaff.registerColleague(x);

	bob->sendMessage(mediatorStaff, "I'm quitting this job!");

	// Sam's buddies only
	Mediator mediatorSamsBuddies;
	mediatorSamsBuddies.registerColleague(frank);
	mediatorSamsBuddies.registerColleague(tom);

	sam->sendMessage(mediatorSamsBuddies, "Hooray!  He's gone!  Let's go for a drink, guys!");
}