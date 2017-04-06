// https://www.codingame.com/ide/puzzle/horse-racing-duals
// Xavier Morel - 2016-03-12

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool two_equals = false;

typedef struct elem_s {
    int pow;
    struct elem_s *p;
    struct elem_s *n;
} elem;

elem *create_elem(int pw)
{
    elem *cur = new elem();
    cur->p = 0;
    cur->n = 0;
    cur->pow = pw;
    return cur;
}

elem *add_elem(elem *first, int pw)
{
    if (!first) {
        return create_elem(pw);
    }

    elem *prev;
    for (elem *tmp = first; tmp; tmp = tmp->n) {
        if (pw == tmp->pow) {
            two_equals = true;
            return first;
        } else if (pw < tmp->pow) {
            elem *cur = create_elem(pw);
            if (tmp->p) {
                tmp->p->n = cur;
            } else {
                first = cur;
            }
            cur->p = tmp->p;
            cur->n = tmp;
            tmp->p = cur;
            return first;
        }
        prev = tmp;
    }

    elem *cur = create_elem(pw);
    prev->n = cur;
    cur->p = prev;

    return first;
}

int main()
{
    int N;
    cin >> N; cin.ignore();

    elem *first = 0;
    elem *cur;

    for (int i = 0; i < N; i++) {
        int pw;
        cin >> pw; cin.ignore();
        first = add_elem(first, pw);
    }

    if (two_equals) {
        cout << "0" << endl;
    } else {
        int least = -1;
        elem *prev = 0;
        for (elem *tmp = first; tmp; tmp = tmp->n) {
            if (prev) {
                delete prev;
            }
            if (tmp->n) {
                int diff = tmp->n->pow - tmp->pow;
                if (least == -1 || least > diff) {
                    least = diff;
                }
            }
            prev = tmp;
        }
        if (prev) {
            delete prev;
        }
        if (least < 0) {
            least = 0;
        }
        cout << least << endl;
    }
}
