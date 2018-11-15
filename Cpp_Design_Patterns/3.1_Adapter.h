#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Adapter

Adapter

Convert the interface of a class into another interface that clients expect.
Adapter lets classes work together that couldn't otherwise because of incompatible
interfaces. */

#include <iostream>
#include <memory>

// Abstract Target
class Hindu {
public:
	virtual ~Hindu() = default;
	virtual void performsHinduRitual() const = 0;
};

// Concrete Target
class HinduFemale : public Hindu {
public:
	virtual void performsHinduRitual() const override {
		std::cout << "Hindu girl performs Hindu ritual." << std::endl;
	}
};

// Abstract Adaptee
class Muslim {
public:
	virtual ~Muslim() = default;
	virtual void performsMuslimRitual() const = 0;
};

// Concrete Adaptee
class MuslimFemale : public Muslim {
public:
	virtual void performsMuslimRitual() const override {
		std::cout << "Muslim girl performs Muslim ritual." << std::endl;
	}
};

class HinduRitual {
public:
	void carryOutRitual(Hindu *hindu) {
		std::cout << "On with the Hindu rituals!" << std::endl;
		hindu->performsHinduRitual();
	}
};

// Adapter
class HinduAdapter : public Hindu {
private:
	Muslim* muslim;

public:
	HinduAdapter(Muslim* m) : muslim(m) {}

	virtual void performsHinduRitual() const override {
		muslim->performsMuslimRitual();
	}
};

void adapter() {
	std::unique_ptr<Hindu> hinduGirl = std::make_unique<HinduFemale>();
	std::unique_ptr<Muslim> muslimGirl = std::make_unique<MuslimFemale>();

	HinduRitual hinduRitual;

	hinduRitual.carryOutRitual(hinduGirl.get());

	// Following will not compile of course since the parameter must be of type std::unique_ptr<Hindu>.
	// hinduRitual.carryOutRitual(muslimGirl.get());

	// adapt muslimGirl to become a Hindu!
	std::unique_ptr<Hindu> adaptedMuslim = std::make_unique<HinduAdapter>(muslimGirl.get());

	// So now muslimGirl, in the form of adaptedMuslim, participates in the hinduRitual!
	// Note that muslimGirl is carrying out her own type of ritual in hinduRitual though.
	hinduRitual.carryOutRitual(adaptedMuslim.get());
}