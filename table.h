#pragma once
#include "player.h"
#include <iostream>
#include <vector>

class Table {
	private:
		int currScore;
		vector<int> diceValues;
		bool Farkled;
	public:
		Table();

		void rollAllDie(Player& p);
		void printResults();
		bool isFarkle();
		void keepDice(Player& p);
		void cleanTable();
};
