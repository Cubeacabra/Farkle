#include "player.h"
using namespace std;

Player::Player() {
	for (int i = 0; i < 6; i++) {
		Die d;
		dice.push_back(d);
	}
	money = 1000;
	score = 0;
}
Player::Player(int newID) {
	playerID = newID;
	for (int i = 0; i < 6; i++) {
		Die d;
		dice.push_back(d);
		dice.at(i).setIndex(i);
	}
	money = 1000;
	score = 0;
}

Player::Player(vector<Die>& newDie, int newId) : dice(newDie), playerID(newId) {
	score = 1000;
	money = 0;
	for (int i = 0; i < dice.size(); i++) {
		dice.at(i).setIndex(i);
	}
}
void Player::initDice(const vector<Die>& newDie){
	dice = newDie;
	for (int i = 0; i < dice.size(); i++) {
		dice.at(i).setIndex(i);
		dice.at(i).printSelf();
	}
}

void Player::updateScore(const int newPoints) {
	score += newPoints;
}

int Player::getScore() const {
	return score;
}
int Player::getID() const {
	return playerID;
}

vector<Die>& Player::getDie() {
	return dice;
}
void Player::setBadDie(int index) {
	dice.at(index).setCanRoll(false);
}
void Player::resetDie() {
	for (Die& d : dice) {
		d.setCanRoll(true);
	}
}

void Player::winMoney(int newMoney) {
	money += newMoney;
}
void Player::loseMoney(int lostMoney) {
	money -= lostMoney;
}


int Player::getMoney() {
	return money;
}
void Player::resetScore() {
	score = 0;
}
