// https://www.codingame.com/ide/puzzle/bender-episode-1
// Xavier Morel - 2016-03-15

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define LOOP 0
#define WEST 1
#define NORTH 2
#define EAST 3
#define SOUTH 4

#define EMPTY ' '
#define DIR_WEST 'W'
#define DIR_NORTH 'N'
#define DIR_EAST 'E'
#define DIR_SOUTH 'S'
#define WALL '#'
#define BRK_WALL 'X'
#define START '@'
#define END '$'
#define BEER 'B'
#define TELEPORTER 'T'
#define INVERTER 'I'

using namespace std;

vector<string> map;

struct Coords {
    int x;
    int y;

    Coords () : x(0), y(0) {};
    Coords (int x, int y) : x(x), y(y) {};
};

struct Character {
    Coords pos;
    char dir = SOUTH;
    bool boosted = false;
    bool inverted = false;
    int brkWalls = 0;

    void faceNextDirection(bool recursive_call)
        {
            if (inverted == true) {
                if (!recursive_call) {
                    dir = WEST;
                    return;
                }
                if (dir == WEST) {
                    dir = NORTH;
                } else if (dir == NORTH) {
                    dir = EAST;
                } else if (dir == EAST) {
                    dir = SOUTH;
                } else if (dir == SOUTH) {
                    dir = WEST;
                }
            } else {
                if (!recursive_call) {
                    dir = SOUTH;
                    return;
                }
                if (dir == SOUTH) {
                    dir = EAST;
                } else if (dir == EAST) {
                    dir = NORTH;
                } else if (dir == NORTH) {
                    dir = WEST;
                } else if (dir == WEST) {
                    dir = SOUTH;
                }
            }
        }
};

vector<Coords> getPositions(char type)
{
    vector<Coords> res;
    for (int x = 0; x < map.size(); x++) {
        size_t y = 0;
        while ((y = map[x].find_first_of(type, y)) != string::npos) {
            res.push_back(Coords(x, y));
            y++;
        }
    }
    return res;
}

inline void clearCell(Coords pos)
{
    map[pos.x].at(pos.y) = EMPTY;
}

char getCurrentCellType(const Character &bender)
{
    return map[bender.pos.x].at(bender.pos.y);
}

Coords getNextCellPos(const Character &bender)
{
    Coords next = bender.pos;
    switch (bender.dir) {
    case NORTH:
        next.x--;
        break;
    case SOUTH:
        next.x++;
        break;
    case WEST:
        next.y--;
        break;
    case EAST:
        next.y++;
        break;
    }
    return next;
}

char getNextCellType(const Character &bender)
{
    Coords next = getNextCellPos(bender);
    return map[next.x].at(next.y);
}

char getDirection(Character &bender, bool recursive_call)
{
    char nextNode = getNextCellType(bender);
    char dir = bender.dir;
    if (nextNode == WALL) {
        bender.faceNextDirection(recursive_call);
        return getDirection(bender, true);
    } else if (nextNode == BRK_WALL) {
        if (bender.boosted == false) {
            bender.faceNextDirection(recursive_call);
            return getDirection(bender, true);
        }
    }
    return dir;
}

void teleportBender(Character &bender)
{
    vector<Coords> poss = getPositions(TELEPORTER);
    for (Coords pos : poss) {
        if (bender.pos.x != pos.x || bender.pos.y != pos.y) {
            bender.pos = pos;
            break;
        }
    }
    cerr << "Teleport couldnt find other teleporter ?! Wtf ?" << endl;
}

vector<int> getDirections(void)
{
    vector<Character> history;
    Character bender;
    vector<int> dirs;

    // Get initial pos.
    bender.pos = getPositions(START).front();
    clearCell(bender.pos);

    int turns = 0;
    while (1) {
        // Check current cell and proceed as necessary (Teleporter, Beer, Inverter, new direction, break wall, ...)
        char currentCell = getCurrentCellType(bender);
        switch (currentCell) {
        case TELEPORTER:
            teleportBender(bender);
            break;
        case BEER:
            bender.boosted = bender.boosted ? false : true;
            break;
        case INVERTER:
            bender.inverted = bender.inverted ? false : true;
            break;
        case DIR_NORTH:
            bender.dir = NORTH;
            break;
        case DIR_SOUTH:
            bender.dir = SOUTH;
            break;
        case DIR_WEST:
            bender.dir = WEST;
            break;
        case DIR_EAST:
            bender.dir = EAST;
            break;
        case BRK_WALL: // We should be boosted here...
            if (!bender.boosted) {
                cerr << "WTF ?! On a breakable wall but not boosted ?!" << endl;
            }
            clearCell(bender.pos);
            break;
        case END:
            // YAY!
            return dirs;
        }
        // Check for next direction.
        char dir = getDirection(bender, false);
        // Append next direction to the stack.
        dirs.push_back(dir);
        // Move to the next cell.
        bender.pos = getNextCellPos(bender);
        // Check history for doubles with current status.
        // If loop:   clean stuff + return vector<int>();
        // Save current status to the history.
        turns++;

        // Crappy check for loops, hehe...
        if (turns > 200) {
            return vector<int>();
        }
    }

    return dirs;
}

int main()
{
    int H = 0;
    int W = 0;
    cin >> H >> W; cin.ignore();
    for (int i = 0; i < H; i++) {
        string row;
        getline(cin, row);
        map.push_back(row);
    }

    vector<int> dirs = getDirections();
    if (!dirs.size()) {
        cout << "LOOP" << endl;
        return 0;
    }

    for (int dir : dirs) {
        switch (dir) {
        case NORTH:
            cout << "NORTH" << endl;
            break;
        case SOUTH:
            cout << "SOUTH" << endl;
            break;
        case WEST:
            cout << "WEST" << endl;
            break;
        case EAST:
            cout << "EAST" << endl;
            break;
        }
    }
}
