#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <random>
#include <ctime>
using namespace std;

mt19937 random_mt;
//Initialize maps and iterators for global use
map<int, int> dicemap;
map<int, int>::iterator iter;

map<string, vector<int>> statemap;
map<string, vector<int>>::iterator it;

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void RollDice(int numberOfRolls, int numberOfSides) {

	for (int i = 1; i <= numberOfSides; i++) {
		dicemap[i] = 0;
	}

	for (int i = 0; i < numberOfRolls; i++) {
		int randint = Random(1, numberOfSides);
		dicemap[randint] += 1;
	}
}

void LoadStates(string line) {

	int count = 0;
	int numlength;
	string name;
	vector<int> statedata;
	//Florida,26582,19893297,47463,7328046

	while (count < 5) {
		//cout << "\nLine: " << line << endl;

		for (unsigned int i = 0; i < line.length(); i++) {
			//cout << line.at(i) << " ";

			if (line.at(i) == ',') {
				if (count == 0) {
					name = line.substr(0, i);
					//cout << "Name: " << name << endl;

				}
				else {
					//cout << "Adding: " << line.substr(numlength,i-numlength) << endl;
					statedata.push_back(stoi(line.substr(numlength, i - numlength)));

				}
				numlength = i + 1;
				count++;
			}

			if (name == "State") {
				break;
			}
		}

		if (name == "State") {
			break;
		}
	}

	statemap[name] = statedata;
}

void DisplayState(vector<int> data) {
	cout << "Population: " << data[1] << endl;
	cout << "Per Capita Income: " << data[0] << endl;
	cout << "Median Household Income: " << data[2] << endl;
	cout << "Number of Households: " << data[3] << endl;
}

int main()
{
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);

		cout << "Number of times to roll the die: ";
		// user input
		int numberOfRolls;
		cin >> numberOfRolls;
		cout << endl;

		cout << "Number of sides on this die: ";
		// user input
		int numberOfSides;
		cin >> numberOfSides;
		cout << endl;

		// Roll Dice
		RollDice(numberOfRolls, numberOfSides);
		for (iter = dicemap.begin(); iter != dicemap.end(); iter++) {
			cout << iter->first << ": " << iter->second << endl;
		}
	}

	else if (option == 2)
	{
		// Load the states
		ifstream statesdata;
		statesdata.open("states.csv");

		if (option == 2) {
			string line;
			getline(statesdata, line);

			while (getline(statesdata, line)) {

				LoadStates(line);

			}
		}

		// Get input for option 1 (show all states) or 2 (do a search for a particular state)
		cout << "1. Print all states" << endl << "2. Search for a state" << endl;
		cin >> option;

		if (option == 1) {
			for (it = statemap.begin(); it != statemap.end(); it++) {
				cout << it->first << endl;
				DisplayState(it->second);
			}
		}

		else if (option == 2) {
			string search;
			cin >> search;
			it = statemap.find(search);
			if (it != statemap.end()) {
				cout << it->first << endl;
				DisplayState(it->second);
			}
			else {
				cout << "No match found for " << search << endl;
			}
		}
	}

	return 0;
}

