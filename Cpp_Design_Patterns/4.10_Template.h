#pragma once

/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Template_Method

Template Method

By defining a skeleton of an algorithm in an operation, deferring some steps to
subclasses, the Template Method lets subclasses redefine certain steps of that
algorithm without changing the algorithm's structure. */

#include <ctime>
#include <assert.h>
#include <iostream>

/* An abstract class that is common to several games in which players play
against the others, but only one is playing at a given time. */

// Interface/base class
class Game {
protected:
	int m_playersCount;
	int m_movesCount;
	int m_playerWon;

public:
	Game() : m_playersCount(0), m_movesCount(0), m_playerWon(-1) {
		srand((unsigned)time(NULL));
	}

	void playOneGame(const int playersCount = 0) {

		m_playersCount = playersCount;
		m_movesCount = 0;
		m_playerWon = -1;

		initializeGame();

		// Some games have fixed no. of players setup within initializeGame()
		assert(m_playersCount); 

		int curr_player = 0;
		while (!endOfGame()) {
			makePlay(curr_player);
			curr_player = (curr_player + 1) % m_playersCount;
			if (!curr_player) {
				++m_movesCount;
			}
		}

		printWinner();
	}

protected:
	virtual void initializeGame() = 0;
	virtual void makePlay(int) = 0;
	virtual bool endOfGame() const = 0;
	virtual void printWinner() const = 0;
};

// Now we can extend this class in order to implement actual games:
class Monopoly : public Game {

	void initializeGame() override {
		// Initialize players' money 
		// Shuffle chance and community chance cards
	}

	// Process one turn for player
	void makePlay(int player) override {
		// Takes at least 20 turns for a player to win
		if (m_movesCount < 20)
			return;

		// Decide winner according to Monopoly rules
		const int chances = (m_movesCount > 199) ? 199 : m_movesCount;
		const int random = rand() * 200 / RAND_MAX;
		if (random < chances)
			m_playerWon = player;
	}

	bool endOfGame() const override {
		return m_playerWon != -1;
	}

	void printWinner() const override {
		assert(m_playerWon >= 0 && m_playerWon < m_playersCount);

		// Display the winning player
		std::cout << "Monopoly player " << m_playerWon << " won in " << m_movesCount << " moves." << std::endl;
	}
};

class Chess : public Game {

	void initializeGame() override {
		m_playersCount = 2;
		// Place the pieces on the board
	}

	// Process one turn for player
	void makePlay(int player) override  {

		// Takes at least 10 turns for a player to win
		if (m_movesCount < 10)
			return;

		// Decide winner if Checkmate or Stalemate has been reached
		const int chances = (m_movesCount > 99) ? 99 : m_movesCount;
		const int random = rand() * 100 / RAND_MAX;
		if (random < chances)
			m_playerWon = player;
	}

	bool endOfGame() const override {
		return m_playerWon != -1;
	}

	void printWinner() const override {
		assert(m_playerWon >= 0 && m_playerWon < m_playersCount);

		// Display the winning player
		std::cout << "Chess Player " << m_playerWon << " won in " << m_movesCount << " moves." << std::endl;
	}
};


void template_pattern() {

	Chess chess;
	for (unsigned i = 0; i < 10; ++i)
		chess.playOneGame();

	Monopoly monopoly;
	for (unsigned i = 0; i < 10; ++i)
		monopoly.playOneGame((i % 7) + 2);
}