#pragma once
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

class Die {
	unsigned int SIDES;
	vector<double> weight;
	unsigned int last_roll;
	bool rollable;
	std::string description;
	int dieIndex = 0;
	public:
	Die(); //Create a fair die
	Die(vector<double> new_weights, int new_sides, std::string newDescription); //Create a cheater die
	int get_roll(); //Return the last value rolled
	void roll(); //Set the die to a random value
	bool canRoll() const; //Checks if you can roll it, since you cant if you stored it's value for that turn
	void setCanRoll(bool b); //Make it so you can/cant roll die
	void printSelf();
	int getSides();
	void setIndex(int newIndex);
	int getDieIndex();
};
