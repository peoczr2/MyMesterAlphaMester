/*
Megoldás lényege:
Mindenki egyetlen legismertebb tagra mutat, így a kapcsolatok egy függvénygráfot adnak: minden csúcsból pontosan egy él indul.
Ebben a körök egymástól függetlenek, ezért minden kezdőcsúcsból végigmegyünk az úton, amíg már bejárt csúcshoz nem érünk.
Ha az aktuális bejárásban érünk vissza, az új kör; ennek hossza és legkisebb sorszámú tagja alapján választjuk ki a leghosszabbat.
Mindegyik csúcsot legfeljebb egyszer járjuk be, így az idő O(N).
*/
/*
Hint 1: || Mindenkinek pontosan egy legismertebbje van, így minden csúcsból egyetlen él indul; a körök ebben a szerkezetben könnyen megtalálhatók. ||
Hint 2: || Járd végig az utat egy kezdőcsúcsból, és jegyezd fel a bejárás sorrendjét; ha olyan csúcshoz érsz, amelyet ugyanebben a bejárásban már láttál, az a csúcs egy kör része. ||
Hint 3: || A kör tagjait úgy kapod meg, hogy egy kiválasztott tagtól kezdve mindig a legismertebbjüket követed, amíg vissza nem érsz a kezdőponthoz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> f(n + 1);
    for (int i = 1; i <= n; i++) cin >> f[i];

    vector<int> walk(n + 1, 0); // melyik bejárás (kezdőcsúcs) járta be a csúcsot, 0 = még nem
    vector<int> pos(n + 1, 0);  // a csúcs helye abban a bejárásban
    int bestLen = 0, bestMin = INT_MAX, bestStart = -1;

    for (int s = 1; s <= n; s++) {
        if (walk[s]) continue;
        vector<int> path;
        int u = s;
        while (!walk[u]) {
            walk[u] = s;
            pos[u] = path.size();
            path.push_back(u);
            u = f[u];
        }
        if (walk[u] != s) continue; // már korábbi bejárásban lévő csúcsba futottunk

        int len = path.size() - pos[u];
        int mn = INT_MAX;
        for (int i = pos[u]; i < (int)path.size(); i++) mn = min(mn, path[i]);
        if (len > bestLen || (len == bestLen && mn < bestMin)) {
            bestLen = len;
            bestMin = mn;
            bestStart = mn;
        }
    }

    cout << bestLen << '\n';
    int x = bestStart;
    for (int i = 0; i < bestLen; i++) {
        if (i) cout << ' ';
        cout << x;
        x = f[x];
    }
    cout << '\n';
    return 0;
}
