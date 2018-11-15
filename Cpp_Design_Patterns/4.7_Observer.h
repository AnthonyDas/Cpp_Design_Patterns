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

// The Abstract Observer
class ObserverBoardInterface {
public:
	virtual void update(double a, double b, double c) = 0;
};

// Abstract Interface for Displays
class DisplayBoardInterface {
public:
	virtual void show() = 0;
};

// The Abstract Subject
class WeatherDataInterface
{
public:
	virtual void registerOb(ObserverBoardInterface* ob) = 0;
	virtual void removeOb(ObserverBoardInterface* ob) = 0;
	virtual void notifyOb() = 0;
};

// The Concrete Subject
class ParaWeatherData : public WeatherDataInterface {
	double m_humidity;
	double m_temperature;
	double m_pressure;
	std::list<ObserverBoardInterface* > m_obs;

public:
	void SensorDataChange(double a, double b, double c) {
		m_humidity = a;
		m_temperature = b;
		m_pressure = c;
		notifyOb();
	}

	void registerOb(ObserverBoardInterface* ob) {
		m_obs.push_back(ob);
	}

	void removeOb(ObserverBoardInterface* ob) {
		m_obs.remove(ob);
	}

protected:
	void notifyOb() {
		std::list<ObserverBoardInterface*>::iterator pos = m_obs.begin();
		while (pos != m_obs.end())
		{
			((ObserverBoardInterface*)(*pos))->update(m_humidity, m_temperature, m_pressure);
			(dynamic_cast<DisplayBoardInterface*>(*pos))->show();
			++pos;
		}
	}
};

// A Concrete Observer
class CurrentConditionBoard : public ObserverBoardInterface, public DisplayBoardInterface {
	double m_h;
	double m_t;
	double m_p;
	ParaWeatherData& m_data;

public:
	CurrentConditionBoard(ParaWeatherData& a) :m_data(a) {
		m_data.registerOb(this);
	}

	void show() {
		std::cout << "_____CurrentConditionBoard_____" << std::endl;
		std::cout << "humidity: " << m_h << std::endl;
		std::cout << "temperature: " << m_t << std::endl;
		std::cout << "pressure: " << m_p << std::endl;
		std::cout << "_______________________________" << std::endl;
	}

	void update(double h, double t, double p) {
		m_h = h;
		m_t = t;
		m_p = p;
	}
};

// A Concrete Observer
class StatisticBoard : public ObserverBoardInterface, public DisplayBoardInterface {
	double m_maxt;
	double m_mint;
	double m_avet;
	int m_count;
	ParaWeatherData& m_data;

public:
	StatisticBoard(ParaWeatherData& a) :m_maxt(-1000), m_mint(1000), m_avet(0), m_count(0), m_data(a) {
		m_data.registerOb(this);
	}

	void show() {
		std::cout << "________StatisticBoard_________" << std::endl;
		std::cout << "lowest  temperature: " << m_mint << std::endl;
		std::cout << "highest temperature: " << m_maxt << std::endl;
		std::cout << "average temperature: " << m_avet << std::endl;
		std::cout << "_______________________________" << std::endl;
	}

	void update(double h, double t, double p) {
		++m_count;
		if (t > m_maxt) {
			m_maxt = t;
		}
		if (t < m_mint) {
			m_mint = t;
		}
		m_avet = (m_avet * (m_count - 1) + t) / m_count;
	}
};


void observer() {

	ParaWeatherData * wdata = new ParaWeatherData;
	CurrentConditionBoard* currentB = new CurrentConditionBoard(*wdata);
	StatisticBoard* statisticB = new StatisticBoard(*wdata);

	wdata->SensorDataChange(10.2, 28.2, 1001);
	wdata->SensorDataChange(12, 30.12, 1003);
	wdata->SensorDataChange(10.2, 26, 806);
	wdata->SensorDataChange(10.3, 35.9, 900);

	wdata->removeOb(currentB);

	wdata->SensorDataChange(100, 40, 1900);

	delete statisticB;
	delete currentB;
	delete wdata;
}