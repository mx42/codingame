// Coders Strike Back Challenge - 2016-02-27
// Xavier Morel - 2016-02-27
// Ranking 543/2530

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define M_PI 3.14159265358979323846  /* pi */

#define MAX_ANGLE               25
#define CHECK_DISTANCE_CLOSE    200
#define CHECK_DISTANCE          3000
#define CHECK_DISTANCE_FAR      6000

#define SPEED_SLOW              50
#define SPEED_MED               100
#define SPEED_FAST              150
#define SPEED_MAX               200

typedef struct s_Coords
{
    int x;
    int y;
} Coords;

typedef struct s_Pod
{
    Coords pos;
    Coords vec;
    int angle;
    int nextCP;

    Coords tgt; // Target.
    int speed;
    string dbgMsg;
} Pod;

Pod myPods[2];
Pod enemyPods[2];

int getAngle(Coords a, Coords b)
{
    float rad = atan2(b.y - a.y, b.x - a.x);
    int deg = (rad * 180 / M_PI);
    return (deg + 360) % 360;
}

Coords getTarget(int podNb, Coords cp)
{
    Coords tmp;
    tmp.x = myPods[podNb].pos.x + myPods[podNb].vec.x;
    tmp.y = myPods[podNb].pos.y + myPods[podNb].vec.y;

    tmp.x = cp.x - tmp.x;
    tmp.y = cp.y - tmp.y;

    tmp.x = myPods[podNb].pos.x + tmp.x;
    tmp.y = myPods[podNb].pos.y + tmp.y;

    return tmp;
}

int getDistance(Coords a, Coords b)
{
    return (int) sqrt(((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) * (b.y - a.y)));
}

int turnsToReach(int podNb, Coords cp)
{
    Coords pos = myPods[podNb].pos;
    Coords speed = myPods[podNb].vec;
    int turns = 0;
    int prevDist = -1;

    int i = 0;

    while (i < 20) {
        int dist = getDistance(pos, cp);
        if (dist < 600) {
            return turns;
        }

        if (prevDist > -1 && prevDist < dist) {
            return -1;
        }

        pos.x += speed.x;
        pos.y += speed.y;

        speed.x *= 0.85;
        speed.y *= 0.85;

        if (speed.x < 5 && speed.y < 5) {
            return -1;
        }

        prevDist = dist;
        turns++;
        i++;
    }

    return -1;
}

void process(int podNb, Coords cp, Coords nextCP)
{
    Pod pod = myPods[podNb];

    int angle = getAngle(myPods[podNb].pos, cp);
    int dist = getDistance(myPods[podNb].pos, cp);

    myPods[podNb].tgt = getTarget(podNb, cp);

    if (((abs(angle - pod.angle) + 360) % 360) < MAX_ANGLE) {
        if (dist > CHECK_DISTANCE) {
            if (dist > CHECK_DISTANCE_FAR) {
                myPods[podNb].speed = SPEED_MAX;
            } else {
                myPods[podNb].speed = SPEED_FAST;
            }
        }  else {
            int nextAngle = getAngle(pod.pos, nextCP);
            if (((abs(nextAngle - pod.angle) + 360) % 360) < MAX_ANGLE) {
                myPods[podNb].speed = SPEED_MAX;
            } else {
                int ttr = turnsToReach(podNb, cp);
                if (ttr == 1) {
                    myPods[podNb].tgt = getTarget(podNb, nextCP);
                    myPods[podNb].speed = 0;
                } else {
                    if (dist > CHECK_DISTANCE_CLOSE) {
                        myPods[podNb].speed = SPEED_MED;
                    } else {
                        myPods[podNb].speed = SPEED_SLOW;
                    }
                }
            }
        }
    } else {
        myPods[podNb].speed = SPEED_SLOW;
    }
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int laps;
    cin >> laps; cin.ignore();
    int checkpointCount;
    cin >> checkpointCount; cin.ignore();

    Coords checkpoints[checkpointCount];

    for (int i = 0; i < checkpointCount; i++) {
        cin >> checkpoints[i].x;
        cin >> checkpoints[i].y;
    }

    // game loop
    while (1) {
        for (int i = 0; i < 2; i++) {
            cin >> myPods[i].pos.x;
            cin >> myPods[i].pos.y;
            cin >> myPods[i].vec.x;
            cin >> myPods[i].vec.y;
            cin >> myPods[i].angle;
            cin >> myPods[i].nextCP;
            cin.ignore();
        }

        for (int i = 0; i < 2; i++) {
            cin >> enemyPods[i].pos.x;
            cin >> enemyPods[i].pos.y;
            cin >> enemyPods[i].vec.x;
            cin >> enemyPods[i].vec.y;
            cin >> enemyPods[i].angle;
            cin >> enemyPods[i].nextCP;
            cin.ignore();
        }

        for (int i = 0; i < 2; i++) {
            Coords cp = checkpoints[myPods[i].nextCP];
            Coords nextCP = checkpoints[(myPods[i].nextCP + 1) % checkpointCount];
            process(i, cp, nextCP);
            cout << myPods[i].tgt.x << " " << myPods[i].tgt.y << " " << myPods[i].speed;
            if (myPods[i].dbgMsg.size() > 0) {
                cout << " " << myPods[i].dbgMsg;
            }
            cout << endl;
        }
    }
}
