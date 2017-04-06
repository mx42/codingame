// https://www.codingame.com/ide/puzzle/teads-sponsored-contest
// Xavier Morel - 2016-03-17

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <cmath>

using namespace std;
map<int, vector<int>> points;

int findFarthestNode(int origin, int *distanceOut)
{
    int maxDistance = 0;
    int farthestNode = 0;
    vector<pair<int,int>> process;

    set<int> discovered;

    process.push_back(pair<int,int>(origin,0));
    while (process.size() > 0) {
        pair<int,int> node = process.back(); // node, distance
        process.pop_back();
        discovered.insert(node.first);

        if (node.second > maxDistance) {
            maxDistance = node.second;
            farthestNode = node.first;
        }

        for (int adjNode : points[node.first]) {
            if (discovered.find(adjNode) == discovered.end()) {
                process.push_back(pair<int,int>(adjNode, node.second + 1));
            }
        }

    }

    if (distanceOut != 0) {
        *distanceOut = maxDistance;
    }

    return farthestNode;
}



int main()
{
    int n;
    cin >> n; cin.ignore();
    int firstNode;
    for (int i = 0; i < n; i++) {
        int xi;
        int yi;
        cin >> xi >> yi; cin.ignore();
        points[xi].push_back(yi);
        points[yi].push_back(xi);
        if (i == 0) {
            firstNode = xi;
        }
    }

    int distance;
    int farNode = findFarthestNode(firstNode, &distance);
    cerr << "Farthest node from origin is " << farNode << " with distance of " << distance << endl;
    farNode = findFarthestNode(farNode, &distance);
    cerr << "Farthest node from previous is " << farNode << " with distance of " << distance << endl;

    cout << ceil(distance / 2.0f) << endl;
}
