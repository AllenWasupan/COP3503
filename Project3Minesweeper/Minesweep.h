#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>

using namespace std;
using namespace sf;


class Tile {
	struct Neighbor {
		bool isbomb;
	};

private:
	bool revealed;
	bool isbomb;
	vector<Neighbor> neighborvector;
};
class Game {

private:
	int width, height, minecount, tilecount, row, column;

	Tile tile;
	vector<Tile> tilevec;
	RenderWindow window;
	
	String filenamee;
public:
	//Default Constructor, takes in the file name for the board info
	Game(string input) {

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
		
		
		window.setTitle("Minesweeper");
		window.setSize(Vector2u(width, height));
		
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
	bool isBorder(Tile tile) {

	}
};