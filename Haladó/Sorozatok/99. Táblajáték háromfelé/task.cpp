/*
Megoldás lényege:
A tábla sorai rendre 1,3,9,27,... hosszúak, ezért egy mezőt elég a (sor, oszlop) párral leírni.
Az oszlop indexét hármas számrendszerben is felfoghatjuk: lefelé lépve egy új hármas számjegyet
illesztünk hozzá (0,1 vagy 2), felfelé lépve pedig egyet levágunk róla.

Mivel legfeljebb 1000 lépés van, az oszlop sorszáma nagyon nagy lehet, ezért tetszőleges pontosságú
egészt használunk. A végén hármas számrendszerben írjuk ki.
*/
/*
Hint 1: || A lefelé lépések a hármas számrendszerbeli számjegyek hozzáfűzésének felelnek meg. ||
Hint 2: || A felfelé lépés ugyanennek az inverze: osztás 3-mal. ||
Hint 3: || Az oszlopszám kinőheti a 64 bites típust, ezért nagy egész kell. ||
*/

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
        if (digits[i] < 2) {
            ++digits[i];
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
        digits[i] = 2;
        ++i;
    }
    --digits[i];
    normalize(digits);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    int row = 0;
    deque<int> col(1, 0);

    for (int i = 0; i < k; ++i) {
        int move;
        cin >> move;
        if (move == 0 || move == 1 || move == 2) {
            col.push_front(move);
            normalize(col);
            ++row;
        } else if (move == 3) {
            if (!col.empty()) col.pop_front();
            if (col.empty()) col.push_back(0);
            --row;
        } else if (move == 4) {
            subOne(col);
        } else {
            addOne(col);
        }
    }

    cout << row << '\n';
    if (col.size() == 1 && col[0] == 0) {
        cout << 0 << '\n';
        return 0;
    }

    string digits;
    digits.reserve(col.size());
    for (auto it = col.rbegin(); it != col.rend(); ++it) {
        digits.push_back(char('0' + *it));
    }
    cout << digits << '\n';
    return 0;
}