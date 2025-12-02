#include <iostream>
#include "die.h"
#include "player.h"
#include "table.h"
#include "presetDie.h"
#include "/public/colors.h"

using namespace std;

int main() {
	srand(time(0));

	cout << "DOG COLLAR" << endl;
	string first, second, third, fourth, fifth;
	Player p1(0);
	Player p2(1);
	vector<Player> players = {p1, p2};
	presetDie special;
	Table table;
	int endScore = 0;
	int wager = 0;
	bool wonRound = true;

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
			//  while (true) {
			cout << "What dice would you like to start with: ";
			int choice = 0;
			cin >> choice;
			//Die win  = special.getDie(choice);
			std::vector<Die> dice;
			dice.push_back(special.getDie(choice));
			p.initDice(dice);

			//  }
		} else if (first == "3") {
			//TODO: Prompt user for input, letting them input weights btwn 0 and 1. I would recomend prompting them first
			//cout << "You choice 3,
			//      for how many values they will input (so how many sides are on the die) and then having them input their
			//      prefered dice weights. Read these into a vector of doubles, then make sure all the weights in the vector add
			//      up to between 0.99 and 1.01. Lastly, call initDice and pass in this vector for the player
		} else {
			cout << "Bad Input!!" << endl;
		}
	}


	while (true) {
		//TODO: game logic
		if (wonRound) {
			for (int i = 0; i < players.size(); i++) {
				players.at(i).resetScore();
				if (players.at(i).getMoney() <= 0) {
					setcolor(255,165,0);
					cout << "Player " << players.at(i).getID() << " went Bankrupt!! Player ";
					if (i == players.size() - 1) {
						cout << " 0 Wins!!!" << endl;
					} else {
						cout << players.at(i).getID() + 1 << " Wins!!!" << endl;
					}
					setcolor(255,255,255);
					exit(EXIT_SUCCESS);
				}	
			}
			cout << "How much would you like to wager? You Have $" << players.at(0).getMoney() << "  (Enter a number > 0 and < " << players.at(0).getMoney() << " )" << endl;
			cin >> wager;
			if (!cin) {
				cout << "BAD INPUT. PROGRAM DIE NOW" << endl;
				exit(EXIT_FAILURE);
			}

			while (wager < 0 || wager > players.at(0).getMoney()) {
				cout << "Bad Input For Wager!!" << endl;
				cout << "How much would you like to wager? You Have $" << players.at(0).getMoney() << "  (Enter a number > 0 and < " << players.at(0).getMoney() << " )" << endl;
				cin >> ws;
				cin >> wager;
			}
			cout << "How many points do you want to play to? (Input a number)" << endl;
			cin >> endScore;
			wonRound = false;
		}
		for (Player& p : players) {

			if (wonRound) {
				p.setMoney(-1 *wager);
				break;
			}
			bool moveOn = false;
			setcolor(220, 0, 255);
			cout << "Player " << p.getID() << "'s Turn!" << endl;
			setcolor(255,255,255);
			while (!moveOn) {
				setcolor(0,255,255);
				cout << "Player " << p.getID() << "'s total points: " << p.getScore() << endl;
				cout << "Player " << p.getID() << "'s points on the board: " << table.getScore() << endl;
				setcolor(255,255,255);
				//	cerr<< "in loop good" << endl;
				table.rollAllDie(p);
				//	cerr << "rolled die good" << endl;
				if (table.isFarkle()) {
					setcolor(255,0,0);
					cout << "BUST!! YOU FARKLED" << endl;
					setcolor(255,255,255);
					moveOn = true;
					table.cleanTable();
					p.resetDie();
					continue;
				}
				//	cerr << "farkle check good" << endl;
				table.printResults();
				//	cerr << "print good" << endl;
				table.keepDice(p);


				cout << "What will you do?" << endl;
				cout << "1) Keep Playing" << endl;
				cout << "2) End Your Turn" << endl;

				string option;
				cin >> option;
				while (option != "1" && option != "2") {
					cout << "Bad Input!" << endl;
					cout << "What will you do?" << endl;
					cout << "1) Keep Playing" << endl;
					cout << "2) End Your Turn" << endl;
					cin >> option;
				}
				if (option == "1") {
					continue;
				} else {
					moveOn = true;
					//					cout << "score before updating " << p.getScore() << " and the amount we want to add is " << table.getScore() << endl;
					p.updateScore(table.getScore());
					//					cout << "Player " << p.getID() << "'s score is now " << p.getScore() << endl;
					if (p.getScore() >= endScore) {
						setcolor(255,165,0);
						cout << "Player  " << p.getID() << " wins!!" << endl;
						setcolor(255,255,255);
						wonRound = true;
						p.setMoney(wager);
						//	exit(EXIT_SUCCESS);
					}
					p.resetDie();
					table.cleanTable();
				}
			}

		}

	}

}

