/*
Megoldás lényege:
A tábla sorai kétszereződnek, ezért egy mezőt elég a (sor, oszlop) párral leírni.
A leírt lépések mindegyikére közvetlenül megmondható, hogyan változik a sor és az oszlop:
balra lefelé: a következő sor első fele, jobbra lefelé: a második fele,
felfelé: visszaosztás, vízszintes lépések: oszlop +/- 1.

A végső oszlopot binárisan kell kiírni.
*/
// Hint 1: || A sorok hossza 1,2,4,8,..., ezért a pozíciót binárisan is érdemes felfogni. ||
// Hint 2: || A 0 és 1 lefelé visz, a 2 felfelé, a 3 és 4 ugyanabban a sorban mozgat. ||

#include <bits/stdc++.h>
using namespace std;

static void normalize(deque<int>& digits) {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

static void addOne(deque<int>& digits) {
    int i = 0;
    while (true) {
        if (i == (int)digits.size()) digits.push_back(0);
        if (digits[i] == 0) {
            digits[i] = 1;
            break;
        }
        digits[i] = 0;
        ++i;
    }
    normalize(digits);
}

static void subOne(deque<int>& digits) {
    int i = 0;
    while (digits[i] == 0) {
        digits[i] = 1;
        ++i;
    }
    digits[i] = 0;
    normalize(digits);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;
    int row = 0;
    deque<int> col(1, 0);
    for (int i = 0; i < K; ++i) {
        int x;
        cin >> x;
        if (x == 0) {
            col.push_front(0);
            normalize(col);
            ++row;
        } else if (x == 1) {
            col.push_front(1);
            normalize(col);
            ++row;
        } else if (x == 2) {
            if (!col.empty()) col.pop_front();
            if (col.empty()) col.push_back(0);
            --row;
        } else if (x == 3) {
            subOne(col);
        } else {
            addOne(col);
        }
    }

    cout << row << '\n';
    if (col.size() == 1 && col[0] == 0) {
        cout << 0 << '\n';
    } else {
        string s;
        s.reserve(col.size());
        for (auto it = col.rbegin(); it != col.rend(); ++it) {
            s.push_back(char('0' + *it));
        }
        cout << s << '\n';
    }
    return 0;
}
