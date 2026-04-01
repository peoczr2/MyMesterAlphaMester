/*
Megoldas lenyege:
Egy sikeres BST-kereses utolso eleme maga a keresett kulcs. A korabbi elemek mind olyan
csucsok, amelyeknel balra vagy jobbra lepunk tovabb, ez pedig egyre szukebb megengedett
ertektartomanyt ad a kesobbi csucsokra.

Vegigmegyunk a sorozaton, a cel pedig az utolso elem. Fenntartjuk az aktualis (low, high)
nyilt intervallumot, amelybe minden kovetkezo vizsgalt kulcsnak esnie kell. Ha az aktualis
csucs nagyobb a celnal, akkor balra megyunk es a felso korlat csokken; ha kisebb, akkor jobbra
megyunk es az also korlat no. Ha valami megszegi ezt, a sorozat nem lehet BST-keresosorozat.
*/
/*
Hint 1: || Az utolso elemnek kell lennie a keresett kulcsnak. ||
Hint 2: || Minden korabbi elem egy uj also vagy felso korlatot ad a tovabbiakra. ||
Hint 3: || Ismetlodo ertek sem lehet a sorozatban, mert BST-ben a kulcsok kulonbozoek. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int h;
        cin >> h;
        vector<long long> a(h);
        for (int i = 0; i < h; ++i) cin >> a[i];

        long long target = a.back();
        long long low = LLONG_MIN, high = LLONG_MAX;
        bool ok = true;
        unordered_set<long long> seen;
        seen.reserve(2 * h + 1);

        for (int i = 0; i < h; ++i) {
            if (seen.count(a[i])) {
                ok = false;
                break;
            }
            seen.insert(a[i]);

            if (!(low < a[i] && a[i] < high)) {
                ok = false;
                break;
            }
            if (i == h - 1) break;

            if (target < a[i]) {
                high = min(high, a[i]);
            } else if (target > a[i]) {
                low = max(low, a[i]);
            } else {
                ok = false;
                break;
            }
        }

        cout << (ok ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}