#pragma once
#include "prompt.h"
using namespace std;

class character {
	public:
		string name;
		string description;
		int damage;
		int totalHealth;
		int currentHealth;
		vector<character*> allPointers;
		character();
		character(const string &nName, const string &nDescription);
		string describe();
		virtual void fight(character *other) =0;
		virtual bool isAlive() =0;
		virtual void setStats(int level) =0;
};

 
