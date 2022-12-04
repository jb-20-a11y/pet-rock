#include "character.h"
using namespace std;

character::character() {
	name="Default";
	description="Default";
}

character::character(const string &nName, const string &nDescription) {
	name=nName;
	description=nDescription;
}

string character::describe() {
	return name+" "+description+" It has a total health of "+to_string(totalHealth)+" and can do up to "+to_string(2*damage+1)+" damage.";
}

