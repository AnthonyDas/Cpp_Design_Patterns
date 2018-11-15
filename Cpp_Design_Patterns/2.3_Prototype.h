#pragma once

/*https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Prototype

Prototype

A prototype pattern is used in software development when the type of objects to create
is determined by a prototypical instance, which is cloned to produce new objects. This
pattern is used, for example, when the inherent cost of creating a new object in the
standard way is prohibitively expensive for a given application.

Implementation:

Declare an abstract base class that specifies a pure virtual clone() method. Any class
that needs a "polymorphic constructor" capability derives itself from the abstract base
class, and implements the clone() operation.

Here the client code first invokes the factory method. This factory method, depending
on the parameter, finds out the concrete class. On this concrete class, the clone()
method is called and the object is returned by the factory method.

This is a sample implementation of Prototype method. We have the detailed description
of all the components here.

- Record class, which is a pure virtual class that has a pure virtual method clone().
- CarRecord, BikeRecord and PersonRecord as concrete implementation of a Record class.
- An enum RecordType as one to one mapping of each concrete implementation of Record class.
- RecordFactory class that has a Factory method CreateRecord(…). This method requires
an enum RecordType as parameter and depending on this parameter it returns the concrete
implementation of Record class. */

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>

// Record is the base Prototype
class Record {
public:
	virtual ~Record() {}
	virtual void print() = 0; // Pure virtual
	virtual std::unique_ptr<Record> clone() = 0; // Pure virtual
};

// CarRecord is a Concrete Prototype
class CarRecord : public Record {

	std::string m_carName;
	int m_ID;

public:
	CarRecord(std::string carName, int ID) : m_carName(carName), m_ID(ID) {};

	void print() override {
		std::cout << "Car Record\n"
			<< "Name  : " << m_carName << "\n"
			<< "Number: " << m_ID << "\n" << std::endl;
	}

	std::unique_ptr<Record> clone() override {
		return std::make_unique<CarRecord>(*this); // Compiler generated copy constructor
	}
};

/* BikeRecord is the Concrete Prototype */
class BikeRecord : public Record {

	std::string m_bikeName;
	int m_ID;

public:
	BikeRecord(std::string bikeName, int ID) : m_bikeName(bikeName), m_ID(ID) {};

	void print() override {
		std::cout << "Bike Record\n"
			<< "Name  : " << m_bikeName << "\n"
			<< "Number: " << m_ID << "\n" << std::endl;
	}

	std::unique_ptr<Record> clone() override {
		return std::make_unique<BikeRecord>(*this); // Compiler generated copy constructor
	}
};

/* PersonRecord is the Concrete Prototype */
class PersonRecord : public Record {

	std::string m_personName;
	int m_age;

public:
	PersonRecord(std::string personName, int age) : m_personName(personName), m_age(age) {};

	void print() override {
		std::cout << "Person Record\n"
			<< "Name : " << m_personName << "\n"
			<< "Age  : " << m_age << "\n" << std::endl;
	}

	std::unique_ptr<Record> clone() override {
		return std::make_unique<PersonRecord>(*this); // Compiler generated copy constructor
	}
};

// Opaque record type, avoids exposing concrete implementations
enum RecordType { CAR, BIKE, PERSON };

// RecordFactory is the client
class RecordFactory {

	std::unordered_map<RecordType, std::unique_ptr<Record>, std::hash<int> > m_records;

public:
	RecordFactory() {
		m_records[CAR] = std::make_unique<CarRecord>("Ferrari", 5050);
		m_records[BIKE] = std::make_unique<BikeRecord>("Yamaha", 2525);
		m_records[PERSON] = std::make_unique<PersonRecord>("Tom", 25);
	}

	std::unique_ptr<Record> createRecord(RecordType recordType) {
		return m_records[recordType]->clone();
	}
};

/* Another example:

To implement the pattern, declare an abstract base class that specifies a pure virtual clone()
member function. Any class that needs a "polymorphic constructor" capability derives itself from
the abstract base class, and implements the clone() operation.

The client, instead of writing code that invokes the new operator on a hard-wired class name,
calls the clone() member function on the prototype, calls a factory member function with a parameter
designating the particular concrete derived class desired, or invokes the clone() member function
through some mechanism provided by another design pattern. */

class CPrototypeMonster {
protected:
	std::string m_name;

public:
	
	virtual ~CPrototypeMonster() {};

	virtual CPrototypeMonster* Clone() const = 0; // Pure virtual

	void Name(std::string name) { m_name = name;  }
	std::string Name() const { return m_name; }
};

class CGreenMonster : public CPrototypeMonster {
protected:
	int m_numberOfArms;
	double m_slimeAvailable;

public:

	virtual CPrototypeMonster* Clone() const {
		return new CGreenMonster(*this);
	}

	void NumberOfArms(int numberOfArms) { m_numberOfArms = numberOfArms; }
	void SlimeAvailable(double slimeAvailable) { m_slimeAvailable = slimeAvailable; }

	int NumberOfArms() const { return m_numberOfArms; }
	double SlimeAvailable() const { return m_slimeAvailable; }
};

class CPurpleMonster : public CPrototypeMonster {
protected:
	int m_intensityOfBadBreath;
	double m_lengthOfWhiplikeAntenna;

public:

	virtual CPrototypeMonster* Clone() const {
		return new CPurpleMonster(*this);
	}

	void IntensityOfBadBreath(int intensityOfBadBreath) { m_intensityOfBadBreath = intensityOfBadBreath; }
	void LengthOfWhiplikeAntenna(double lengthOfWhiplikeAntenna) { m_lengthOfWhiplikeAntenna = lengthOfWhiplikeAntenna; }

	int IntensityOfBadBreath() const { return m_intensityOfBadBreath; }
	double LengthOfWhiplikeAntenna() const { return m_lengthOfWhiplikeAntenna; }
};

class CBellyMonster : public CPrototypeMonster {
protected:
	double m_roomAvailableInBelly;

public:

	virtual CPrototypeMonster* Clone() const {
		return new CBellyMonster(*this);
	}

	void RoomAvailableInBelly(double roomAvailableInBelly) { m_roomAvailableInBelly = roomAvailableInBelly; }
	double RoomAvailableInBelly() const { return m_roomAvailableInBelly; }
};
