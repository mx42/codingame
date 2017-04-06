// https://www.codingame.com/ide/puzzle/winamax-battle
// Xavier Morel - 2016-03-14
// WIP : only passing tests up to 88%...

#include <iostream>
#include <string>
#include <list>

using namespace std;

int parseCard(string card)
{
    int num;
    card = card.substr(0, card.size() - 1);
    if (card == "J") {
        num = 11;
    } else if (card == "Q") {
        num = 12;
    } else if (card == "K") {
        num = 13;
    } else if (card == "A") {
        num = 14;
    } else {
        num = stoi(card);
    }
    return num;
}

void moveCards(list<int> &winner, int card1, list<int> &stack1, int card2, list<int> &stack2)
{
    while (stack1.size() > 0) {
        winner.push_back(stack1.front());
        stack1.pop_front();
    }
    winner.push_back(card1);
    while (stack2.size() > 0) {
        winner.push_back(stack2.front());
        stack2.pop_front();
    }
    winner.push_back(card2);
}

void battleMove(list<int> &stack, int card, list<int> &cards)
{
    stack.push_back(card);
    for (int i = 0; i < 3; i++) {
        if (cards.size() == 0) {
            break;
        }
        stack.push_back(cards.front());
        cards.pop_front();
    }
}

int runSimulation(list<int> &p1, list<int> &p2) {
    list<int> stack1;
    list<int> stack2;
    int turns = 0;

    while (p1.size() > 0 && p2.size() > 0) {
        cerr << "Turn " << turns << ": " << p1.size() << " (" << stack1.size() << ") vs " << p2.size() << " (" << stack2.size() << ")" << endl;

        int first1 = p1.front(); p1.pop_front();
        int first2 = p2.front(); p2.pop_front();

        if (first1 > first2) {
            cerr << first1 << " > " << first2 << endl;
            moveCards(p1, first1, stack1, first2, stack2);
            turns++;
        } else if (first1 < first2) {
            cerr << first1 << " < " << first2 << endl;
            moveCards(p2, first1, stack1, first2, stack2);
            turns++;
        } else {
            // BATTLE
            cerr << "Battle" << endl;
            battleMove(stack1, first1, p1);
            battleMove(stack2, first2, p2);
        }

    }

    cerr << "END Turn " << turns << ": " << p1.size() << " (" << stack1.size() << ") vs " << p2.size() << " (" << stack2.size() << ")" << endl;

    return turns;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    list<int> player1;
    list<int> player2;

    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string cardp1; // the n cards of player 1
        cin >> cardp1; cin.ignore();
        player1.push_back(parseCard(cardp1));
    }

    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    for (int i = 0; i < m; i++) {
        string cardp2; // the m cards of player 2
        cin >> cardp2; cin.ignore();
        player2.push_back(parseCard(cardp2));
    }

    int turns = runSimulation(player1, player2);

    if (!player1.size() && !player2.size()) {
        cout << "PAT" << endl;
    } else {
        int winner = (player1.size() > 0 ? 1 : 2);
        cout << winner << " " << turns << endl;
    }
}
