/*
Megoldás lényege:
Árvíz az a maximális, egymás melletti mérési sorozat, amelyben minden vízállás meghaladja a 800 cm-t. Az árvíz csúcsmagassága a sorozat legmagasabb mérése, helyét a sorozat első előfordulásaként tartjuk nyilván.
Egy balról jobbra haladó bejárással megkapjuk az árvizek kezdő- és végsorszámát, majd minden árvízben megkeressük a csúcs helyét. A csúcsok sorszámai már növekvő sorrendben vannak, így a szomszédos csúcsok a listában egymás utáni párok.
Ezek közül azt a párt választjuk, amelynek sorszámkülönbsége a legkisebb. Csak a szigorúan kisebb különbség írja felül az eddigit, így egyenlőség esetén az első pár marad.
Az algoritmus O(N) időben fut, ami az N <= 10000 és a 0,1 mp-es időlimit mellett bőven elég.
*/
/*
Hint 1: || Az árvizeket a 800 cm-nél magasabb mérések maximális sorozatai adják. Először ezeket keresd meg, majd minden sorozatban a legmagasabb mérés helyét. ||
Hint 2: || Az árvizek sorszámai a bejárás sorrendjében növekvők. A szomszédos csúcsok közötti távolság a két csúcs sorszámának különbsége, és csak a szomszédos párokat kell vizsgálni. ||
Hint 3: || Tartsd meg az eddig talált legkisebb távolságot, és csak szigorúan kisebbnél írd felül a párt. Így egyenlőség esetén az első pár marad, ahogy a feladat kéri. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // Árvizek: a 800 cm-nél magasabb mérések maximális sorozatai, 1-től indexelve.
    vector<pair<int, int>> arvizek;
    int i = 1;
    while (i <= n) {
        if (a[i] <= 800) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 <= n && a[j + 1] > 800) j++;
        arvizek.push_back({i, j});
        i = j + 1;
    }

    int K = arvizek.size();
    cout << K << '\n';
    if (K == 0) return 0;

    for (int k = 0; k < K; k++) {
        if (k) cout << ' ';
        cout << arvizek[k].first << ' ' << arvizek[k].second;
    }
    cout << '\n';

    // Az egyes árvizek csúcsának helye (első előfordulás).
    vector<int> csucsok;
    for (auto [s, e] : arvizek) {
        int legjobb = s;
        for (int k = s + 1; k <= e; k++)
            if (a[k] > a[legjobb]) legjobb = k;
        csucsok.push_back(legjobb);
    }
    for (int k = 0; k < K; k++) {
        if (k) cout << ' ';
        cout << csucsok[k];
    }
    cout << '\n';

    if (K < 2) return 0;

    // A szomszédos csúcsok közül a legkisebb sorszámkülönbségű (első) pár.
    int legkisebb = INT_MAX, hely = 0;
    for (int k = 0; k + 1 < K; k++) {
        int tav = csucsok[k + 1] - csucsok[k];
        if (tav < legkisebb) {
            legkisebb = tav;
            hely = k;
        }
    }
    cout << csucsok[hely] << ' ' << csucsok[hely + 1] << '\n';
    return 0;
}
