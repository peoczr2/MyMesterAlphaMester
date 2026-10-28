/*
Megoldás lényege:
Hó Eduárd ugrása után, minden újabb ugrásnál két érték számít: a nála szigorúan nagyobb pontszámok közül a legkisebb (ez áll közvetlenül előtte), és a nála szigorúan kisebb pontszámok közül a legnagyobb (ez áll közvetlenül utána). Az egyenlő pontszámú versenyző nem áll sem előtte, sem mögötte.
Mindkét értéket futás közben tartjuk karban: új pontszám csak akkor írja felül a régit, ha szigorúan közelebb van Hó Eduárd pontszámához, az egyenlő pontszámú versenyzők pedig ugyanúgy bekerülnek a jelöltek közé. Minden versenyzőt megjelölünk, aki legalább egyszer ilyen helyen állt.
Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A keresett két versenyző Hó Eduárd pontszámához legközelebbi nála nagyobb, illetve kisebb pontszámú versenyző. Csak az M. ugrás után számít a rangsor, és csak azok, akik addig már ugrottak. ||
Hint 2: || Tartsd nyilván futás közben két értéket: a nála szigorúan nagyobb pontszámok legkisebbikét és a nála szigorúan kisebb pontszámok legnagyobbikát. Egy új pontszám csak akkor írja felül a régi értéket, ha a Hó Eduárdhoz képest szigorúan közelebb van. ||
Hint 3: || Egyenlő pontszám esetén a versenyző is bekerül a jelöltek közé, mert ugyanazt a helyet foglalja el. Az M. ugrás előtt ugrottak közül azokat kell egyszer megjelölni, akik az M. ugrás pillanatában a szélső értéket adják; az utána érkezők azonnal megjelölhetők. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];

    const int pm = p[m];
    int felette_min = INT_MAX;  // a nála szigorúan jobb pontszámok legkisebbike
    int alatta_max = -1;        // a nála szigorúan gyengébb pontszámok legnagyobbika

    // Az M. ugrás előtt ugrottak: a szélső értékeket építjük fel.
    for (int i = 1; i < m; i++) {
        if (p[i] > pm) felette_min = min(felette_min, p[i]);
        else if (p[i] < pm) alatta_max = max(alatta_max, p[i]);
    }

    vector<bool> elotte(n + 1, false), utana(n + 1, false);

    // Az M. ugrás pillanatában a jelöltek: a szélső értékkel megegyező pontszámúak.
    for (int i = 1; i < m; i++) {
        if (p[i] > pm && p[i] == felette_min) elotte[i] = true;
        if (p[i] < pm && p[i] == alatta_max) utana[i] = true;
    }

    // Az M. ugrás után érkező versenyzők.
    for (int i = m + 1; i <= n; i++) {
        if (p[i] > pm) {
            if (p[i] < felette_min) felette_min = p[i];
            if (p[i] == felette_min) elotte[i] = true;
        } else if (p[i] < pm) {
            if (p[i] > alatta_max) alatta_max = p[i];
            if (p[i] == alatta_max) utana[i] = true;
        }
    }

    auto kiir = [&](const vector<bool>& jelolt) {
        vector<int> ids;
        for (int i = 1; i <= n; i++)
            if (jelolt[i]) ids.push_back(i);
        cout << ids.size();
        for (int x : ids) cout << ' ' << x;
        cout << '\n';
    };

    kiir(elotte);
    kiir(utana);
    return 0;
}
