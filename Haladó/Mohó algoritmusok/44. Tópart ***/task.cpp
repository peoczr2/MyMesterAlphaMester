/*
Feladat: A partszakaszok közül a lehető legtöbbet kell kiválasztani úgy, hogy ne zavarják egymást.
Ötlet: Ez a klasszikus intervallumütemezés: mindig a legkorábban végződő, még nem ütköző vállalkozást választjuk.
Hint 1: || Ha a következő szakasz már a korábbi után kezdődik, akkor elfér. ||
Hint 2: || A legkorábban végződő szakaszok hagyják meg a legtöbb lehetőséget a későbbiekre. ||
Hint 3: || Ezért rendezés után csak azt kell nézni, hogy az adott szakasz kezdete nagyobb-e az utoljára választott befejezésénél. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end(), [](const auto &x, const auto &y) {
        if (x.second != y.second) return x.second < y.second;
        return x.first < y.first;
    });

    int cnt = 0, last = 0;
    for (auto [l, r] : a) {
        if (l > last) {
            ++cnt;
            last = r;
        }
    }
    cout << cnt << '\n';
    return 0;
}