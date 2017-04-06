// https://www.codingame.com/ide/puzzle/chuck-norris
// Xavier Morel - 2014-10-16

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void print_bits(bool bit, int len)
{
    static bool first_char = true;

    if (!first_char) {
        cout << ' ';
    }

    cout << '0';
    if (!bit) {
        cout << '0';
    }
    cout << ' ';

    for (int i = 0; i < len; i++) {
        cout << '0';
    }

    first_char = false;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string MESSAGE;
    getline(cin, MESSAGE);

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    bool bit;
    int len = 0;

    for (char c : MESSAGE) {
        // cerr << "Letter " << c << endl;
        for (int w = 7; w > 0; w--) {
            bool cur_bit = (c & 1 << (w - 1));
            if (len == 0 || bit == cur_bit) {
                bit = cur_bit;
                len++;
            } else if (bit != cur_bit) {
                // cerr << "printing " << len << " bits " << (bit ? '1' : '0') << endl;
                print_bits(bit, len);
                bit = cur_bit;
                len = 1;
            }

            // cerr << "weight " << w << ": " << (bit ? '1' : '0') << endl;
        }
        // cerr << "printing " << len << " bits " << (bit ? '1' : '0') << endl;
    }

    print_bits(bit, len);

    cout << endl;
}
