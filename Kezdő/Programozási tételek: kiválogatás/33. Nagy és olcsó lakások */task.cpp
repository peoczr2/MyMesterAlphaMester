/*
Megoldás lényege:
Először kiszámoljuk minden lakás négyzetméterenkénti árát (ár / terület), majd ezek számtani közepét, ami az átlagár. Ezután egy második menetben kiválogatjuk azokat a lakásokat, amelyek területe nagyobb A-nál, és négyzetméterenkénti ára az átlagár alatt marad. Mivel a négyzetméterárak törtek, lebegőpontos számokkal dolgozunk, és az összehasonlításnál egy kis tűrést (1e-9) hagyunk, hogy az egyenlő értékek ne kerüljenek a kiválasztottak közé. A lakásokat sorszám szerint járjuk be, így a kiírt sorszámok automatikusan növekvő sorrendben lesznek. Az időigény O(N), ami N ≤ 100 esetén bőven elég.
*/
/*
Hint 1: || Két menetre van szükség: előbb az összes lakás négyzetméterenkénti árából kell átlagot számolni, utána a feltételeknek megfelelő lakásokat kell kiválogatni. ||
Hint 2: || Egy lakás négyzetméterenkénti ára ár / terület. Az átlag ezek összege osztva N-nel. Mivel törtekkel dolgozol, használj double vagy long double típust, és az összehasonlításnál adj egy kis tűrést. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a;
    cin >> n >> a;

    vector<int> ar(n), terulet(n);
    for (int i = 0; i < n; i++) cin >> ar[i] >> terulet[i];

    // Az átlagár: a lakások négyzetméterenkénti áraink számtani közepe.
    long double atlag = 0;
    for (int i = 0; i < n; i++) atlag += (long double)ar[i] / terulet[i];
    atlag /= n;

    vector<int> valasztott;
    for (int i = 0; i < n; i++) {
        long double nm_ar = (long double)ar[i] / terulet[i];
        if (terulet[i] > a && nm_ar < atlag - 1e-9) valasztott.push_back(i + 1);
    }

    cout << valasztott.size() << '\n';
    for (size_t i = 0; i < valasztott.size(); i++) {
        if (i > 0) cout << ' ';
        cout << valasztott[i];
    }
    cout << '\n';

    return 0;
}
