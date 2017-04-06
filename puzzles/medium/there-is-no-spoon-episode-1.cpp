// https://www.codingame.com/ide/puzzle/there-is-no-spoon-episode-1
// Xavier Morel - 2016-03-13

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define POS(x,y) ((width * y) + x)

/**
 * Don't let the machines win. You are humanity's last hope...
 **/
int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();

    char table[(width * height) + 1];

    for (int i = 0; i < height; i++) {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        memcpy(table + (width*i), line.c_str(), width);
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (*(table + POS(x, y)) == '.') {
                continue;
            }

            int rightof = -1;
            int below = -1;

            for (int t = x + 1; t < width; t++) {
                if (*(table + POS(t, y)) == '0') {
                    rightof = t;
                    break;
                }
            }

            for (int t = y + 1; t < height; t++) {
                if (*(table + POS(x, t)) == '0') {
                    below = t;
                    break;
                }
            }

            cout
                << x << " "
                << y << " "
                << (rightof == -1 ? -1 : rightof) << " "
                << (rightof == -1 ? -1 : y) << " "
                << (below == -1 ? -1 : x) << " "
                << (below == -1 ? -1 : below) << endl;
        }
    }
}
