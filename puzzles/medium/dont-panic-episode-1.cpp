// https://www.codingame.com/ide/puzzle/don't-panic-episode-1
// Xavier Morel - 2016-03-14

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int nbFloors; // number of floors

    int width; // width of the area
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor

    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();

    int floors[nbFloors];
    memset(floors, 0, nbFloors);
    floors[exitFloor] = exitPos;

    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        floors[elevatorFloor] = elevatorPos;
    }

    //    bool firstTurn = true;

    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        int prevDestPos = (cloneFloor > 0 ? floors[cloneFloor - 1] : -1);
        int destPos = floors[cloneFloor];
        cerr << "Clone " << clonePos << " " << destPos << endl;

        if (cloneFloor == -1 && clonePos == -1 && direction == "NONE") {
            cerr << "no clone" << endl;
            cout << "WAIT" << endl;
        } else if (
            (clonePos == width - 1 && direction == "RIGHT")
            || (clonePos == 0 && direction == "LEFT")
            ) {
            cerr << "avoid laser" << endl;
            cout << "BLOCK" << endl;
        } else if (prevDestPos != clonePos && (
                       (clonePos > destPos && direction != "LEFT")
                       || (clonePos < destPos && direction != "RIGHT")
                       )
            ) {
            cerr << "Not the right direction" << endl;
            cout << "BLOCK" << endl;
        } else {
            cerr << "..." << endl;
            cout << "WAIT" << endl;
        }
    }
}
