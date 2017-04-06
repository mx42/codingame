// https://www.codingame.com/ide/puzzle/temperatures
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
    int N; // the number of temperatures to analyse
    cin >> N; cin.ignore();



    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    if (N == 0) {
        cout << "0";
    } else {
        int minTemp;
        for (int i = 0; i < N; i++) {
            int temp;
            cin >> temp;

            if (i == 0) {
                minTemp = temp;
            } else if (
                ((temp * temp) < (minTemp * minTemp)) || (
                    (temp * temp) == (minTemp * minTemp) && minTemp < temp
                    )
                ) {
                minTemp = temp;
            }
        }

        cout << minTemp;
    }
    cout << endl;
}
