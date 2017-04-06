// https://www.codingame.com/ide/puzzle/mayan-calculation
// Xavier Morel - 2016-03-15

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int L;
    int H;
    cin >> L >> H; cin.ignore();
    map<int, string> nums;
    for (int i = 0; i < H; i++) {
        string numeral;
        cin >> numeral; cin.ignore();
        for (int j = 0; j < 20; j++) {
            if (!nums.count(j)) {
                nums[j] = string();
            }
            nums[j] += numeral.substr(j*L, L);
            nums[j] += "\n";
        }
    }
    map<int, string> term1;
    int S1;
    cin >> S1; cin.ignore();
    for (int i = 0; i < S1; i++) {
        int numPow = floor(i/H);
        string num1Line;
        cin >> num1Line; cin.ignore();
        if (!term1.count(numPow)) {
            term1[numPow] = string();
        }
        term1[numPow] += num1Line;
        term1[numPow] += "\n";
    }

    map<int, string> term2;
    int S2;
    cin >> S2; cin.ignore();
    for (int i = 0; i < S2; i++) {
        int numPow = floor(i/H);
        string num2Line;
        cin >> num2Line; cin.ignore();
        if (!term2.count(numPow)) {
            term2[numPow] = string();
        }
        term2[numPow] += num2Line;
        term2[numPow] += "\n";
    }
    string operation;
    cin >> operation; cin.ignore();

    //    cerr << "Numbers:" << endl;
    double number1 = 0;
    double number2 = 0;

    for (int i = 0; i < 20; i++) {
        //        cerr << i << endl << nums[i] << endl;
        for (int j = 0; j < term1.size(); j++) {
            if (term1[j] == nums[i]) {
                int pw = term1.size() - j - 1;
                cerr << "Number1 += " << i << " * 20^ " << pw << endl;
                number1 += i * pow(20.0, pw);
            }
        }
        for (int j = 0; j < term2.size(); j++) {
            if (term2[j] == nums[i]) {
                int pw = term2.size() - j - 1;
                cerr << "Number2 += " << i << " * 20^ " << pw << endl;
                number2 += i * pow(20.0, pw);
            }
        }
    }
    //    cerr << "term1:" << endl;
    //    for (int i = 0; i < term1.size(); i++) {
    //        cerr << term1[i] << endl;
    //    }
    //    cerr << number1 << endl;

    //    cerr << "term2:" << endl;
    //    for (int i = 0; i < term2.size(); i++) {
    //        cerr << term2[i] << endl;
    //    }
    //    cerr << number2 << endl;

    cerr << number1 << operation << number2;

    double res = 0;
    switch (operation.c_str()[0]) {
    case '+':
        res = number1 + number2;
        break;
    case '-':
        res = number1 - number2;
        break;
    case '/':
        res = number1 / number2;
        break;
    case '*':
        res = number1 * number2;
        break;
    }

    cerr << " = " << res << endl;

    bool started_to_write = false;
    for (int i = 64; i > 0; i--) {
        double curPow = pow(20.0, i - 1);
        if (curPow <= res) {
            int curNb = floor(res / curPow);
            cerr << "Current pow: " << curPow << " - nb: " << curNb << " = " << curPow * curNb << " (res " << res << ")" << endl;
            res -= (curNb * curPow);
            cout << nums[curNb];
            started_to_write = true;
        } else if (started_to_write == true) {
            cout << nums[0]; // endl should be included.
        }
    }
    if (started_to_write == false) {
        cout << nums[0];
    }
}
