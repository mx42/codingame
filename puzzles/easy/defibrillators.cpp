// https://www.codingame.com/ide/puzzle/defibrillators
// Xavier Morel - 2016-03-07

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define M_PI (3.14159265358979323846)

using namespace std;

typedef struct {
    double lon;
    double lat;
} Coords;

typedef struct {
    int     id;
    string  name;
    string  address;
    string  phone; // ?
    Coords  coords;
} Defib;

void fillDefib(string s, Defib *out)
{
    size_t current;
    size_t next = -1;
    string tmp;

    current = next + 1;
    next = s.find_first_of(";", current);
    out->id = stoi(s.substr(current, next - current));

    current = next + 1;
    next = s.find_first_of(";", current);
    out->name = s.substr(current, next - current);

    current = next + 1;
    next = s.find_first_of(";", current);
    out->address = s.substr(current, next - current);

    current = next + 1;
    next = s.find_first_of(";", current);
    out->phone = s.substr(current, next - current);

    current = next + 1;
    next = s.find_first_of(";", current);
    tmp = s.substr(current, next - current);
    replace(tmp.begin(), tmp.end(), ',', '.');
    out->coords.lon = stod(tmp);

    current = next + 1;
    next = s.find_first_of(";", current);
    tmp = s.substr(current, next - current);
    replace(tmp.begin(), tmp.end(), ',', '.');
    out->coords.lat = stod(tmp);
}

double calcDist(Coords from, Coords to)
{
    double fLon = from.lon * M_PI / 180;
    double fLat = from.lat * M_PI / 180;
    double tLon = to.lon * M_PI / 180;
    double tLat = to.lat * M_PI / 180;

    double x = (tLon - fLon) * cos((tLat + fLat) / 2);
    double y = (tLat - fLat);
    double res = (sqrt((x*x) + (y*y)) * 6371);

    return res;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string  tmp;
    Coords  userCoords;

    cin >> tmp; cin.ignore();
    replace(tmp.begin(), tmp.end(), ',', '.');
    userCoords.lon = stod(tmp);
    cin >> tmp; cin.ignore();
    replace(tmp.begin(), tmp.end(), ',', '.');
    userCoords.lat = stod(tmp);

    int N;
    cin >> N; cin.ignore();

    int nearest = -1;
    double nearest_dist = 0;

    Defib defibs[N];
    for (int i = 0; i < N; i++) {
        string DEFIB;
        getline(cin, DEFIB);
        fillDefib(DEFIB, &defibs[i]);
        double dist = calcDist(userCoords, defibs[i].coords);
        if (nearest < 0 || nearest_dist > dist) {
            nearest = i;
            nearest_dist = dist;
        }
    }

    cout << defibs[nearest].name << endl;
}
