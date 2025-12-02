#include "table.h"
#include <cctype>
#include <sstream>
#include <cmath>
#include "/public/colors.h"
using namespace std;


//int currScore;
//      vector<int> currValues;
//    bool Farkled;
Table:: Table() {
	currScore = 0;
	Farkled = false;
	maxSides = 0;
}

void Table::setFreq() {
	frequency.clear();
	frequency.resize(maxSides);
	for (int i = 0; i < diceValues.size(); i++) {
		//		frequency.at(diceValues.at(i)-1)++;
		frequency.at(diceValues.at(i).get_roll() - 1)++;
	}
}

void Table::rollAllDie(Player& p){
	diceValues.clear(); //Clears the diceValues vector so the player cann keep going with less dice
	int t = 0;
	bool seenGoodDie = false;
	while (!seenGoodDie) {
		for (Die d : p.getDie()) {
			//cerr << "enter loop for " << endl;
		/*	setcolor(255,255,0);	
			if (d.canRoll()) {
				cout << t << " Can roll this die!" << endl;
			} else {
				cout << t << "\t  CANNTTTT roll this die" << endl;
			}
			setcolor(255,255,255);
			t++;*/
			if(d.canRoll()) {
				seenGoodDie = true;
				d.roll();
				//	cerr << "roll good  for " << endl;
				//diceValues.push_back(d.get_roll());
				diceValues.push_back(d);
				if (d.getSides() > maxSides) {
					maxSides = d.getSides();
				}
			}
		}
		if (!seenGoodDie) {
			for (Die& d: p.getDie()) {
				d.setCanRoll(true);
			}
		}
	}
	//	setcolor(255,0,0);
	//	for (Die d : diceValues) {
	//		cerr << d.get_roll() << " " << d.getDieIndex() << endl;;
	//	}
	//cerr << endl;
	//	setcolor(255,255,255);
	//	cerr << "exit loop good " << endl;
	this->setFreq();
	//	cerr << "set freq good" << endl;
}

void Table::printResults(){
	if (!diceValues.size()) return;
	cout << "Dice Rolls: ";
	for (int i = 0; i < diceValues.size(); i++) {
		//cout << diceValues.at(i) << " ";
		cout << diceValues.at(i).get_roll() << " ";
	}
	cout << endl;
}

bool Table::isFarkle(){
	for (int i = 0; i < frequency.size(); i++) {
		if ((i == 0 || i == 4) && frequency.at(i) > 0) return false;
		if (frequency.at(i) >= 3) return false;
	}
	return true;
}
void Table::keepDice(Player& p){
	cout << "Choose which die to keep (input values btwn 0 and " << diceValues.size() - 1 << " with spaces btwn them" << endl;
	string line;
	cin >> ws;
	getline(cin,line);
	stringstream str(line);
	string val;
	vector<int> chosenDies(maxSides);

	while (true) {
		bool badInput = false;
		while (str >> val) {
			bool isNum = true;
			for (char c : val) {
				if (!isdigit(c)) {
					isNum = false;
					break;
				}
			}
			if (isNum && stoi(val) >= 0 && stoi(val) < diceValues.size()) {
				//currScore += diceValues.at(stoi(val));
				//chosenDies.at(diceValues.at(stoi(val)) - 1)++;
				chosenDies.at(diceValues.at(stoi(val)).get_roll() - 1)++;
			} else {
				cout << "bad input was " << val << endl;
				badInput = true;
				cout << "Bad Dice Input! Try again" << endl;
				cin >> ws;
				line = "";
				getline(cin,line);
				str.clear();
				str.str(line);
				badInput = true;
				fill(chosenDies.begin(), chosenDies.end(), 0);

				break;
			}
		}

		for (int i = 0; i < chosenDies.size(); i++) {
			//se0tcolor(0,255,0);
			//cerr << "i is " << i << " and chosendie is " << chosenDies.at(i) << " and frequency is " << frequency.at(i) << endl;
			//setcolor(255,255,255);
			if (chosenDies.at(i) > frequency.at(i)) {
				cout << "Bad Dice Input! Try again" << endl;
				cin >> ws;
				line = "";
				getline(cin,line);
				str.clear();
				str.str(line);
				badInput = true;
				fill(chosenDies.begin(), chosenDies.end(), 0);
				break;
			}
		}
		if (badInput) {
			continue;
		}
		//TODO: if user gets to this point their dice are valid, give them points and put chosen die aside
		if (!isValidCombo(chosenDies)) {
			cout << "Bad Dice Combination! Try Again)" << endl;
			cin >> ws;
			line = "";
			getline(cin,line);
			str.clear();
			str.str(line);
			badInput = true;
			fill(chosenDies.begin(), chosenDies.end(), 0);
		} else {
			for (int i = 0; i < diceValues.size(); i++) {
				//cerr << "gonna check chosenDies(diceValues(i))" << endl;
				//for (int i : chosenDies) {cout << i << " ";} cout << endl;
				//for (int i : diceValues) {cout << i << " ";} cout << endl;

				//if (chosenDies.at(diceValues.at(i) - 1) > 0) {
				if (chosenDies.at(diceValues.at(i).get_roll() - 1) > 0) {
					p.setBadDie(diceValues.at(i).getDieIndex());
					/*setcolor(255,255,0);
					cerr << "Setting bad die for index" << i << endl;
					setcolor(255,255,255);*/
				}


				//cerr << " checked chosenDies(diceValues(i)) successfully" << endl;
			}
			computeScore(chosenDies);
			}

			if (badInput) {
				continue;
			}

			break;
		}
	}
	void Table::computeScore(vector<int> vec) {
		//each position of vec represents the side of the die, and contains how many times the user inputted they want that number.
		int returnScore = 0;
		for (int i = 0; i < vec.size(); i++) {
			int currFreq = vec.at(i); //Frequency User inputted this number
			int currFace = i+1; //Corresponding face since vectors start at 0

			if (currFace == 1) { 
				if (currFreq == 1 || currFreq == 2) { //1 or 2 ones => 100 each
					returnScore += 100 * currFreq;
				}
			} else if (currFace == 5) {
				if (currFreq == 1 || currFreq == 2) { //1 or 2 fives => 50 each
					returnScore += 50 * currFreq;
				}
			}

			if (currFreq >= 3) { //Triples, Quads, Etc
				if (currFace == 1) {
					returnScore += 1000 * pow(2, currFreq - 3); //Starts at 1000 for ones and doubles each time
				} else {
					returnScore += currFace * 100 * pow(2,currFreq - 3); //Starts at face * 100 for others and doubles each time
				}

			}

		}
		currScore += returnScore;	
	}

	bool Table::isValidCombo(vector<int> vec) {
		//each position of vec represents the side of the die, and contains how many times the user inputted they want that number. 
		for (int i = 0; i < vec.size(); i++) {
			int currFreq = vec.at(i); //Frequency User inputted this number
			int currFace = i+1; //Corresponding face since vectors start at 0
			if (currFace == 1 || currFace == 5) { //1s and 5s always good
				continue;
			} 
			if (currFreq == 0) continue; //means user didnt type so its fine
			if (currFreq >= 3) continue; //triples or more are good
			if (currFreq < 3) return false; //means choosing something that only came up once or twice and is NOT 1 or 5, badness
		}
		return true;
	}




	void Table::cleanTable(){
		currScore = 0;
		Farkled = false;
		maxSides = 0;
	}
	int Table::getScore() {
		return currScore;
	}
