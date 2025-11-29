//Write your last name and your partner's name here
#include <iostream>
#include "die.h"
#include "player.h"
#include "table.h"
#include "presetDie.h"

using namespace std;

int main() {
	srand(time(0));

	string first, second, third, fourth, fifth;
	Player p1(0);
	Player p2(1);
	vector<Player> players = {p1, p2};
	presetDie special;

	cout << "Welcome to Farkle!" << endl;

	for (Player p : players) {
		cout << "Player " << p.getID() << " Choose an option (1,2,3)" << endl;
		cout << "1) Start the game with regular die" << endl; 
		cout << "2) Play with preset weighted die" << endl;
		cout << "3) Play with custom weighted die" << endl;


		cin >> first;
		while (first != "1" && first != "2" && first != "3") {
			cin >> first;
		}

		if (first == "1") {
			//Dont need extra work, already initialized to default die
		} else if (first == "2") {
			special.printAll();
			//TODO: Prompt user for more information, giving them the choice of die found in presetDie.cc
		} else if (first == "3") {
			//TODO: Prompt user for input, letting them input weights btwn 0 and 1. I would recomend prompting them first
			//      for how many values they will input (so how many sides are on the die) and then having them input their
			//      prefered dice weights. Read these into a vector of doubles, then make sure all the weights in the vector add
			//      up to between 0.99 and 1.01. Lastly, call initDice and pass in this vector for the player
		} else {
			cout << "Bad Input!!" << endl;
		}
	}

	while (true) {
		//TODO: game logic
		break;
	}

}
