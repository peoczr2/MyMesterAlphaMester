/*
Megoldás lényege:
Minden versenyzőt függetlenül kell vizsgálni, mert a két pontszám különbsége csak az ő két értékétől függ. A pontszámokat tízszeresükre szorozva egész számokká alakítjuk, mivel 0,5-ös lépésekben adhatók, így az átalakítás pontos. Ha a különbség abszolút értéke nagyobb 20-nál (ez 2 pontnak felel meg), a versenyző sorszámát (1-től számozva) eltároljuk. A végén a sorszámokat egy sorban, szóközzel elválasztva írjuk ki, vagy -1-et, ha nincs ilyen versenyző. Az időigény O(N), ami 10^5 versenyzőre bőven belefér az időkorlátba.
*/
/*
Hint 1: || Minden versenyző két pontszáma csak az ő saját különbségét határozza meg, így nincs szükség a többiek adataira. Elég egyetlen menetben végigolvasni a bemenetet, és közben számolni a sorszámot. ||
Hint 2: || A kérdés a két pontszám különbségének abszolút értéke, tehát nem számít, melyik a nagyobb. A tizedes törteket érdemes egész számmá alakítani (például a 8.5-öt 85-nek tekinteni), így a 2 pontos határ összehasonlítása pontos marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> sorszamok;
    for (int i = 1; i <= n; i++) {
        double a, b;
        cin >> a >> b;

        long long x = llround(a * 10);
        long long y = llround(b * 10);
        if (llabs(x - y) > 20) {
            sorszamok.push_back(i);
        }
    }

    if (sorszamok.empty()) {
        cout << -1 << "\n";
    } else {
        for (size_t i = 0; i < sorszamok.size(); i++) {
            if (i > 0) {
                cout << ' ';
            }
            cout << sorszamok[i];
        }
        cout << "\n";
    }

    return 0;
}
