#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>

using namespace std;
using namespace sf;


struct Tile {
public:

	bool revealed = false;
	bool isbomb = false;
	bool top = true;
	bool left = true;
	bool right = true;
	bool down = true;
	bool flag = false;
	bool flock = false;
	int num = 0;

};

class Game {

private:
	int width, height, minecount = 0, tilecount, row, column;
	RenderWindow window;
	String filenamee;
public:
	Tile tile;
	vector<Tile> tilevec;
	//Default Constructor, takes in the file name for the board info
	Game(string input) {
		setBoard(input);
		
	}

	void setTiles() {
		tilevec.clear();
		//Sets tiles
		for (int i = 0; i < gettilecount(); i++) {
			Tile tile;
			tile.revealed = false;
			tile.isbomb = false;
			//Determines if the sides exist
			if (i < column) {
				tile.top = false;
			}
			if (i % column == 0) {
				tile.left = false;
			}
			if (i > ((column * row) - column - 1)) {
				tile.down = false;
			}
			if ((i + 1) % column == 0) {
				tile.right = false;
			}
			tilevec.push_back(tile);
		}
	}

	void setNums() {
		//Sets up num
		for (int i = 0; i < gettilecount(); i++) {
			//cout << i << endl;
			//Top
			if (tilevec[i].top) {
				if (tilevec[i - column].isbomb) {
					tilevec[i].num++;
				}
			}
			//Left
			if (tilevec[i].left) {
				if (tilevec[i - 1].isbomb) {
					tilevec[i].num++;
				}
			}
			//Right
			if (tilevec[i].right) {
				if (tilevec[i + 1].isbomb) {
					tilevec[i].num++;
				}
			}
			//Down
			if (tilevec[i].down) {
				if (tilevec[i + column].isbomb) {
					tilevec[i].num++;
				}
			}
			//Topleft
			if (tilevec[i].top && tilevec[i].left) {
				if (tilevec[i - column - 1].isbomb) {
					tilevec[i].num++;
				}
			}
			
			//Topright
			if (tilevec[i].top && tilevec[i].right) {
				if (tilevec[i - column + 1].isbomb) {
					tilevec[i].num++;
				}
			}
			
			//Downleft
			if (tilevec[i].down && tilevec[i].left) {
				if (tilevec[i + column - 1].isbomb) {
					tilevec[i].num++;
				}
			}
			//Downright
			if (tilevec[i].down && tilevec[i].right) {
				if (tilevec[i + column + 1].isbomb) {
					tilevec[i].num++;
				}
			}
		}
	}

	void setMines(vector<int> mines, bool board) {
		int count = 0;
		cout << "Adding mines!" << endl;
		cout << mines.size() << endl;
		if (board) {			
			while (count < minecount) {
				for (unsigned int i = 0; i < mines.size(); i++) {
					if (mines[i] == 1) {
						tilevec[i].isbomb = true;
						count++;
						cout << "Placing a mine: " << count << endl;
					}
				}
			}
		}

		else {
			//Sets mines for cfg
			while (count < mines.size()) {

				for (int i = 0; i < gettilecount(); i++) {
					//cout << count << endl;
					if (mines[count] == i) {
						tilevec[i].isbomb = true;
						count++;
						break;
					}
				}
			}
		}

		cout << "Mines placed!" << endl;
	}

	void setBoard(string input) {

		ifstream file(input);
		string line;
		vector<int> holder;

		getline(file, line);
		column = stoi(line);

		getline(file, line);
		row = stoi(line);

		getline(file, line);
		minecount = stoi(line);

		tilecount = column * row;
		width = column * 32;
		height = row * 32 + 88;
		setTiles();

		vector<int> minelocations;
		//Loop to set bombs and then loop to sort
		int count = 0;
		bool same = false;

		for (unsigned int i = 0; i < minecount; i++) {
			int minespot = rand() % gettilecount();
			while (count < minelocations.size()) {
				if (minespot == minelocations[count]) {
					minespot = rand() % gettilecount();
					count = 0;
				}
				count++;
			}
			count = 0;
			minelocations.push_back(minespot);
			sort(minelocations.begin(), minelocations.end());
		}

		setMines(minelocations, false);

		setNums();
		
	}

