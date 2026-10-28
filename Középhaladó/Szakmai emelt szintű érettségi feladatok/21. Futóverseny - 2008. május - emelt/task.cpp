/*
Megoldás lényege:
Minden versenyző összidejét a köridők összegeként kapjuk meg, századmásodpercben, így az összegzés egész számokkal elvégezhető. A rendezéshez (összidő, rajtszám) párokat használunk: a párok alapértelmezett összehasonlítása először az időt, holtverseny esetén a kisebb rajtszámot veszi figyelembe, ami a feladat szabálya. A kiíráskor az összidőből az osztás és a maradékképzés adja a perc, a másodperc és a századmásodperc részt. Az időigény O(N·L + N log N), ami N ≤ 1000 és L ≤ 100 mellett bőven belefér a korlátba.
*/
/*
Hint 1: || Egy versenyző összideje a köridők összege, és mivel ezek egész századmásodpercek, az összegzés egész számokkal elvégezhető. Utána a versenyzőket érdemes (összidő, rajtszám) párokként tárolni és rendezni. ||
Hint 2: || A kiíráskor az összidőből számold ki a részeket: perc = összidő / 6000, másodperc = (összidő / 100) % 60, századmásodperc = összidő % 100. A másodperc és a századmásodperc mindig két számjegyen jelenjen meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, l;
    cin >> n >> l;
    vector<pair<long long, int>> versenyzok;  // (összidő századmásodpercben, rajtszám)
    for (int i = 1; i <= n; i++) {
        long long osszido = 0;
        for (int j = 0; j < l; j++) {
            long long t;
            cin >> t;
            osszido += t;
        }
        versenyzok.push_back({osszido, i});
    }
    sort(versenyzok.begin(), versenyzok.end());
    for (auto [ido, rajt] : versenyzok) {
        cout << rajt << ' ' << ido / 6000 << ':' << setfill('0') << setw(2) << (ido / 100) % 60
             << ':' << setw(2) << ido % 100 << setfill(' ') << '\n';
    }
    return 0;
}
