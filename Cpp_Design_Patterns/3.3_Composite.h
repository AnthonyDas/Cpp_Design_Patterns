#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Composite

Composite

Composite lets clients treat individual objects and compositions of objects uniformly.
The Composite pattern can represent both the conditions. In this pattern, one can 
develop tree structures for representing part-whole hierarchies. */

#include <vector>
#include <iostream> 
#include <memory>
#include <algorithm> // std::for_each

class Graphic {
public:
	virtual void print() const = 0;
	virtual ~Graphic() {}
};

class Ellipse : public Graphic {
public:
	void print() const override {
		std::cout << "Ellipse" << std::endl;
	}
};

class CompositeGraphic : public Graphic {
	std::vector<Graphic*>  graphicList_;

public:
	void print() const override {
		for (Graphic* a : graphicList_) {
			a->print();
		}
	}

	void add(Graphic *aGraphic) {
		graphicList_.push_back(aGraphic);
	}
};

void composite() {
	// Initialize four ellipses
	const std::unique_ptr<Ellipse> ellipse1 = std::make_unique<Ellipse>();
	const std::unique_ptr<Ellipse> ellipse2 = std::make_unique<Ellipse>();
	const std::unique_ptr<Ellipse> ellipse3 = std::make_unique<Ellipse>();
	const std::unique_ptr<Ellipse> ellipse4 = std::make_unique<Ellipse>();

	// Initialize three composite graphics
	const std::unique_ptr<CompositeGraphic> graphic = std::make_unique<CompositeGraphic>();
	const std::unique_ptr<CompositeGraphic> graphic1 = std::make_unique<CompositeGraphic>();
	const std::unique_ptr<CompositeGraphic> graphic2 = std::make_unique<CompositeGraphic>();

	// Composes the graphics
	graphic->add(graphic1.get());
	graphic->add(graphic2.get());

	graphic1->add(ellipse1.get());
	graphic1->add(ellipse2.get());
	graphic1->add(ellipse3.get());

	graphic2->add(ellipse4.get());

	// Prints the complete graphic (four times the string "Ellipse")
	graphic->print();
}