#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{

    /* Type code here. */
    cout << "Enter a title for the data:" << endl;
    string title;
    getline(cin, title);
    cout << "You entered: " << title << endl;

    cout << "Enter the column 1 header:" << endl;
    string col1;
    getline(cin, col1);
    cout << "You entered: " << col1 << endl;

    cout << "Enter the column 2 header:" << endl;
    string col2;
    getline(cin, col2);
    cout << "You entered: " << col2 << endl;


    string input;
    int num;
    string name;
    vector<int> vecnum;
    vector<string> vecname;
    //The do while loop 
    do {
        cout << "Enter a data point (-1 to stop input):" << endl;
        getline(cin, input);

        //loop doesn't work so i added a if statement
        if (input == "-1") {
            break;
        }

        int leg = input.length();

        for (int i = 0; i < leg; i++) {
            //Does try loop if there's at least one comma
            if (input.at(i) == ',') {
                //Substring for before and after comma, and sets the name
                string strnum = input.substr(i + 1, input.length());
                int strnumlen = strnum.length();
                name = input.substr(0, i);
                //Tries to do the stoi, but also sees errors
                try {
                    int comma = 0;
                    for (int i = 0; i < strnumlen; i++) {
                        if (strnum.at(i) == ',') {
                            comma = comma + 1;
                        }
                    }
                    //Error if more than 1 comma
                    if (comma > 0) {
                        cout << "Error: Too many commas in input." << endl;
                        break;
                    }
                    //Tries to convert the substring into a number
                    num = stoi(strnum);

                    cout << "Data string: " << name << endl;
                    vecname.push_back(name);
                    cout << "Data integer: " << num << endl;
                    vecnum.push_back(num);
                    break;
                }
                //Catch all if the statement can't turn into an integer
                catch (...) {
                    cout << "Error: Comma not followed by an integer." << endl;
                    break;
                }
            }
            else if (i == leg - 1) {
                cout << "Error: No comma in string." << endl;
            }
        }
    } while (input != "-1");

    cout << endl;
    //Table 1
    //Does Title
    cout << right << setw(33) << title << endl;
    //Does headers
    cout << left << setw(20) << col1;
    cout << "|";
    cout << right << setw(23) << col2 << endl;
    cout << "--------------------------------------------" << endl;
    int veclen = vecnum.size();
    //Loop for both columns
    for (int i = 0; i < veclen; i++) {

        cout << left << setw(20) << vecname[i];
        cout << "|";
        cout << right << setw(23) << vecnum[i] << endl;
    }
    cout << endl;

    //Table 2
    for (int i = 0; i < veclen; i++) {
        cout << right << setw(20) << vecname[i] << " ";
        //vector<string> star;
        for (int j = 0; j < vecnum[i]; j++) {
            //star.push_back("*");
            cout << "*";
        }
        cout << endl;
    }


    /* Overall flow of the program:
    aGet some input for the title
    aGet some input for column header #1
    aGet some input for column header #2
    Until the user types "-1":
    Get input for a string
    Validate input
    If valid...
       Split
       Validate second half of input
       If also valid...
          Store separate pieces

    Print out data in table format

    Print out data in chart format
    */

    return 0;
}