	void setTest(string input) {
		setTiles();

		ifstream file(input, ifstream::binary);
		string m;
		vector<int> boardmine;
		minecount = 0;

		while (getline(file, m)) {
		
			for (unsigned int i = 0; i < m.size(); i++) {
				if (m[i] == '1') {
					boardmine.push_back(1);
					minecount += 1;
				}
				else if (m[i] == '0') {
					boardmine.push_back(0);
				}
				
				
			}
		}
		for (unsigned int i = 0; i < boardmine.size(); i++) {
			if (i % column == 0) {
				cout << endl;
			}
			cout << boardmine[i];
			
		}
		cout << "Minecount: " << minecount << endl;

		setMines(boardmine, true);

		setNums();
	}

	void recursiveclick(int tileselected) {
		if (tilevec[tileselected].num == 0) {
			//Top
			if (tilevec[tileselected].top) {
				if (tilevec[tileselected - column].revealed == false) {
					tilevec[tileselected - column].revealed = true;
					if (tilevec[tileselected - column].num == 0) {
						recursiveclick(tileselected - column);
					}
				}
			}
			//Left
			if (tilevec[tileselected].left) {
				if (tilevec[tileselected - 1].revealed == false) {
					tilevec[tileselected - 1].revealed = true;
					if (tilevec[tileselected - 1].num == 0) {
						recursiveclick(tileselected - 1);
					}
				}
			}
			//Right
			if (tilevec[tileselected].right) {
				if (tilevec[tileselected + 1].revealed == false) {
					tilevec[tileselected + 1].revealed = true;
					if (tilevec[tileselected + 1].num == 0) {
						recursiveclick(tileselected + 1);
					}
				}
			}
			//Down
			if (tilevec[tileselected].down) {
				if (tilevec[tileselected + column].revealed == false) {
					tilevec[tileselected + column].revealed = true;
					if (tilevec[tileselected + column].num == 0) {
						recursiveclick(tileselected + column);
					}
				}
			}
			//Topleft
			if (tilevec[tileselected].top && tilevec[tileselected].left) {
				if (tilevec[tileselected - column - 1].revealed == false) {
					tilevec[tileselected - column - 1].revealed = true;
					if (tilevec[tileselected - column - 1].num == 0) {
						recursiveclick(tileselected - column - 1);
					}
				}
			}
			//Topright
			if (tilevec[tileselected].top && tilevec[tileselected].right) {
				if (tilevec[tileselected - column + 1].revealed == false) {
					tilevec[tileselected - column + 1].revealed = true;
					if (tilevec[tileselected - column + 1].num == 0) {
						recursiveclick(tileselected - column + 1);
					}
				}
			}
			//Downleft
			if (tilevec[tileselected].down && tilevec[tileselected].left) {
				if (tilevec[tileselected + column - 1].revealed == false) {
					tilevec[tileselected + column - 1].revealed = true;
					if (tilevec[tileselected + column - 1].num == 0) {
						recursiveclick(tileselected + column - 1);
					}
				}
			}
			//Downright
			if (tilevec[tileselected].down && tilevec[tileselected].right) {
				if (tilevec[tileselected + column + 1].revealed == false) {
					tilevec[tileselected + column + 1].revealed = true;
					if (tilevec[tileselected + column + 1].num == 0) {
						recursiveclick(tileselected + column + 1);
					}
				}
			}
		}
	}



	Tile getTile() {
		return tile;
	}
	vector<Tile> getTileVector() {
		return tilevec;
	}
	int getwidth() {
		return width;
	}
	int getheight() {
		return height;
	}
	int getminecount() {
		return minecount;
	}
	int gettilecount() {
		return tilecount;
	}
	int getRow() {
		return row;
	}
	int getColumn() {
		return column;
	}
	
};