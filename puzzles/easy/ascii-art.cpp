// https://www.codingame.com/ide/puzzle/ascii-art
// Xavier Morel - 2014-10-16

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> letters;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    string T;
    getline(cin, T);


    for (int i = 0; i < H; i++) {
        string ROW;
        getline(cin, ROW);
        letters.push_back(ROW);
    }

    for (char &c : T) {
        // Handling char.
        if (c >= 'a' && c <= 'z') {
            c -= 'a';
        } else if (c >= 'A' && c <= 'Z') {
            c -= 'A';
        } else {
            c = 26; // ?
        }
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    for (int i = 0; i < H; i++) {
        for (char c : T) {
            cout << letters[i].substr((c*L), L);
        }
        cout << endl;
    }
}
