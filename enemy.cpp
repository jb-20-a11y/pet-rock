#include "enemy.h"
#include <string>
#include <chrono>
#include "prompt.h"
using namespace std;
 
enemy::enemy(const string & nName, const string & nDescription) : character(nName, nDescription)
{
}

void enemy::fight(character *other) {
	int rDamage = ((int) (damage/2)) + getRandom(-1*(((int) (damage/2))),damage+1);
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
		cout << "You die!" << endl;
	}
}

bool enemy::isAlive() {
	return currentHealth>0;
}

void enemy::setStats(int level) {
	srand(time(nullptr));
	int baseStat = 2 * level;
	int x = 3;
	damage = level;
	if (damage<1) damage=1;
	currentHealth = totalHealth = 2 * level + 2;
}