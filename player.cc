#include "player.h"
using namespace std;

Player::Player() {
	for (int i = 0; i < 6; i++) {
		Die d;
		dice.push_back(d);
	}
	score = 0;
}

Player::Player(vector<Die>& newDie, int newId) : dice(newDie), playerID(newId) {
	score = 0;
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
