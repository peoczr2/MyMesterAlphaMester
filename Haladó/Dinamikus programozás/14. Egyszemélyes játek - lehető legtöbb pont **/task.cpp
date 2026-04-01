/*
Mivel a levett párok helye üresen marad, később sem lehet olyan két számot együtt levenni, amelyek között
eredetileg rés keletkezett, tehát a feladat legfeljebb K darab, egymást nem átfedő szomszédos pár kiválasztása.
Legyen dp[t][i] a legnagyobb pontszám az első i számból, ha t párt vettünk le. Az i-edik pozíciónál vagy nem
használjuk az i-edik elemet, vagy levesszük az (i-1,i) párt, és ekkor dp[t-1][i-2]-ből lépünk tovább.
*/
/*
Hint 1: || Az üres helyek miatt egy levett pár után nem olvad össze a két oldal. ||
Hint 2: || Emiatt a feladat fix helyű, nem átfedő hossz-2 blokkok kiválasztásává egyszerűsödik. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<long long> prev(n + 1, 0), cur(n + 1, 0);
    for (int step = 1; step <= k; ++step) {
        fill(cur.begin(), cur.end(), 0);
        for (int i = 1; i <= n; ++i) {
            cur[i] = cur[i - 1];
            if (i >= 2) {
                cur[i] = max(cur[i], prev[i - 2] + a[i - 1] + a[i]);
            }
        }
        prev.swap(cur);
    }

    cout << prev[n] << '\n';
    return 0;
}