// https://www.codingame.com/ide/puzzle/conway-sequence
// Xavier Morel - 2016-03-23

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> line;


void computeNextLine()
{
    vector<int> next;

    int curNb = 0;
    int qty = 0;

    for (int n : line) {
        if (curNb != n) {
            if (curNb != 0) {
                next.push_back(qty);
                next.push_back(curNb);
            }
            curNb = n;
            qty = 1;
        } else {
            qty++;
        }
    }

    if (curNb != 0) {
        next.push_back(qty);
        next.push_back(curNb);
    }

    line = next;
}

void printLine(ostream& out)
{
    bool first = true;
    for (int n : line) {
        if (first == false) {
            out << " ";
        }
        out << n;
        first = false;
    }
    out << endl;
}

int main()
{
    int R;
    cin >> R; cin.ignore();
    int L;
    cin >> L; cin.ignore();

    line.push_back(R);

    for (int i = 1; i < L; i++) {
        printLine(cerr);
        computeNextLine();
    }
    printLine(cout);
}
