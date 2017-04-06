// https://www.codingame.com/ide/puzzle/mars-lander-episode-1
// Xavier Morel - 2016-03-12

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    int N; // the number of points used to draw the surface of Mars.
    cin >> N; cin.ignore();
    int landing_start = 0;
    int landing_end = 0;
    int landing_y;

    for (int i = 0; i < N; i++) {
        int LAND_X; // X coordinate of a surface point. (0 to 6999)
        int LAND_Y; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.

        cin >> LAND_X >> LAND_Y; cin.ignore();
        if ((i == 0 || landing_y != LAND_Y) && (landing_end - landing_start < 1000)) {
            landing_start = LAND_X;
            landing_y     = LAND_Y;
        } else if (landing_y == LAND_Y) {
            landing_end = LAND_X;
        }
    }

    // game loop
    while (1) {
        Coords pos;
        int HS; // the horizontal speed (in m/s), can be negative.
        int VS; // the vertical speed (in m/s), can be negative.
        int F; // the quantity of remaining fuel in liters.
        int R; // the rotation angle in degrees (-90 to 90).
        int P; // the thrust power (0 to 4).
        cin >> pos.x >> pos.y >> HS >> VS >> F >> R >> P; cin.ignore();

        int power = 0;
        if (VS < -39) {
            power = 4;
        }

        cout << "0 " << power << endl; // R P. R is the desired rotation angle. P is the desired thrust power.
    }
}
