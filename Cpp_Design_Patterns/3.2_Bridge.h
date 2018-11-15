#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Bridge

Bridge

The Bridge Pattern is used to separate out the interface from its implementation.
Doing this gives the flexibility so that both can vary independently.

The following example will output: 
API1.circle at 1:2 7.5
API2.circle at 5:7 27.5
*/

#include <iostream>

// Implementor
class DrawingAPI {
public:
	virtual void drawCircle(double x, double y, double radius) = 0;
	virtual ~DrawingAPI() {}
};

// Concrete ImplementorA
class DrawingAPI1 : public DrawingAPI {
public:
	void drawCircle(double x, double y, double radius) {
		std::cout << "API1.circle at " << x << ':' << y << ' ' << radius << std::endl;
	}
};

// Concrete ImplementorB
class DrawingAPI2 : public DrawingAPI {
public:
	void drawCircle(double x, double y, double radius) {
		std::cout << "API2.circle at " << x << ':' << y << ' ' << radius << std::endl;
	}
};

// Abstraction
class Shape {
public:
	virtual ~Shape() {}
	virtual void draw() = 0;
	virtual void resizeByPercentage(double pct) = 0;
};

// Refined Abstraction
class CircleShape : public Shape {
	double m_x, m_y, m_radius;
	DrawingAPI *m_drawingAPI;
public:
	CircleShape(double x, double y, double radius, DrawingAPI *drawingAPI) :
		m_x(x), m_y(y), m_radius(radius), m_drawingAPI(drawingAPI) {}

	void draw() {
		m_drawingAPI->drawCircle(m_x, m_y, m_radius);
	}
	void resizeByPercentage(double pct) {
		m_radius *= pct;
	}
};

void bridge() {
	CircleShape circle1(1, 2, 3, new DrawingAPI1());
	CircleShape circle2(5, 7, 11, new DrawingAPI2());
	circle1.resizeByPercentage(2.5);
	circle2.resizeByPercentage(2.5);
	circle1.draw();
	circle2.draw();
}