#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Facade

Facade

The Facade Pattern hides the complexities of the system by providing an interface
to the client from where the client can access the system on a unified interface.
Facade defines a higher-level interface that makes the subsystem easier to use.
For instance making one class method perform a complex process by calling several
other classes. 

Facade is one of the easiest patterns... And this is very simple example.

Imagine you set up a smart house where everything is on remote. So to turn the lights
on you push lights on button - And same for TV, AC, Alarm, Music, etc...

When you leave a house you would need to push a 100 buttons to make sure everything 
is off and are good to go which could be little annoying if you are lazy like me.
So I defined a Facade for leaving and coming back. (Facade functions represent buttons...)
So when I come and leave I just make one call and it takes care of everything...*/

#include <string>
#include <iostream>

class Alarm {
public:
	void alarmOn() {
		std::cout << "Alarm is on and house is secured" << std::endl;
	}

	void alarmOff() {
		std::cout << "Alarm is off and you can go into the house" << std::endl;
	}
};

class Ac {
public:
	void acOn() {
		std::cout << "Ac is on" << std::endl;
	}

	void acOff() {
		std::cout << "AC is off" << std::endl;
	}
};

class Tv {
public:
	void tvOn() {
		std::cout << "TV is on" << std::endl;
	}

	void tvOff() {
		std::cout << "TV is off" << std::endl;
	}
};

class HouseFacade {
	Alarm alarm;
	Ac ac;
	Tv tv;

public:
	HouseFacade() {}

	void goToWork() {
		ac.acOff();
		tv.tvOff();
		alarm.alarmOn();
	}

	void comeHome() {
		alarm.alarmOff();
		ac.acOn();
		tv.tvOn();
	}
};

void facade() {
	HouseFacade hf;

	// Rather than calling 100 different on and off functions, thanks to facade I only have 2 functions...
	hf.goToWork();
	hf.comeHome();
}

/* The output of the program above is:

AC is off
TV is off
Alarm is on and house is secured
Alarm is off and you can go into the house
Ac is on
Tv is on
*/