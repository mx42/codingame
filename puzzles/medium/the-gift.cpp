// https://www.codingame.com/ide/puzzle/the-gift
// Xavier Morel - 2016-03-14

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef struct {
    int number;
    int budget;
    int resp;
} Ood;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int number;
    cin >> number; cin.ignore();
    int total_price;
    cin >> total_price; cin.ignore();
    int budget[number];
    int total_sum = 0;
    cerr << "Price: " << total_price << " for " << number << " people." << endl;
    for (int i = 0; i < number; i++) {
        cin >> budget[i]; cin.ignore();
        total_sum += budget[i];
        cerr << "Budget " << i << ": " << budget[i] << " (Total: " << total_sum << ")" << endl;
    }

    if (total_sum < total_price) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    int res[number];
    for (int i = 0; i < number; i++) {
        res[i] = 0;
    }

    int left = total_price;
    while (left > 0) {
        int eq_parts = left / number;
        if (eq_parts == 0) {
            eq_parts = 1;
        }
        cerr << "Each ood should pay " << eq_parts << " (left: " << left << ")" << endl;
        for (int i = 0; i < number; i++) {
            if (left == 0) {
                break;
            }
            if (budget[i] >= eq_parts) {
                cerr << "Ood " << i << " can pay (budget " << budget[i] << ")" << endl;
                res[i] += eq_parts;
                left -= eq_parts;
                budget[i] -= eq_parts;
                cerr << "-> Will pay total " << res[i] << " (budget left: " << budget[i] << ")" << endl;
            } else {
                cerr << "Ood " << i << " cant pay that much" << endl;
                res[i] += budget[i];
                left -= budget[i];
                budget[i] = 0;
                cerr << "-> Will pay total " << res[i] << " (budget left: " << budget[i] << ")" << endl;
            }
        }
    }

    sort(res, res + number);

    for (int i = 0; i < number; i++) {
        cout << res[i] << endl;
    }
}
