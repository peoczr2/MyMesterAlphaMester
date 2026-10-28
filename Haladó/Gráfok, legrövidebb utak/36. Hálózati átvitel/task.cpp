/*
Megoldás lényege:
A kérdés a legszélesebb út egy változata: egy útvonal sávszélessége a legszűkebb vezetékének sávszélessége, de az útvonal legfeljebb H vezetékből állhat, így a lépésszámot is figyelembe kell venni. Legyen best[v] az a legnagyobb sebesség, amellyel a K csúcsból legfeljebb h vezetéken át v elérhető; h = 0-ra ez csak K-ra végtelen, minden más csúcsra 0. Minden körben egy (u, v, b) élre a best[v] értéket max(best[v], min(best[u], b)) szerint frissítjük, és ezt mindig a régi tömbből számoljuk, így egy körben pontosan egy vezeték kerül az útvonalba. H kör után kész a tömb; a K csúcsra 0-t, a nem elérhetőkre -1-et írunk ki. Az időigény O(H·(N+M)), ami 100·(10 000 + 20 000) körüli művelet, így a 0,25 mp-es időlimit teljesül.
*/
/*
Hint 1: || Az útvonal sávszélessége a legkisebb éle, így a legszélesebb utat úgy keresd, hogy a szűk keresztmetszetet maximalizálod, de az élek száma is korlátos. ||
Hint 2: || Számold ki, mi érhető el legfeljebb h vezetéken: a következő körben egy (u, v, b) él a v csúcsnak min(előző érték[u], b) sebességet adhat, és ezt a maximumhoz hasonlítod. ||
Hint 3: || Minden körben másolatot készíts az előző állapotról, különben egy körben több vezeték is bekerülne és a H-as korlát sérülne. A végén a K csúcs 0, a nem elérhető csúcsok -1 értéket kapnak. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Line {
    int u, v, b;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, h;
    cin >> n >> m >> k >> h;
    vector<Line> lines(m);
    for (auto &l : lines) cin >> l.u >> l.v >> l.b;

    // best[x]: a K csúcsból legfeljebb 'lépés' vezetéken át elérhető legnagyobb sebesség; 0 = nem elérhető
    const int INF = INT_MAX;
    vector<int> best(n + 1, 0);
    best[k] = INF;

    for (int step = 0; step < h; step++) {
        vector<int> next = best;
        for (const auto &l : lines) {
            next[l.v] = max(next[l.v], min(best[l.u], l.b));
            next[l.u] = max(next[l.u], min(best[l.v], l.b));
        }
        best = next;
    }

    for (int i = 1; i <= n; i++) {
        if (i == k) {
            cout << 0 << '\n';
        } else if (best[i] > 0) {
            cout << best[i] << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
    return 0;
}
