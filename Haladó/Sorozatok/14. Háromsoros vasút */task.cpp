/*
Megoldás lényege:
A kocsikat a bemeneti sorrendben tesszük a három oldalsín valamelyikére (B-művelet). Egy oldalsínen a kocsik
abban a sorrendben jönnek ki, ahogy beléjük kerültek, ezért minden sínen a bemeneti sorrendben
nemcsökkenő címkesorozat kell álljon. A bemenet tehát akkor rendezhető, ha három nemcsökkenő részsorozatra
bontható, és ez pontosan akkor nem lehetséges, ha van 4 hosszú szigorúan csökkenő részsorozat.
A bontást mohón végezzük: minden kocsit arra a sínre teszünk, amelynek utolsó kocsija a legnagyobb, de még
nem nagyobb az új kocsi címkéjénél; ha ilyen sín nincs, a válasz NEM. A kiürítésnél (K-művelet) mindig azt
a sínt választjuk, amelynek első kocsija a legkisebb címkéjű. Az időigény O(N).
*/
/*
Hint 1: || Egy oldalsínen a kocsik a beérkezés sorrendjében jönnek ki, így ezen a sínen a bemeneti sorrendben a címkéknek nemcsökkenőnek kell lenniük. ||
Hint 2: || Ha a bemenet három nemcsökkenő részsorozatra bontható, a kiürítés egyszerű: mindig a három sín közül a legkisebb első címkéjű kocsit húzd ki. ||
Hint 3: || A bontást mohón építsd: minden sínhez tartsd nyilván az utolsó kocsi címkéjét, és az új kocsit arra a sínre tedd, amelynek ez a címke a legnagyobb, de még nem nagyobb az új címkénél. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // top[c]: a c-edik oldalsín utolsó kocsijának címkéje (0, ha a sín üres; a címkék 1..4)
    array<int, 3> top = {0, 0, 0};
    vector<int> side(n);
    for (int i = 0; i < n; ++i) {
        int best = -1;
        for (int c = 0; c < 3; ++c) {
            if (top[c] <= a[i] && (best == -1 || top[c] > top[best])) best = c;
        }
        if (best == -1) {
            cout << "NEM\n";
            return 0;
        }
        side[i] = best;
        top[best] = a[i];
    }

    vector<string> ops;
    ops.reserve(2 * n);
    array<vector<int>, 3> track;
    for (int i = 0; i < n; ++i) {
        ops.push_back("B" + to_string(side[i] + 1));
        track[side[i]].push_back(a[i]);
    }

    array<size_t, 3> head = {0, 0, 0};
    while (true) {
        int best = -1;
        for (int c = 0; c < 3; ++c) {
            if (head[c] >= track[c].size()) continue;
            if (best == -1 || track[c][head[c]] < track[best][head[best]]) best = c;
        }
        if (best == -1) break;
        ops.push_back("K" + to_string(best + 1));
        ++head[best];
    }

    for (const string &op : ops) cout << op << '\n';
    return 0;
}
