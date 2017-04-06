// https://www.codingame.com/ide/puzzle/power-of-thor-episode-1
// Xavier Morel - 2014-10-16

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int LX; // the X position of the light of power
    int LY; // the Y position of the light of power
    int TX; // Thor's starting X position
    int TY; // Thor's starting Y position
    cin >> LX >> LY >> TX >> TY; cin.ignore();

    // game loop
    while (1) {
        int E; // The level of Thor's remaining energy, representing the number of moves he can still make.
        cin >> E; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        if (TY < LY) {
            cout << "S";
            TY++;
        } else if (TY > LY) {
            cout << "N";
            TY--;
        }

        if (TX > LX) {
            cout << "W";
            TX++;
        } else if (TX < LX) {
            cout << "E";
            TX--;
        }

        cout << endl; // A single line providing the move to be made: N NE E SE S SW W or NW
    }
}
