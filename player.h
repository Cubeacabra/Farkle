#pragma once
#include "die.h"
#include <vector>
#include <iostream>

class Player {
	private:
		int playerID;
		int score;
		vector<Die> dice;
	public:
		Player(); //Default With 6 Normal Die
		Player(vector<Die>& newDie, int newID); //For Using Weighted Die
		void updateScore(const int newPoints);
		vector<Die>& getDie();
		int getScore() const;
		int getID() const;
		void setBadDie(int index); //Makes the rollable bool false
};
