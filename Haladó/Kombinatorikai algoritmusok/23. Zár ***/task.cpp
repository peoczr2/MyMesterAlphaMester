/*
Megoldás lényege:
Mindhárom tárcsa külön-külön körben áll. Egy lépésben bármelyik részhalmazt
forgathatjuk egységgel egy irányba, ezért a három tárcsát egymástól függetlenül
kezelhetjük annyiban, hogy egy pozitív irányú lépés több tárcsán egyszerre is
dolgozhat.

Ha egy tárcsát az 1-es állásba akarunk hozni, akkor kétféle irány közül válasz-
thatunk: az óramutató járásával megegyezően vagy ellentétesen. Egy adott irány-
párás választásnál a szükséges lépésszám a pozitív és negatív irányú lépések
maximumának összege. Ezért a 2^3 lehetséges irányválasztást elég kipróbálni.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int a[3];
    for (int i = 0; i < 3; ++i) cin >> a[i];

    int ans = INT_MAX;
    for (int mask = 0; mask < 8; ++mask) {
        int pos = 0, neg = 0;
        for (int i = 0; i < 3; ++i) {
            int cw = (1 - a[i] + n) % n;
            int ccw = (a[i] - 1 + n) % n;
            if (mask & (1 << i)) pos = max(pos, cw);
            else neg = max(neg, ccw);
        }
        ans = min(ans, pos + neg);
    }

    cout << ans << '\n';
    return 0;
}