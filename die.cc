#include "die.h"
#include <cassert>
#include <iomanip>
using namespace std;

Die::Die() : SIDES(6), last_roll(0) {
	rollable = true;
	for (unsigned int i = 0; i < SIDES; i++)
		weight.push_back(1.0/SIDES);
}

Die::Die(vector<double> new_weights, const int new_sides, string newDescription) : SIDES(new_sides), last_roll(0) {
	description = newDescription;
	rollable = true;
	assert(new_sides >= 4);
	//cerr << description << endl;
	assert(new_weights.size() == SIDES);
	double sum = 0;
	for (unsigned int i = 0; i < SIDES; i++) {
		assert(new_weights[i] >= 0 && new_weights[i] <= 1);
		sum += new_weights[i];
		weight.push_back(new_weights[i]);
	}
	assert(sum > .99 && sum < 1.01);
}

int Die::get_roll() {
//`	cerr << "last roll is " << last_roll << endl;
	assert(last_roll >= 1 && last_roll <= SIDES);
	return last_roll;
}

void Die::roll() {
	//TODO: Implement weight system
	double val =(rand() / double(RAND_MAX)); //Generates a double btwn 0 and 1 for more accuracy
	for (int i = 0; i < weight.size(); i++) {
		val -= weight.at(i);
		//cerr << "weight is: " << weight.at(i) << " and i is " << i << " and roll is " << last_roll << endl;
		if (val <= 0) {
			last_roll = i + 1;
			return;
		}
	}
	last_roll = SIDES;
}
bool Die::canRoll() const {
	return rollable;	
}	
void Die::setCanRoll(bool b) {
	rollable = b;
}
void Die::printSelf() {
	cout << description << ": ";
	for (double d : weight) {
		cout << fixed << setprecision(2) << d << "% ";
	}
	cout << endl;
}
int Die::getSides() {
	return SIDES;
}
