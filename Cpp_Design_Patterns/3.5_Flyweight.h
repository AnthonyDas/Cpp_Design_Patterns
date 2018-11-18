#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Flyweight

Flyweight

The pattern for saving memory (basically) by sharing properties of objects. Imagine
a huge number of similar objects which all have most of their properties the same.
It is natural to move these properties out of these objects to some external data
structure and provide each object with the link to that data structure. */

#include <iostream>
#include <string>
#include <vector>

#define NUMBER_OF_SAME_TYPE_CHARS 3;

// Actual flyweight objects class (forward declaration)
class FlyweightCharacter;

/* FlyweightCharacterAbstractBuilder is a class holding the properties which are shared by
many objects. So instead of keeping these properties in those objects we keep them externally,
making objects flyweight. See more details in the comments of flyweight() function. */
class FlyweightCharacterAbstractBuilder {
	FlyweightCharacterAbstractBuilder() {}
	~FlyweightCharacterAbstractBuilder() {}

public:
	static std::vector<float> fontSizes; // let's imagine that sizes may be of floating point type
	static std::vector<std::string> fontNames; // font name may be of variable length (take 6 bytes as average)

	static void setFontsAndNames() {
		fontSizes[0] = 1.0;
		fontSizes[1] = 1.5;
		fontSizes[2] = 2.0;

		fontNames[0] = "first_font";
		fontNames[1] = "second_font";
		fontNames[2] = "third_font";
	}

	static FlyweightCharacter createFlyweightCharacter(unsigned short, unsigned short, unsigned short);
};

std::vector<float> FlyweightCharacterAbstractBuilder::fontSizes(3);

std::vector<std::string> FlyweightCharacterAbstractBuilder::fontNames(3);

class FlyweightCharacter {
	unsigned short fontSizeIndex; // index instead of actual font size
	unsigned short fontNameIndex; // index instead of font name

	unsigned positionInStream;

public:

	FlyweightCharacter(unsigned short fontSizeIndex, unsigned short fontNameIndex, unsigned short positionInStream) :
		fontSizeIndex(fontSizeIndex), fontNameIndex(fontNameIndex), positionInStream(positionInStream) {}

	void print() {
		std::cout << "Font Size: " << FlyweightCharacterAbstractBuilder::fontSizes[fontSizeIndex]
			<< ", font Name: " << FlyweightCharacterAbstractBuilder::fontNames[fontNameIndex]
			<< ", character stream position: " << positionInStream << std::endl;
	}

	~FlyweightCharacter() {}
};

FlyweightCharacter FlyweightCharacterAbstractBuilder::createFlyweightCharacter(
	unsigned short fontSizeIndex, unsigned short fontNameIndex, unsigned short positionInStream) {

	FlyweightCharacter fc(fontSizeIndex, fontNameIndex, positionInStream);

	return fc;
}


void flyweight() {
	std::vector<FlyweightCharacter> chars;

	FlyweightCharacterAbstractBuilder::setFontsAndNames();
	unsigned short limit = NUMBER_OF_SAME_TYPE_CHARS;

	for (unsigned short i = 0; i < limit; ++i) {
		chars.push_back(FlyweightCharacterAbstractBuilder::createFlyweightCharacter(0, 0, i));
		chars.push_back(FlyweightCharacterAbstractBuilder::createFlyweightCharacter(1, 1, (unsigned short)(i + 1 * limit)));
		chars.push_back(FlyweightCharacterAbstractBuilder::createFlyweightCharacter(2, 2, (unsigned short)(i + 2 * limit)));
	}

	/* Each chararacter object stores links to its fontName and fontSize.

	Each object, instead of allocating 6 bytes for average 6-char fontName string
	(convention stated above) and 4 bytes for fontSize float, instead allocates 2
	bytes for each of fontNameIndex and fontSizeIndex.

	That means for each object we save 6 + 4 - 2 - 2 = 6 bytes. Now imagine we have
	NUMBER_OF_SAME_TYPE_CHARS = 1000, i.e. with our code we will have 3 groups of
	chars with 1000 chars in each group which will save
	3 * 1000 * 6 - (3 * 6 + 3 * 4) = 17970 saved bytes, where (3 * 6 + 3 * 4)
	is the number of bytes allocated by FlyweightCharacterAbstractBuilder.

	So the idea of the pattern is to move properties shared by many objects to some
	external container. The objects in that case don't store the data themselves they
	store only links to the data which saves memory and makes the objects lighter. */
	for (unsigned short i = 0; i < chars.size(); i++) {
		chars[i].print();
	}
}