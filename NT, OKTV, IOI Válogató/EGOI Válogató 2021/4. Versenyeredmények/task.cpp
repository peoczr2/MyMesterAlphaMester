/*
Megoldas: legrövidebb egyedi előtag minden azonosítóra.
A H hosszu azonosítok lexikografikus sorrendjében eleg a szomszedos elemekkel
megnevezett leghosszabb kozos prefixet nezni. Egy azonositohoz a szukseges
elotag hossza: max(LCP balra, LCP jobbra) + 1.
H kis, ezert stabil radix rendezesre epitjuk az O(NH) megoldast.
*/
/*
Hint 1: || Egy azonosító rövidített alakja akkor egyértelmű, ha egyetlen másik azonosító sem kezdődik ugyanezzel az előtaggal. Ezért minden azonosítóra azt kell megnézni, mekkora a leghosszabb közös előtagja egy másik azonosítóval. ||
Hint 2: || Rendezd az azonosítókat lexikografikusan. Ekkor a leghosszabb közös előtag minden azonosítónál a sorban közvetlenül szomszédos azonosítóval alakul ki, így elég a két szomszédot vizsgálni. ||
Hint 3: || A rendezést stabil számlálórendezéssel (radix rendezéssel) végezd el: előbb az utolsó betű szerint, majd visszafelé az első betűig. Ezután a szomszédos párok közös előtagjából számítsd az egyes azonosítók szükséges előtaghosszát (a maximum plusz egy), és ennek megfelelően írd ki a neveket. ||
*/

#include <bits/stdc++.h>
using namespace std;

static int lcp(const string& a, const string& b) {
    int i = 0, n = (int)a.size();
    while (i < n && a[i] == b[i]) ++i;
    return i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;
    vector<string> nev(n);
    vector<int> pont(n);
    for (int i = 0; i < n; ++i) cin >> nev[i] >> pont[i];

    vector<int> sorrend(n), tmp(n);
    iota(sorrend.begin(), sorrend.end(), 0);
    for (int pos = h - 1; pos >= 0; --pos) {
        int cnt[26] = {0};
        for (int id : sorrend) ++cnt[nev[id][pos] - 'a'];
        for (int i = 1; i < 26; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) {
            int id = sorrend[i];
            tmp[--cnt[nev[id][pos] - 'a']] = id;
        }
        sorrend.swap(tmp);
    }

    vector<int> kell(n, 1);
    for (int i = 0; i < n; ++i) {
        int id = sorrend[i];
        int bal = 0, jobb = 0;
        if (i > 0) bal = lcp(nev[id], nev[sorrend[i - 1]]);
        if (i + 1 < n) jobb = lcp(nev[id], nev[sorrend[i + 1]]);
        kell[id] = min(h, max(bal, jobb) + 1);
    }

    for (int i = 0; i < n; ++i) {
        cout << nev[i].substr(0, kell[i]);
        for (int j = kell[i]; j < h; ++j) cout << '.';
        cout << ' ' << pont[i] << '\n';
    }
    return 0;
}