#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
using namespace std;
class Color
{
private:
	string name;
	string hexvalue;
	unsigned int r;
	unsigned int b;
	unsigned int g;
	
public:
	string uIntToHex(unsigned int num) {
		string alpha = "0123456789ABCDEF";

		unsigned int temp = num / 16;

		string first = "0";
		for (unsigned int i = 0; i < alpha.size(); i++) {
			if (temp == i) {
				first = alpha[i];
			}
		}

		unsigned int temp1 = num % 16;
		string second = "0";
		for (unsigned int i = 0; i < alpha.size(); i++) {
			if (temp1 == i) {
				second = alpha[i];
			}
		}

		string hex = first + second;
		return hex;
	}
	//Given an integer value, convert it to RGB and Hex values
	void SetValue(int value) {
		short num = value & 255;
		b = num;
		num = value>>8 & 255;
		g = num;
		num = value>>16 & 255;
		r = num;
		/*
		cout << r << " Red" << endl;
		cout << b << " Blue" << endl;
		cout << g << " Green" << endl;
		*/
		string rhex = uIntToHex(r);
		string ghex = uIntToHex(b);
		string bhex = uIntToHex(g);

		hexvalue = "0x" + rhex + bhex + ghex;

	}
	void SetName(const char* name) {
		this->name = name;
	}

	//Accessors
	unsigned char GetR() const {
		return r;
	}
	unsigned char GetG() const {
		return g;
	}
	unsigned char GetB() const {
		return b;
	}
	string GetHexValue() const {
		return hexvalue;
	}
	string GetName() const {
		return name;
	}
};