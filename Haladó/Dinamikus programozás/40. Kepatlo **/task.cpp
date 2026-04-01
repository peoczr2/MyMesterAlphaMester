/*
Egy jobbra-lefelé haladó határvonal minden oszlophoz kijelöl egy r sort: az első r pixel a vonal jobb-felső oldalára,
az alatta levők a bal-alsó oldalra kerülnek. Egy oszlop adott r választásának költsége ezért külön számolható a fekete
prefixből és a fehér suffixből. Az oszloponkénti választásoknak csak annyit kell teljesíteniük, hogy a sorindex nem
csökkenhet, így egy prefixminimumos DP megadja a minimális hibaszámot.
*/
/*
Hint 1: || Gondold végig, hogy egy oszlopban hol hagyja el a határvonal az oszlopot. ||
Hint 2: || Ha egy oszlopban r sor fölött fut a vonal, akkor az első r pixel lesz fent, a többi lent. ||
Hint 3: || A következő oszlopban a kilépési sor már nem lehet kisebb, mert a vonal nem mehet felfelé. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
        }
    }

    const int INF = 1e9;
    vector<int> prev(n + 1, INF), curr(n + 1, INF), pref_min(n + 1, INF);
    prev[0] = 0;

    for (int col = 1; col <= n; ++col) {
        vector<int> pref_black(n + 1, 0), pref_white(n + 1, 0);
        for (int row = 1; row <= n; ++row) {
            pref_black[row] = pref_black[row - 1] + (a[row][col] == 0);
            pref_white[row] = pref_white[row - 1] + (a[row][col] == 1);
        }

        pref_min[0] = prev[0];
        for (int row = 1; row <= n; ++row) {
            pref_min[row] = min(pref_min[row - 1], prev[row]);
        }

        for (int row = 0; row <= n; ++row) {
            int cost = pref_black[row] + (pref_white[n] - pref_white[row]);
            curr[row] = pref_min[row] + cost;
        }
        swap(prev, curr);
    }

    cout << prev[n] << '\n';
    return 0;
}