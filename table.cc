#include "table.h"
#include <cctype>
#include <sstream>
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
	//cerr << "enter freq good" << endl;
	frequency.clear();
	frequency.resize(maxSides);
	//cerr << "resize good" << endl;
	for (int i = 0; i < diceValues.size(); i++) {
		//	cerr << "in loop for = " << i << endl;
		frequency.at(diceValues.at(i)-1)++;
		//	cerr << "changed freq for i= " << i << endl;
	}
	//	for (int i = 0; i < frequency.size(); i++) {
	//		cout << "i is: " << i << " and freq is " << frequency.at(i) << endl;
	//	}
}

void Table::rollAllDie(Player& p){
	//cerr << "enter good" << endl;
	diceValues.clear(); //Clears the diceValues vector so the player cann keep going with less dice
						//cerr << "clear good" << endl;
	for (Die d : p.getDie()) {
		//	cerr << "enter loop for " << endl;
		if(d.canRoll()) {
			d.roll();
			//	cerr << "roll good  for " << endl;
			diceValues.push_back(d.get_roll());
			if (d.getSides() > maxSides) {
				maxSides = d.getSides();
			}
		}
	}
	//	cerr << "exit loop good " << endl;
	this->setFreq();
	//	cerr << "set freq good" << endl;
}

void Table::printResults(){
	if (!diceValues.size()) return;
	cout << "Dice Rolls: ";
	for (int i = 0; i < diceValues.size(); i++) {
		cout << diceValues.at(i) << " ";
	}
	cout << endl;
}

bool Table::isFarkle(){
	return Farkled;
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
				//p.setBadDie(stoi(val));
				chosenDies.at(diceValues.at(stoi(val)) - 1)++;
			} else {
				badInput = true;
				break;
			}
		}

		for (int i = 0; i < chosenDies.size(); i++) {
			cerr << "i is " << i << " and chosendie is " << chosenDies.at(i) << " and frequency is " << frequency.at(i) << endl;
			if (chosenDies.at(i) > frequency.at(i)) {
				cout << "Bad Dice Input! Try again" << endl;
				cin >> ws;
				line = "";
				getline(cin,line);
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
		break;
	}
}
void Table::cleanTable(){}
int Table::getScore() {
	return currScore;
}
