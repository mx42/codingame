// https://www.codingame.com/ide/puzzle/bender-episode-2
// Xavier Morel - 2016-03-15

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Room {
    int nb;
    int money;
    int door1;
    int door2;

    int cache_money = 0;
};

map<int, Room> rooms;

int getMostMoney(int roomNb)
{
    int money1 = 0;
    int money2 = 0;
    if (rooms[roomNb].door1 > -1) {
        money1 = getMostMoney(rooms[roomNb].door1);
    }
    if (rooms[roomNb].door2 > -1) {
        money2 = getMostMoney(rooms[roomNb].door2);
    }

    if (money1 > money2) {
        rooms[roomNb].money += money1;
    } else {
        rooms[roomNb].money += money2;
    }
    rooms[roomNb].door1 = -1;
    rooms[roomNb].door2 = -1;

    return rooms[roomNb].money;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        string door1;
        string door2;
        Room room;
        cin >> room.nb >> room.money >> door1 >> door2; cin.ignore();
        if (door1 == "E") {
            room.door1 = -1;
        } else {
            room.door1 = stoi(door1);
        }
        if (door2 == "E") {
            room.door2 = -1;
        } else {
            room.door2 = stoi(door2);
        }
        rooms[room.nb] = room;
    }

    cout << getMostMoney(0) << endl;
}
