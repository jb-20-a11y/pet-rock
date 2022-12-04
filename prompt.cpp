#include "prompt.h"
#include <random>
using namespace std;

size_t promptForOptions(const string &prompt, const vector<string> &options) {
	size_t input;
	cout << prompt << endl;
	for (size_t j=0; j<options.size(); ++j) {
		cout << to_string(j+1) << ": " << options[j] << endl;
	}
	cout << ">";
	cin >> input;
	if (input<1 || input>options.size()) {
	return 0;
	}
	return input;
}

int getRandom(int a, int b) {
	random_device rd;
	uniform_int_distribution<int> rn(a,b);
	return rn(rd);
} 
