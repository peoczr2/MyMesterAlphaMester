/*
Feladat: A konténerekből a lehető legtöbb helyet kell felszabadítani egymásra pakolással, azzal a kiegészítéssel, hogy ideiglenesen üres helyre is lehet tenni konténert.
Ötlet: Ez is a lehető legkevesebb növekvő láncra bontás feladata: egy új konténer mindig a legnagyobb kisebb láncvégre kerüljön.
Hint 1: || A cél az, hogy minél kevesebb lánc maradjon a végén. ||
Hint 2: || Az aktuális méretet a legnagyobb még kisebb láncvéghez érdemes hozzárendelni. ||
Hint 3: || A válasz a konténerek száma mínusz a láncok száma. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    multiset<int> tails;
    for (int x : a) {
        auto it = tails.lower_bound(x);
        if (it == tails.begin()) {
            tails.insert(x);
        } else {
            --it;
            tails.erase(it);
            tails.insert(x);
        }
    }

    cout << n - (int)tails.size() << '\n';
    return 0;
}