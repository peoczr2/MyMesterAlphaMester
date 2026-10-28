/*
Megoldás lényege:
A napokat hétfőtől kezdve 0 és 6 közötti indexszel jelöljük, az év első napjának indexe S-1.
Végigmegyünk az év 12 hónapján: minden hónap első napjának indexét egy 7 elemű számlálótömbben eggyel növeljük, majd a következő hónap első napjának indexe az aktuális index plusz a hónap napjainak száma, mod 7.
Február napjainak száma 28 vagy 29, a szökőév-szabály szerint (400-zal osztható, vagy 4-gyel osztható de 100-zal nem).
Az időigény O(1), mert mindig 12 hónapot járunk be.
*/
/*
Hint 1: || Nem kell naptárat építeni: elég az év első napjának indexéből kiindulni, és minden hónap után megnézni, mennyivel tolódik el a következő hónap első napja. ||
Hint 2: || Egy 7 elemű tömbben számold, hányszor fordul elő az egyes napindex hónap első napjaként. A következő hónap indexe: (aktuális + a mostani hónap napjainak száma) mod 7, a február hossza pedig a szökőév-szabálytól függ. ||
*/
#include <bits/stdc++.h>
using namespace std;

static bool szokoev(int ev) {
    if (ev % 400 == 0) return true;
    if (ev % 100 == 0) return false;
    return ev % 4 == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int ev, s;
    cin >> ev >> s;

    vector<int> honapok = {31, 28 + (szokoev(ev) ? 1 : 0), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    array<int, 7> db{};
    int kezdo = s - 1;
    for (int napok : honapok) {
        ++db[kezdo];
        kezdo = (kezdo + napok) % 7;
    }

    for (int i = 0; i < 7; ++i) {
        if (i) cout << ' ';
        cout << db[i];
    }
    cout << '\n';
    return 0;
}