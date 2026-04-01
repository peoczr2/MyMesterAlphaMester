/*
Megoldás lényege:
Az őrzött napok uniója rendezett, diszjunkt intervallumokból áll. Egy új jelentkező szakasza csak a
szomszédos intervallumokkal tud összeérni, ezért a komponensszám változása kizárólag attól függ,
hogy balról, jobbról, mindkét oldalról vagy egyik oldalról sem ér hozzá.

A válasz minden lépés után az intervallumok száma.
*/
// Hint 1: || Csak a szomszédos, esetleg éppen érintkező intervallumok számítanak. ||
// Hint 2: || Ha egyik oldalról sem ér hozzá, akkor új komponens keletkezik. ||
// Hint 3: || Ha mindkét oldalról érintkezik, akkor két komponenst egyesít. ||

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    map<int,int> segs;
    for (int i = 0; i < N; ++i) {
        int l, r;
        cin >> l >> r;

        auto it = segs.lower_bound(l);
        auto left = (it == segs.begin() ? segs.end() : prev(it));
        bool adjL = left != segs.end() && left->second + 1 == l;
        bool adjR = it != segs.end() && r + 1 == it->first;

        int nl = l, nr = r;
        if (adjL) {
            nl = left->first;
            nr = max(nr, left->second);
            segs.erase(left);
        }
        if (adjR) {
            nr = it->second;
            segs.erase(it);
        }

        segs[nl] = nr;

        int delta = 1 - int(adjL) - int(adjR);
        cout << segs.size() << '\n';
    }
    return 0;
}