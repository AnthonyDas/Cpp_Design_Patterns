#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Observer

Observer

The Observer Pattern defines a one-to-many dependency between objects so that
when one object changes state, all its dependents are notified and updated automatically.

Problem:

In one place or many places in the application we need to be aware about a system
event or an application state change. We'd like to have a standard way of subscribing
to listening for system events and a standard way of notifying the interested parties.
The notification should be automated after an interested party subscribed to the system
event or application state change. There also should be a way to unsubscribe.

Forces:

Observers and observables probably should be represented by objects. The observer
objects will be notified by the observable objects.

Solution:

After subscribing the listening objects will be notified by a way of method call. */

#include <list>
#include <algorithm>
#include <iostream>

// Abstract Observer
class ObserverInterface {
public:
	virtual void update(double a, double b, double c) = 0; // Pure virtual
	virtual void show() const = 0; // Pure virtual
};

// Abstract Subject
class WeatherDataInterface {
public:
	virtual void registerObj(ObserverInterface* ) = 0; // Pure virtual
	virtual void removeObj(ObserverInterface* ) = 0; // Pure virtual
	virtual void notifyObj() = 0;
};

// Concrete Subject
class ParaWeatherData : public WeatherDataInterface {
	double m_humidity;
	double m_temperature;
	double m_pressure;
	std::list<ObserverInterface* > m_objs;

public:
	void SensorDataChange(double a, double b, double c) {
		m_humidity = a;
		m_temperature = b;
		m_pressure = c;
		notifyObj();
	}

	void registerObj(ObserverInterface* obj) override {
		m_objs.push_back(obj);
	}

	void removeObj(ObserverInterface* obj) override {
		m_objs.remove(obj);
	}

protected:
	void notifyObj() override {
		for (auto it = m_objs.begin(); it != m_objs.end(); ++it) {
			(*it)->update(m_humidity, m_temperature, m_pressure);
			(*it)->show();
		}
	}
};

// Concrete Observer
class CurrentCondition : public ObserverInterface{
	double m_h;
	double m_t;
	double m_p;
	ParaWeatherData& m_data;

public:
	CurrentCondition(ParaWeatherData &a) : m_data(a) {
		m_data.registerObj(this);
	}

	void show() const override {
		std::cout << "_____CurrentConditionBoard_____" << std::endl;
		std::cout << "humidity: " << m_h << std::endl;
		std::cout << "temperature: " << m_t << std::endl;
		std::cout << "pressure: " << m_p << std::endl;
		std::cout << "_______________________________" << std::endl;
	}

	void update(double h, double t, double p) override {
		m_h = h;
		m_t = t;
		m_p = p;
	}
};

// A Concrete Observer
class Statistic : public ObserverInterface {
	double m_maxt;
	double m_mint;
	double m_averaget;
	int m_count;
	ParaWeatherData& m_data;

public:
	Statistic(ParaWeatherData& a) :m_maxt(-1000), m_mint(1000), m_averaget(0), m_count(0), m_data(a) {
		m_data.registerObj(this);
	}

	void show() const override {
		std::cout << "________StatisticBoard_________" << std::endl;
		std::cout << "lowest  temperature: " << m_mint << std::endl;
		std::cout << "highest temperature: " << m_maxt << std::endl;
		std::cout << "average temperature: " << m_averaget << std::endl;
		std::cout << "_______________________________" << std::endl;
	}

	void update(double h, double t, double p) override {
		++m_count;
		if (t > m_maxt) {
			m_maxt = t;
		}
		if (t < m_mint) {
			m_mint = t;
		}
		m_averaget = (m_averaget * (m_count - 1) + t) / m_count;
	}
};


void observer() {

	ParaWeatherData wdata;
	CurrentCondition current(wdata);
	Statistic statistic(wdata);

	wdata.SensorDataChange(10.2, 28.2, 1001);
	wdata.SensorDataChange(12, 30.12, 1003);
	wdata.SensorDataChange(10.2, 26, 806);
	wdata.SensorDataChange(10.3, 35.9, 900);

	wdata.removeObj(&current);

	wdata.SensorDataChange(100, 40, 1900);
}