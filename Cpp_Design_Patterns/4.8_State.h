#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#State

State

The State Pattern allows an object to alter its behavior when its internal
state changes. The object will appear as having changed its class. */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>

enum class Input { DUCK_DOWN, STAND_UP, JUMP, DIVE };

// Forward declarations
class Fighter;
class StandingState; 
class JumpingState; 
class DivingState;

class FighterState {
public:
	// Need to postpone initialisation as incomplete types 
	static std::shared_ptr<FighterState> standing;
	static std::shared_ptr<FighterState> diving;
	static std::shared_ptr<FighterState> ducking;
	static std::shared_ptr<FighterState> jumping;

	virtual ~FighterState() = default;

	virtual void handleInput(Fighter&, Input) = 0; // Pure virtual
	virtual void update(Fighter&) = 0; // Pure virtual
};

class Fighter {
	std::string m_name;
	std::shared_ptr<FighterState> m_state;
	int m_fatigueLevel = std::rand() % 10;

public:
	Fighter(const std::string& name) : m_name(name), m_state(FighterState::standing) {}

	std::string getName() const {
		return m_name;
	}

	int getFatigueLevel() const {
		return m_fatigueLevel;
	}

	// Delegate input handling to current 'state'.
	virtual void handleInput(Input input) {
		m_state->handleInput(*this, input);
	}

	void changeState(std::shared_ptr<FighterState> state) {
		m_state = state;
		// Delegate updating to new 'state'
		m_state->update(*this);
	}

	void standsUp() { std::cout << getName() << " stands up." << std::endl; }
	void ducksDown() { std::cout << getName() << " ducks down." << std::endl; }
	void jumps() { std::cout << getName() << " jumps into the air." << std::endl; }
	void dives() { std::cout << getName() << " makes a dive attack in the middle of the jump!" << std::endl; }
	void feelsStrong() { std::cout << getName() << " feels strong!" << std::endl; }

	void changeFatigueLevelBy(int change) {
		m_fatigueLevel += change;
		std::cout << "fatigueLevel = " << m_fatigueLevel << std::endl;
	}
};

class DuckingState : public FighterState {
	int chargingTime;
	static const int FullRestTime = 5;

public:
	DuckingState() : chargingTime(0) {}

	virtual void handleInput(Fighter& fighter, Input input) override {
		switch (input) {
		case Input::STAND_UP:  
			fighter.changeState(FighterState::standing); 
			fighter.standsUp();
			break;
		case Input::DUCK_DOWN:
			std::cout << fighter.getName() << " remains in ducking position, ";
			if (chargingTime < FullRestTime) {
				std::cout << "recovering in the meantime." << std::endl;
			}
			else {
				std::cout << "fully recovered." << std::endl;
			}
			update(fighter);
			break;
		default:
			std::cout << "One cannot do that while ducking.  " << fighter.getName()
				<< " remains in ducking position by default." << std::endl;
			update(fighter);
			break;
		}
	}

	virtual void update(Fighter& fighter) override {
		++chargingTime;
		std::cout << "Charging time = " << chargingTime << "." << std::endl;
		if (fighter.getFatigueLevel() > 0)
			fighter.changeFatigueLevelBy(-1);
		if (chargingTime >= FullRestTime && fighter.getFatigueLevel() <= 3)
			fighter.feelsStrong();
	}
};

class StandingState : public FighterState {
public:
	virtual void handleInput(Fighter& fighter, Input input) override {
		switch (input) {
		case Input::STAND_UP: 
			std::cout << fighter.getName() << " remains standing." << std::endl; 
			break;
		case Input::DUCK_DOWN:
			fighter.ducksDown();
			fighter.changeState(FighterState::ducking);
			break;
		case Input::JUMP:
			fighter.jumps();
			fighter.changeState(FighterState::jumping);
		default:
			std::cout << "One cannot do that while standing.  " << fighter.getName()
				<< " remains standing by default." << std::endl;
			break;
		}
	}

	virtual void update(Fighter& fighter) override {
		if (fighter.getFatigueLevel() > 0)
			fighter.changeFatigueLevelBy(-1);
	}
};

class JumpingState : public FighterState {
	int jumpingHeight;

public:
	JumpingState() {
		jumpingHeight = std::rand() % 5 + 1;
	}

	virtual void handleInput(Fighter& fighter, Input input) override {
		switch (input) {
		case Input::DIVE:
			fighter.changeState(FighterState::diving);
			fighter.dives();
			break;
		default:
			std::cout << "One cannot do that in the middle of a jump.  " << fighter.getName()
				<< " lands from his jump and is now standing again." << std::endl;
			fighter.changeState(FighterState::standing);
			break;
		}
	}

	virtual void update(Fighter& fighter) override {
		std::cout << fighter.getName() << " has jumped " << jumpingHeight
			<< " feet into the air." << std::endl;

		if (jumpingHeight >= 3)
			fighter.changeFatigueLevelBy(1);
	}
};

class DivingState : public FighterState {
public:
	virtual void handleInput(Fighter& fighter, Input) override  {
		std::cout << "Regardless of what the user input is, " << fighter.getName()
			<< " lands from his dive and is now standing again." << std::endl;

		fighter.changeState(FighterState::standing);
	}

	virtual void update(Fighter& fighter) override  {
		fighter.changeFatigueLevelBy(2);
	}
};

std::shared_ptr<FighterState> FighterState::standing(new StandingState);
std::shared_ptr<FighterState> FighterState::diving(new DivingState);
std::shared_ptr<FighterState> FighterState::ducking(new DuckingState);
std::shared_ptr<FighterState> FighterState::jumping(new JumpingState);

void state() {
	std::srand((unsigned int)std::time(nullptr));
	Fighter rex("Rex the Fighter"), borg("Borg the Fighter");
	std::cout << rex.getName() << " and " << borg.getName() << " are currently standing." << std::endl;

	int choice;
	auto chooseAction = [&choice](Fighter& fighter) { // Lambda
		std::cout << std::endl
			<< static_cast<int>(Input::DUCK_DOWN) << ") Duck down  "
			<< static_cast<int>(Input::STAND_UP) << ") Stand up  "
			<< static_cast<int>(Input::JUMP) << ") Jump  "
			<< static_cast<int>(Input::DIVE) << ") Dive in the middle of a jump" << std::endl;

		std::cout << "Choice for " << fighter.getName() << "? ";
		std::cin >> choice;
		fighter.handleInput(static_cast<Input>(choice));
	};

	
	chooseAction(rex);
	chooseAction(borg);
}