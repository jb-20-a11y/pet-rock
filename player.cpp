#include "player.h"
#include "prompt.h"
#include <random>
using namespace std;
 
player::player(const string &nName, const string &nDescription) : character(nName, nDescription)
{
}

void player::fight(character *other) {
	vector<string> options;
	options.push_back("Attack");
	options.push_back("Restock my health");
	int option = promptForOptions("Select what to do",options);
	if (option==1) {

		int rDamage = damage + getRandom(-3,3);
		if (rDamage<=0) {
			cout << name << " misses. Not even close!" << endl;
		}
		else {
			other->currentHealth-=rDamage;
			cout << name << " hits " << other->name << " for " << rDamage << " damage!" << endl;
		}
		if (other->currentHealth>0) {
			cout << other->name << " is at " << other->currentHealth << "/" << other->totalHealth << " health." << endl;
		}
		else {
			cout << other->name << " dies." << endl;
		}
	}
	else if (option==2) {
		int oldHealth = currentHealth;
		int moreHealth = getRandom(1,3);
		currentHealth=currentHealth+moreHealth;
		if (currentHealth>totalHealth) currentHealth=totalHealth;
		cout << name << " gains " << (currentHealth-oldHealth) << " health." << endl;
		cout << name << " is at " << currentHealth << "/" << totalHealth << " health." << endl;
	}
}

bool player::isAlive() {
	return currentHealth>0;
}

void player::setStats(int level) {
	int baseStat = 2 * level;
	int x = 6;
	damage = 3;
	currentHealth = totalHealth = 3 * x;
}