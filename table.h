#pragma once
#include "player.h"
#include <iostream>
#include <vector>

class Table {
	private:
		int currScore;
		vector<Die> diceValues;
		vector<int> frequency;
		int maxSides;
		bool Farkled;
		void setFreq();
	public:
		Table();

		void rollAllDie(Player& p);
		void printResults();
		bool isFarkle();
		void keepDice(Player& p);
		void cleanTable();
		int getScore();
		void computeScore(vector<int> vec);
		bool isValidCombo(vector<int> vec);
};
