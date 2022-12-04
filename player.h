#pragma once
#include "character.h"
using namespace std;

class player:public character {
	public:
		player(const string &nName, const string &nDescription);
		void fight(character *other);
		bool isAlive();
		void setStats(int level);
};
