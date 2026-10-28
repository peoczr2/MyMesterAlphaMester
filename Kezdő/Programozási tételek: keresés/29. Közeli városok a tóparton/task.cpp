/*
Megoldás lényege:
A települések a tó körül helyezkednek el, ezért a sorozatot körben kell tekinteni, és az i-edik település K legközelebbi szomszédja egy K+1 elemű, őt tartalmazó összefüggő körszakasz. A sorozatot háromszor egymás mellé írva ezek a szakaszok lineáris indexintervallumként kezelhetők, az 1. település pozíciója 0, a kerület pedig az első szám. Egy szakasz költsége a két szélső elem i-től mért távolságának maximuma, és ez a kezdőindex növelésével előbb csökken, majd nő. A minimumot bináris kereséssel keressük meg, döntetlennél a baloldali (kisebb kezdőindexű) szakasz nyer, mert egyenlő távolságnál a bal oldali szomszéd számít közelebbinek. A kiírt érték a szakasz két szélső sorszáma, az időigény O(N log N).
*/
/*
Hint 1: || A települések egy tó körül vannak, ezért a sorozat végét a kezdetével össze kell kötni, és a kerületet a bemenet első száma adja. ||
Hint 2: || Egy település K legközelebbi szomszédja a körön egy K+1 elemű összefüggő szakasz, amely őt tartalmazza. Ha a pozíciókat háromszor egymás után írod, ezek a szakaszok sima intervallumokként kezelhetők. ||
Hint 3: || A szakasz költsége a szélső elemek távolságának maximuma, és a kezdőindex függvényében előbb csökken, majd nő. Bináris kereséssel találd meg a minimumot, és egyenlő költségnél a kisebb kezdőindexűt válaszd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> raw(n);
    for (auto &x : raw) cin >> x;

    const long long C = raw[0];  // a tó kerülete
    vector<long long> p(n);
    p[0] = 0;
    for (int i = 1; i < n; i++) p[i] = raw[i];

    // A kör háromszoros kiterjesztése: a középső másolat indexei az eredeti települések
    vector<long long> q(3 * n);
    for (int idx = 0; idx < 3 * n; idx++)
        q[idx] = p[idx % n] + (long long)(idx / n - 1) * C;

    for (int i = 0; i < n; i++) {
        int c = i + n;  // i a középső másolatban
        int lo = c - k, hi = c;

        // Első l, ahol a jobboldali távolság nem kisebb a baloldalinál
        int a = lo, b = hi + 1;
        while (a < b) {
            int mid = (a + b) / 2;
            if (q[mid + k] - q[c] >= q[c] - q[mid]) b = mid;
            else a = mid + 1;
        }

        // Két jelölt: a-1 (baloldalibb) és a; egyenlőségnél a kisebb l nyer
        int best = -1;
        long long bestCost = LLONG_MAX;
        for (int l : {a - 1, a}) {
            if (l < lo || l > hi) continue;
            long long cost = max(q[c] - q[l], q[l + k] - q[c]);
            if (cost < bestCost) {
                bestCost = cost;
                best = l;
            }
        }

        int r = best + k;
        int first = (best == c) ? best + 1 : best;
        int last = (r == c) ? r - 1 : r;
        cout << first % n + 1 << ' ' << last % n + 1 << '\n';
    }
    return 0;
}
