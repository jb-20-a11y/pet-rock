#pragma once
#include "character.h"
#include <string>


using namespace std;

class enemy:public character {
	public:

		enemy(const string &nName, const string &nDescription);
		void fight(character *other);
		bool isAlive();
		void setStats(int level);
};
