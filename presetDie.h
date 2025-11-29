#pragma once
#include <iostream>
#include "player.h"

class presetDie {
	private:
		vector<Die> allDie;	
	public:
		presetDie();
		void printAll();
		Die getDie(int index);

};
