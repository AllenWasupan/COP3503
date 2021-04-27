#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

	/* Load files here */
	
	
	ifstream file1("friendlyships.shp", ios_base::binary);
	ifstream file2("enemyships.shp", ios_base::binary);

	ifstream* file;

	if (option == 1) {
		file = &file1;
	}
	else if (option == 2) {
		file = &file2;
	}
	else if (option == 3) {
		file = &file1;
	}

	vector<string> namev;
	vector<string> clas;
	vector<short> length;
	vector<int> shield;
	vector<float> maxwarp;
	vector<float> wepnums;
	vector<string> wpns;
	vector<int> power;
	vector<float> cost;
	vector<int> fp;

	int count;
	file->read((char*)&count, sizeof(count));

	for (int i = 0; i < count; i++) {
		//Length of name
		int len;
		file->read((char*)&len, sizeof(len));
		//1 Name
		char* buffer = new char[len];
		file->read(buffer, len);
		string name = buffer;
		delete[] buffer;
		namev.push_back(name);

		//Length of ship's class
		int lenc;
		file->read((char*)&lenc, sizeof(lenc));
		//2 Class Name
		buffer = new char[lenc];
		file->read(buffer, lenc);
		string namec = buffer;
		delete[] buffer;
		clas.push_back(namec);

		//3 Ship's length in meters
		short shiplen;
		file->read((char*)&shiplen, 2);
		length.push_back(shiplen);

		//4 Ship's shield capacity in terajoules
		int shieldstr;
		file->read((char*)&shieldstr, sizeof(shieldstr));
		shield.push_back(shieldstr);

		//5 Ship's warp speed
		float warpspd;
		file->read((char*)&warpspd, sizeof(warpspd));
		maxwarp.push_back(warpspd);

		//Number of weapons
		int numwep;
		file->read((char*)&numwep, sizeof(numwep));
		wepnums.push_back(numwep);

		int firepower = 0;
		for (int i = 0; i < numwep; i++) {
			//Weapon's name length
			int lenname;
			file->read((char*)&lenname, sizeof(lenname));
			//6 Weapons name
			buffer = new char[lenname];
			file->read(buffer, lenname);
			string namec = buffer;
			delete[] buffer;
			wpns.push_back(namec);

			//7 Power rating of weapon
			int weppwr;
			file->read((char*)&weppwr, sizeof(weppwr));
			power.push_back(weppwr);
			firepower += weppwr;

			//8 Weapon power consumption
			float wepcons;
			file->read((char*)&wepcons, sizeof(wepcons));
			cost.push_back(wepcons);

		}
		fp.push_back(firepower);
	}

	if (option == 3) {
		cout << "adding list 2" << endl;
		file = nullptr;
		file = &file2;
		int scount;

		file->read((char*)&scount, sizeof(scount));

		for (int i = 0; i < scount; i++) {
			//Length of name
			int len;
			file->read((char*)&len, sizeof(len));
			//1 Name
			char* buffer = new char[len];
			file->read(buffer, len);
			string name = buffer;
			delete[] buffer;
			namev.push_back(name);

			//Length of ship's class
			int lenc;
			file->read((char*)&lenc, sizeof(lenc));
			//2 Class Name
			buffer = new char[lenc];
			file->read(buffer, lenc);
			string namec = buffer;
			delete[] buffer;
			clas.push_back(namec);

			//3 Ship's length in meters
			short shiplen;
			file->read((char*)&shiplen, 2);
			length.push_back(shiplen);

			//4 Ship's shield capacity in terajoules
			int shieldstr;
			file->read((char*)&shieldstr, sizeof(shieldstr));
			shield.push_back(shieldstr);

			//5 Ship's warp speed
			float warpspd;
			file->read((char*)&warpspd, sizeof(warpspd));
			maxwarp.push_back(warpspd);

			//Number of weapons
			int numwep;
			file->read((char*)&numwep, sizeof(numwep));
			wepnums.push_back(numwep);

			int firepower = 0;
			for (int i = 0; i < numwep; i++) {
				//Weapon's name length
				int lenname;
				file->read((char*)&lenname, sizeof(lenname));
				//6 Weapons name
				buffer = new char[lenname];
				file->read(buffer, lenname);
				string namec = buffer;
				delete[] buffer;
				wpns.push_back(namec);

				//7 Power rating of weapon
				int weppwr;
				file->read((char*)&weppwr, sizeof(weppwr));
				power.push_back(weppwr);
				firepower += weppwr;

				//8 Weapon power consumption
				float wepcons;
				file->read((char*)&wepcons, sizeof(wepcons));
				cost.push_back(wepcons);

			}
			fp.push_back(firepower);
			cout << name << endl;
		}
		count += scount;

	}

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;

	cin >> option;

	/* Work your magic here */
	if (option == 1) {
		int wpncnt = 0;
		for (int i = 0; i < count; i++) {
			cout << "Name: " << namev[i] << endl;
			cout << "Class: " << clas[i] << endl;
			cout << "Length: " << length[i] << endl;
			cout << "Shield capacity: " << shield[i] << endl;
			cout << "Maximum Warp: " << maxwarp[i] << endl;
			cout << "Armaments: " << endl;

			if (wepnums[i] > 0) {
				for (int j = 0; j < wepnums[i]; j++) {
					cout << wpns[j+wpncnt] << ", ";
					cout << power[j+wpncnt] << ", ";
					cout << cost[j+wpncnt] << endl;
				}
				cout << "Total firepower: " << fp[i] << endl << endl;
				wpncnt += wepnums[i];
			}
			else {
				cout << "Unarmed" << endl << endl;
			}
		}
	}
	else if (option == 2) {

		int strong = 0;
		for (int i = 0; i < count; i++) {
			if (power[strong] < power[i]) {
				strong = i;
			}
		}

		//cout << wpns[strong] << " " << power[strong] << " " << cost[strong] << endl;
		int c = strong;
		int wpncnt = 0;
		for (int i = 0; i < count; i++) {
			cout << c << endl;
			cout << wepnums[i] << endl;
			if (c > wepnums[i]) {
				c -= i;
				wpncnt += wepnums[i];
			}
			else {
				cout << "Name: " << namev[i] << endl;
				cout << "Class: " << clas[i] << endl;
				cout << "Length: " << length[i] << endl;
				cout << "Shield capacity: " << shield[i] << endl;
				cout << "Maximum Warp: " << maxwarp[i] << endl;
				cout << "Armaments: " << endl;
				if (wepnums[i] > 0) {
					for (int j = 0; j < wepnums[i]; j++) {
						cout << wpns[j+wpncnt] << ", ";
						cout << power[j+wpncnt] << ", ";
						cout << cost[j+wpncnt] << endl;
					}
					cout << "Total firepower: " << fp[i] << endl;
				}
				else {
					cout << "Unarmed" << endl;
				}

				break;
			}
		}

	}
	else if (option == 3) {

		int strong = 0;
		int wpncnt = 0;
		for (int i = 0; i < count; i++) {
			//cout << fp[strong] << " " << fp[i] << endl;
			if (fp[strong] < fp[i]) {
				cout << fp[strong] << " " << fp[i] << endl;
				strong = i;
			}
		}
		cout << "Name: " << namev[strong] << endl;
		cout << "Class: " << clas[strong] << endl;
		cout << "Length: " << length[strong] << endl;
		cout << "Shield capacity: " << shield[strong] << endl;
		cout << "Maximum Warp: " << maxwarp[strong] << endl;
		cout << "Armaments: " << endl;

		if (wepnums[strong] > 0) {
			for (int i = 0; i < strong; i++) {
				wpncnt += wepnums[i];
			}
			for (int j = 0; j < wepnums[strong]; j++) {
				cout << wpns[j + wpncnt] << ", ";
				cout << power[j + wpncnt] << ", ";
				cout << cost[j + wpncnt] << endl;
			}
			cout << "Total firepower: " << fp[strong] << endl;
		}
		else {
			cout << "Unarmed" << endl;
		}
		

	}
	else if (option == 4) {
		int weak = 0;
		int wpncnt = 0;
		for (int i = 0; i < count; i++) {
			//cout << fp[weak] << " " << fp[i] << endl;
			if (fp[i] == 0) {
				continue;
			}
			if (fp[weak] > fp[i]) {
				cout << fp[weak] << " " << fp[i] << endl;
				weak = i;
			}
		}
		cout << "Name: " << namev[weak] << endl;
		cout << "Class: " << clas[weak] << endl;
		cout << "Length: " << length[weak] << endl;
		cout << "Shield capacity: " << shield[weak] << endl;
		cout << "Maximum Warp: " << maxwarp[weak] << endl;
		cout << "Armaments: " << endl;

		if (wepnums[weak] > 0) {
			for (int i = 0; i < weak; i++) {
				wpncnt += wepnums[i];
			}
			for (int j = 0; j < wepnums[weak]; j++) {
				cout << wpns[j + wpncnt] << ", ";
				cout << power[j + wpncnt] << ", ";
				cout << cost[j + wpncnt] << endl;
			}
			cout << "Total firepower: " << fp[weak] << endl;
		}
		else {
			cout << "Unarmed" << endl;
		}
	}
	else if (option == 5) {
		for (int i = 0; i < count; i++) {
			if (fp[i] == 0) {
				cout << "Name: " << namev[i] << endl;
				cout << "Class: " << clas[i] << endl;
				cout << "Length: " << length[i] << endl;
				cout << "Shield capacity: " << shield[i] << endl;
				cout << "Maximum Warp: " << maxwarp[i] << endl;
				cout << "Armaments: " << endl;
				cout << "Unarmed" << endl << endl;
			}
		}
	}

	return 0;
}