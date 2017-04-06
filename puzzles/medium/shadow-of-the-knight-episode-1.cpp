// https://www.codingame.com/ide/puzzle/shadows-of-the-knight-episode-1
// Xavier Morel - 2016-03-14

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define MIN 0
#define MAX 1

using namespace std;

typedef struct {
    int x;
    int y;
} Coords;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    Coords pos;
    Coords range[2];

    range[MIN].x = 0;
    range[MIN].y = 0;
    range[MAX].x = W - 1;
    range[MAX].y = H - 1;

    cin >> pos.x >> pos.y; cin.ignore();

    while (1) {
        string BOMB_DIR; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> BOMB_DIR; cin.ignore();

        if (BOMB_DIR == "U") {
            range[MAX].y = pos.y - 1;
        } else if (BOMB_DIR == "UR") {
            range[MAX].y = pos.y - 1;
            range[MIN].x = pos.x;
        } else if (BOMB_DIR == "R") {
            range[MIN].x = pos.x;
        } else if (BOMB_DIR == "DR") {
            range[MIN].y = pos.y;
            range[MIN].x = pos.x;
        } else if (BOMB_DIR == "D") {
            range[MIN].y = pos.y;
        } else if (BOMB_DIR == "DL") {
            range[MIN].y = pos.y;
            range[MAX].x = pos.x - 1;
        } else if (BOMB_DIR == "L") {
            range[MAX].x = pos.x - 1;
        } else if (BOMB_DIR == "UL") {
            range[MAX].y = pos.y - 1;
            range[MAX].x = pos.x - 1;
        }

        if (range[MAX].x != range[MIN].x) {
            pos.x = ceil((range[MAX].x + range[MIN].x) / 2.0f);
        } else {
            pos.x = range[MIN].x;
        }

        if (range[MAX].y != range[MIN].y) {
            pos.y = ceil((range[MAX].y + range[MIN].y) / 2.0f);
        } else {
            pos.y = range[MIN].y;
        }

        cout << pos.x << " " << pos.y << endl; // the location of the next window Batman should jump to.
    }
}
