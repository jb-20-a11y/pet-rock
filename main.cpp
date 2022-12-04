#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include "prompt.h"
#include "player.h"
#include "enemy.h"
using namespace std;

class encounterableEnemy {
public:
	string name;
	string description;
	int level;
	encounterableEnemy(){}
	encounterableEnemy(const string &nName, const string &nDescription, const int &nLevel) {
		name=nName;
		description=nDescription;
		level=nLevel;
	}
};

vector<encounterableEnemy> enemies;
vector<encounterableEnemy> ultimateEnemy;
int enemyIndex = 0;
bool lastEnemyAlive = false;
int globalHealth = 0;

const string intro =
"          _____          \n      __ /__    \\__     \n   _ /      \\    __\\   \n  /          \\__ /  \\  \n |   O          O    |    \n |      ______      /    \n  \\     \\____/     /   \n   \\______________/     \n  PET ROCK ADVENTURE - UNIVERSE/SPACE VERSION!";

void delayScroll(int delayMS, int lineCount) {
	for (int i=0; i<lineCount; ++i) {
		cout << "" << endl;
		this_thread::sleep_for(chrono::milliseconds(delayMS));
	}
}


character* setupRock() {
	string name;
	cout << "What is your rock's name?" << endl;
	while (name=="") getline(cin,name);
	character *rock = new player(name,"just a regular rock");
	return rock;
}

character *generateEnemy(encounterableEnemy *pTemplate) {
	character *umbrella = new enemy(pTemplate->name,pTemplate->description);
	umbrella->setStats(pTemplate->level);
	return umbrella;
}

character *getEnemy(int i) {
	if (i<enemies.size()) {
		return generateEnemy(&enemies[i]);
	}
	else {
		if (globalHealth<=10) {
			return generateEnemy(&enemies[getRandom(0,enemies.size()-1)]);
		}
		else {
			return generateEnemy(&ultimateEnemy[0]);
		}
	}
}

void encounterEnemy(character *pPlayer, character *pEnemy);

void fightDecisions(character *pPlayer) {
	globalHealth=pPlayer->currentHealth;
	if (pPlayer->isAlive())
	{
		character *pEnemy = getEnemy(enemyIndex);
		enemyIndex++;
		vector<string> options;
		pPlayer->allPointers.push_back(pEnemy);
		options.push_back("Encounter");
		options.push_back("Run");
		size_t option = promptForOptions("You encounter " + pEnemy->name + ".\n" + pEnemy->describe(), options);
		if (option == 1)
		{
			encounterEnemy(pPlayer, pEnemy);
		}
		else
		{
			cout << "Game over! There is no place you can run in order to escape." << endl;
			cout << "Number of battles you participated in: " << (enemyIndex-1) << endl;
		}
	}
	else 
	{
		if (lastEnemyAlive) {
			cout << "Game over! You lose!" << endl;
		}
		else {
			cout << "Game over! It's a draw!" << endl;
		}
		cout << "Number of battles you participated in: " << enemyIndex << endl;
	}
}

void encounterEnemy(character *pPlayer, character *pEnemy) {
	while (pPlayer->isAlive() && pEnemy->isAlive()) {
		pPlayer->fight(pEnemy);
		pEnemy->fight(pPlayer);

		delayScroll(10, 1);
	}
	lastEnemyAlive=pEnemy->isAlive();
	fightDecisions(pPlayer);
}

int main() {
	srand(time(nullptr));
	encounterableEnemy uv("Ultraviolet","is part of the EMS and can give you skin cancer.",1);
	encounterableEnemy gamma("Gamma","is the highest energy part of the EMS and can penetrate a lot more than UV!",2);
	encounterableEnemy blackHole("Black hole","is something you simply can't escape!",3);
	encounterableEnemy ice("Freezing cold asteroid","is easy to defeat when you have full health, but not when you don't. Or maybe there's a strategy you can employ to extend this game?",1);
	encounterableEnemy jupiter("Jupiter","has a much more intense gravitational force than Earth.",2);
	encounterableEnemy cake("Chocolate cake","is what you get in order to punish you for your double-digit health.",3);
	enemies.push_back(uv);
	enemies.push_back(gamma);
	enemies.push_back(blackHole);
	enemies.push_back(ice);
	enemies.push_back(jupiter);
	ultimateEnemy.push_back(cake);
	cout << intro << endl;
	cout << "Rules:" << endl;
	cout << "1. Your imaginary rock starts with 18 health." << endl;
	cout << "2. Several enemy characters will battle your rock, with a new enemy encountered every time the rock (hopefully) wins each successive battle." << endl;
	cout << "3. One attack is an instantaneous match in which the two characters shoot each other and can inflict an arbitrary amount of damage." << endl;
	cout << "4. You can choose at any time to restock your rock's health (randomly determined from [0, 3]), and in that match, only the attacker would have the ability to shoot while you reload." << endl;
	cout << "5. If you run, you surrender." << endl;
	cout << "6. The object of the game is to stay alive as long as you can." << endl;
	character *petRock = setupRock();
	cout << "Let's begin the adventure!" << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	delayScroll(10,30);
	petRock->setStats(3);
	fightDecisions(petRock);
	if (petRock->allPointers.size()>0) {
		for (size_t i=0; i<petRock->allPointers.size(); ++i) {
			delete petRock->allPointers[i];
		}
	}
	delete petRock;
	return 0;
}
