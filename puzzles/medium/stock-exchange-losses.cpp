// https://www.codingame.com/ide/puzzle/stock-exchange-losses
// Xavier Morel - 2016-03-16

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n;
    cin >> n; cin.ignore();
    vector<int> history;
    int last_high = 0;
    int last_low = 0;
    int prev = 0;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v; cin.ignore();

        if (i == 0) {
            last_high = v;
            last_low = v;
            continue;
        } else {
            if (v > last_high) {
                if (last_high != last_low) {
                    history.push_back(last_high);
                    history.push_back(last_low);
                }
                last_high = v;
                last_low = v;
            } else if (v < last_low) {
                last_low = v;
            }
        }
    }

    if (last_high != last_low) {
        history.push_back(last_high);
        history.push_back(last_low);
    }

    int max_loss = 0;
    for (vector<int>::iterator it = history.begin(); it != history.end(); it++) {
        int loss = *min_element(it, history.end()) - *it;
        if (loss < max_loss) {
            max_loss = loss;
        }
    }

    cout << max_loss << endl;
}
