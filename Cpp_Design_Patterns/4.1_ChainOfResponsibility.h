#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Chain_of_Responsibility

Chain of Responsibility

Chain of Responsibility pattern has the intent to avoid coupling the sender of a
request to its receiver by giving more than one object a chance to handle the request.
Chains the receiving objects and passes the requests along the chain until an object
handles it.*/

#include <iostream>
#include <memory>

// Abstract class
class Handler {
protected:
	std::unique_ptr<Handler> next;

public:
	Handler() : next(nullptr) {};
	
	virtual ~Handler() {}

	virtual void request(int value) = 0; // Pure virtual

	void setNextHandler(std::unique_ptr<Handler>&& nextInLine) {
		next = std::move(nextInLine);
	}
};

// Concrete
class SpecialHandler : public Handler {
	int myLimit;
	int myId;

public:
	SpecialHandler(int limit, int id) {
		myLimit = limit;
		myId = id;
	}

	~SpecialHandler() {}

	void request(int value) {
		if (value < myLimit) {
			std::cout << "Handler " << myId << " handled the request with a limit of " << myLimit << std::endl;
		}
		else if (next != nullptr) {
			next->request(value);
		}
		else {
			std::cout << "Sorry, I am the last handler (" << myId << ") and I can't handle the request." << std::endl;
		}
	}
};

void chain_of_responsibility() {
	std::unique_ptr<Handler> h1 = std::make_unique<SpecialHandler>(10, 1);
	std::unique_ptr<Handler> h2 = std::make_unique<SpecialHandler>(20, 2);
	std::unique_ptr<Handler> h3 = std::make_unique<SpecialHandler>(30, 3);

	h2->setNextHandler(std::move(h3));
	h1->setNextHandler(std::move(h2));
	
	h1->request(18);

	h1->request(40);
}