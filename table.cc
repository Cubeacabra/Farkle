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
}

void Table::rollAllDie(Player& p){
	diceValues.clear(); //Clears the diceValues vector so the player cann keep going with less dice
	for (Die d : p.getDie()) {
		if(d.canRoll()) {
			d.roll();
			diceValues.push_back(d.get_roll());
		}
	}
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
	cout << "Choose which die to keep (input values btwn 0 and " << diceValues.size() << " with spaces btwn them" << endl;
	string line;
	getline(cin,line);

	stringstream str(line);
	string val;
	while (str >> val) {
	bool isNum = true;
		for (char c : val) {
			if (!isdigit(c)) {
				isNum = false;
				break;
			}
		}

		if (isNum && stoi(val) >= 0 && stoi(val) < diceValues.size()) {
			currScore += diceValues.at(stoi(val));
			p.setBadDie(stoi(val));

		}
	}
}
void Table::cleanTable(){}
