// https://www.codingame.com/ide/puzzle/scrabble
// Xavier Morel - 2016-03-15

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    string  w;
    int     val = 0;
} Word;

Word getWord(string str)
{
    Word res;
    res.w = str;
    res.val += std::count_if(str.begin(), str.end(), [](char c) {return c == 'q' || c == 'z';}) * 10;
    res.val += std::count_if(str.begin(), str.end(), [](char c) {return c == 'j' || c == 'x';}) * 8;
    res.val += std::count_if(str.begin(), str.end(), [](char c) {return c == 'k';}) * 5;
    res.val += std::count_if(str.begin(), str.end(), [](char c) {return c == 'f' || c == 'h' || c == 'v' || c == 'w' || c == 'y';}) * 4;
    res.val += std::count_if(str.begin(), str.end(), [](char c) {return c == 'b' || c == 'c' || c == 'm' || c == 'p';}) * 3;
    res.val += std::count_if(str.begin(), str.end(), [](char c) {return c == 'd' || c == 'g';}) * 2;
    res.val += std::count_if(str.begin(), str.end(), [](char c) {return c == 'e' || c == 'a' || c == 'i' || c == 'o' || c == 'n' || c == 'r' || c == 't' || c == 'l' || c == 's' || c == 'u';}) * 1;
    return res;
}

bool checkLetters(string word, string available)
{
    // A bit redundant, but whatever.
    for (char c : available) {
        if (count(word.begin(), word.end(), c) > count(available.begin(), available.end(), c)) {
            return false;
        }
    }

    return true;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int N;
    cin >> N; cin.ignore();
    vector<Word> dict;

    for (int i = 0; i < N; i++) {
        string W;
        getline(cin, W);
        if (W.size() < 8) {
            dict.push_back(getWord(W));
        }
    }
    string LETTERS;
    getline(cin, LETTERS);

    cerr << "Letters: " << LETTERS << endl;

    Word *bestWord = 0;
    for (Word word : dict) {
        if (word.w.find_first_not_of(LETTERS) == string::npos) {
            if (!checkLetters(word.w, LETTERS)) {
                continue;
            }
            // Check for multiple letter occurrences...
            if (bestWord == 0 || word.val > bestWord->val) {
                cerr << "Word is best than stored one: " << word.w << endl;
                if (bestWord != 0) {
                    delete bestWord;
                }
                bestWord = new Word(word);
            }
        } else {
            cerr << "Word with invalid letters: " << word.w << endl;
        }
    }

    // filtering of dict:
    // str.find_first_not_of(LETTERS)

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << bestWord->w << endl;
    delete bestWord;
}
