// https://www.codingame.com/ide/puzzle/mime-type
// Xavier Morel - 2014-10-16

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N; // Number of elements which make up the association table.
    cin >> N; cin.ignore();
    int Q; // Number Q of file names to be analyzed.
    cin >> Q; cin.ignore();

    map<string, string> mimes;

    for (int i = 0; i < N; i++) {
        string EXT; // file extension
        string MT; // MIME type.
        cin >> EXT >> MT; cin.ignore();

        for (char &c : EXT) {
            if (c >= 'A' && c <= 'Z') {
                c -= 'A' - 'a';
            }
        }
        mimes[EXT] = MT;
    }
    for (int i = 0; i < Q; i++) {
        string FNAME; // One file name per line.
        getline(cin, FNAME);

        string ext;
        if (FNAME.find_last_of('.') != string::npos) {
            ext = FNAME.substr(FNAME.find_last_of('.') + 1);

            for (char &c : ext) {
                if (c >= 'A' && c <= 'Z') {
                    c -= 'A' - 'a';
                }
            }
        } else {
            ext = "";
        }

        cerr << "File " << FNAME << " extension " << ext << endl;

        if (mimes.count(ext)) {
            cout << mimes[ext] << endl;
        } else {
            cout << "UNKNOWN" << endl;
        }
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    // cout << "UNKNOWN" << endl; // For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.
}
