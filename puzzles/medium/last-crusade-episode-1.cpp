// https://www.codingame.com/ide/puzzle/the-last-crusade-episode-1
// Xavier Morel - 2016-03-16

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define FROM_LEFT 0
#define FROM_TOP 1
#define FROM_RIGHT 2

#define NOPE 0
#define LEFT 1
#define RIGHT 2
#define BOTT 3

int types[14][3] = {
    //  LEFT    TOP     RIGHT
    {NOPE,  NOPE,   NOPE},  // type 0
    {BOTT,  BOTT,   BOTT},  // type 1
    {RIGHT, NOPE,   LEFT},  // type 2
    {NOPE,  BOTT,   NOPE},  // type 3
    {NOPE,  LEFT,   BOTT},  // type 4
    {BOTT,  RIGHT,  NOPE},  // type 5
    {RIGHT, NOPE,   LEFT},  // type 6
    {NOPE,  BOTT,   BOTT},  // type 7
    {BOTT,  NOPE,   BOTT},  // type 8
    {BOTT,  BOTT,   NOPE},  // type 9
    {NOPE,  LEFT,   NOPE},  // type 10
    {NOPE,  RIGHT,  NOPE},  // type 11
    {NOPE,  NOPE,   BOTT},  // type 12
    {BOTT,  NOPE,   NOPE}
};

int getDir(int type, int pos)
{
    cerr << "Cell is of type " << type << " and entered from " << pos << endl;
    return types[type][pos];
}

int main()
{
    int W; // number of columns.
    int H; // number of rows.
    cin >> W >> H; cin.ignore();
    int grid[H+1][W+1];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            int x;
            cin >> x;
            cerr << x << endl;
            grid[i][j] = x;
        }
        cin.ignore();
    }
    int EX;
    cin >> EX; cin.ignore();

    cerr << "Large: " << W << " Haut: " << H << endl;
    for (int i = 0; i < H; i++) {
        cerr << "|";
        for (int j = 0; j < W; j++) {
            cerr << grid[i][j] << " ";
        }
        cerr << endl;
    }
    cerr << "----------" << endl;


    // game loop
    while (1) {
        int XI;
        int YI;
        string pos_str;
        int pos;
        cin >> XI >> YI >> pos_str; cin.ignore();

        if (pos_str == "TOP") {
            pos = FROM_TOP;
        } else if (pos_str == "LEFT") {
            pos = FROM_LEFT;
        } else if (pos_str == "RIGHT") {
            pos = FROM_RIGHT;
        } else {
            cerr << "Unrecognized entrance..." << endl;
        }

        cerr << "Cell at " << XI << "x" << YI << endl;
        int dir = getDir(grid[YI][XI], pos);
        cerr << "Dir: " << dir << endl;
        switch (dir) {
        case LEFT:
            XI--;
            break;
        case RIGHT:
            XI++;
            break;
        case BOTT:
            YI++;
            break;
        default:
            cerr << "WUT?" << endl;
        }
        cout << XI << " " << YI << endl;
    }
}
