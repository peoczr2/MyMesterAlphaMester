/*
Megoldás lényege:
Minden szempontra összeadjuk az összes kutya pontját, a kiesőket is beleértve, mert a feladat ezt kéri. Mivel minden szemponthoz ugyanannyi, N darab pontszám tartozik, az átlagok sorrendje megegyezik az összegek sorrendjével, ezért nem kell törtekkel vagy lebegőpontos osztással számolni.
A legnagyobb összegű szempont sorszámát írjuk ki. Egyenlőség esetén a kisebb sorszám marad, mert a maximumot csak szigorúan nagyobb érték írja felül.
A maximum- és ponthatár-sorokat csak be kell olvasni, a megoldáshoz nincs rájuk szükség. Az idő O(N·M), a memóriaigény O(M).
*/
/*
Hint 1: || Nem kell kiszűrni a kiesőket: az átlagot az összes kutya pontjából számoljuk. Elég szempontonként az összes pontot összegezni. ||
Hint 2: || Mivel minden szemponthoz ugyanannyi pontszám tartozik, az összegek sorrendje megegyezik az átlagok sorrendjével. Tárold szempontonként az összeget egy tömbben, majd keress maximumot, és az első előfordulást tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<int> osszeg(m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            osszeg[j] += p;
        }

    int legjobb = 0;
    for (int j = 1; j < m; j++)
        if (osszeg[j] > osszeg[legjobb])
            legjobb = j;

    cout << legjobb + 1 << '\n';
    return 0;
}
