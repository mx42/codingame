// https://www.codingame.com/ide/puzzle/skynet-revolution-episode-1
// Xavier Morel - 2016-03-12

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    bool is_gateway = false;
    vector<int> links;
} Node;

Node    *nodes;

void remove_link(int a, int b)
{
    for (auto it = nodes[a].links.begin(); it != nodes[a].links.end(); it++) {
        if (*it == b) {
            nodes[a].links.erase(it);
            break;
        }
    }

    for (auto it = nodes[b].links.begin(); it != nodes[b].links.end(); it++) {
        if (*it == a) {
            nodes[b].links.erase(it);
            break;
        }
    }
    cout << a << " " << b << endl;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N, L, E;
    cin >> N >> L >> E; cin.ignore();
    nodes = new Node[N];

    for (int i = 0; i < L; i++) {
        int N1, N2;
        cin >> N1 >> N2; cin.ignore();
        nodes[N1].links.push_back(N2);
        nodes[N2].links.push_back(N1);
    }

    for (int i = 0; i < E; i++) {
        int EI;
        cin >> EI; cin.ignore();
        nodes[EI].is_gateway = true;
    }

    // game loop
    while (1) {
        int SI;
        cin >> SI; cin.ignore();

        int a = 0;
        int b = 0;

        for (int i : nodes[SI].links) {
            cerr << "Check node " << i << endl;
            if (nodes[i].is_gateway && nodes[i].links.size() > 0) {
                a = SI;
                b = i;
                break;
            }
        }

        if (a == 0 && b == 0) {
            for (int i = 0; i < N; i++) {
                if (nodes[i].is_gateway && nodes[i].links.size() > 0) {
                    a = i;
                    b = nodes[i].links.back();
                    break;
                }
            }
        }
        remove_link(a, b);
    }
}
